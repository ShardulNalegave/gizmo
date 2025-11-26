
#include "gizmo/cartridge/mbc1.h"
#include "gizmo/log.h"
#include "stdio.h"
#include "stdlib.h"

static inline uint8_t calculate_bank_mask(uint8_t num_banks) {
    if (num_banks == 0) return 0;
    
    uint8_t mask = num_banks - 1;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    
    return mask;
}

bool gizmo_cartridge_load_mbc1(gizmo_cartridge_t *cart) {
    if (!cart || !cart->rom) {
        CRITICAL("invalid cartridge pointer");
        return false;
    }

    // cartridge type
    switch (cart->rom[CART_HEADER_CARTRIDGE_TYPE]) {
        case CART_MBC1:
            cart->type = CART_MBC1;
            break;
        case CART_MBC1_RAM:
            cart->type = CART_MBC1_RAM;
            break;
        case CART_MBC1_RAM_BATTERY:
            cart->type = CART_MBC1_RAM_BATTERY;
            break;
        default:
            CRITICAL("invalid MBC1 cartridge type");
            return false;
    }

    // validate ROM size matches header
    if (cart->rom_size != (size_t)cart->num_rom_banks * ROM_BANK_0_LEN) {
        CRITICAL("ROM size mismatch: expected %zu bytes, got %zu bytes", 
                 (size_t)cart->num_rom_banks * ROM_BANK_0_LEN, cart->rom_size);
        return false;
    }

    gizmo_cartridge_mbc1_state_t *state = calloc(1, sizeof(gizmo_cartridge_mbc1_state_t));
    if (!state) {
        CRITICAL("failed to allocate MBC1 state");
        return false;
    }

    // initialize ram
    switch (cart->rom[CART_HEADER_RAM_SIZE]) {
        case CART_SRAM_BANKS_0:
            state->num_ram_banks = 0;
            state->ram = NULL;
            break;
        case CART_SRAM_BANKS_1:
            state->num_ram_banks = 1;
            break;
        case CART_SRAM_BANKS_4:
            state->num_ram_banks = 4;
            break;
        default:
            WARN("unexpected RAM size %02X, defaulting to no RAM", 
                 cart->rom[CART_HEADER_RAM_SIZE]);
            state->num_ram_banks = 0;
            state->ram = NULL;
            break;
    }

    if (state->num_ram_banks > 0) {
        size_t ram_size = (size_t)state->num_ram_banks * ERAM_LEN;
        state->ram = calloc(1, ram_size);
        if (!state->ram) {
            CRITICAL("failed to allocate %zu bytes for cartridge RAM", ram_size);
            free(state);
            return false;
        }
    }

    state->rom_bank_mask = calculate_bank_mask(cart->num_rom_banks);
    state->ram_bank_mask = calculate_bank_mask(state->num_ram_banks);

    state->ram_enable = false;
    state->rom_bank_lower = 0x01;
    state->bank_upper = 0x00;
    state->banking_mode = 0;

    cart->state = state;
    cart->read = gizmo_cartridge_read_mbc1;
    cart->write = gizmo_cartridge_write_mbc1;
    cart->destroy = gizmo_cartridge_destroy_mbc1;
    cart->save_ram = gizmo_cartridge_save_ram_mbc1;
    cart->load_ram = gizmo_cartridge_load_ram_mbc1;

    return true;
}

void gizmo_cartridge_destroy_mbc1(gizmo_cartridge_t *cart) {
    if (!cart || !cart->state) return;
    
    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;
    if (state->ram) {
        free(state->ram);
        state->ram = NULL;
    }
    
    free(state);
    cart->state = NULL;
}

uint8_t gizmo_cartridge_read_mbc1(gizmo_cartridge_t *cart, uint16_t addr) {
    if (!cart || !cart->state) {
        WARN("invalid cartridge state during read");
        return 0xFF;
    }

    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;

    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_0_END) {
        uint8_t bank_num = 0;
        
        // advanced mode
        if (state->banking_mode == 1) {
            bank_num = (state->bank_upper << 5) & state->rom_bank_mask;
        }
        
        size_t rom_addr = ((size_t)bank_num * ROM_BANK_0_LEN) + addr;
        
        if (rom_addr >= cart->rom_size) {
            WARN("ROM read out of bounds: addr=%04X, bank=%02X", addr, bank_num);
            return 0xFF;
        }
        
        return cart->rom[rom_addr];
    }

    if (addr >= ROM_BANK_N_START && addr <= ROM_BANK_N_END) {
        uint8_t bank_num;
        
        if (state->banking_mode == 0) {
            // simple mode
            bank_num = ((state->bank_upper << 5) | state->rom_bank_lower) & state->rom_bank_mask;
        } else {
            // advanced mode
            bank_num = state->rom_bank_lower & state->rom_bank_mask;
        }
        
        if (bank_num == 0) bank_num = 1;
        uint16_t offset = addr - ROM_BANK_N_START;
        size_t rom_addr = ((size_t)bank_num * ROM_BANK_N_LEN) + offset;
        
        if (rom_addr >= cart->rom_size) {
            WARN("ROM read out of bounds: addr=%04X, bank=%02X", addr, bank_num);
            return 0xFF;
        }
        
        return cart->rom[rom_addr];
    }

    if (addr >= ERAM_START && addr <= ERAM_END) {
        if (!state->ram || state->num_ram_banks == 0) return 0xFF;
        if (!state->ram_enable) return 0xFF;
        
        uint8_t bank_num;
        
        if (state->banking_mode == 0) {
            // simple mode
            bank_num = 0;
        } else {
            // advanced mode
            bank_num = state->bank_upper & state->ram_bank_mask;
        }
        
        uint16_t offset = addr - ERAM_START;
        size_t ram_addr = ((size_t)bank_num * ERAM_LEN) + offset;
        
        if (ram_addr >= (size_t)state->num_ram_banks * ERAM_LEN) {
            WARN("RAM read out of bounds: addr=%04X, bank=%02X", addr, bank_num);
            return 0xFF;
        }
        
        return state->ram[ram_addr];
    }

    WARN("cartridge read from invalid address: %04X", addr);
    return 0xFF;
}

void gizmo_cartridge_write_mbc1(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    if (!cart || !cart->state) {
        WARN("invalid cartridge state during write");
        return;
    }

    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;

    // RAM Enable Register
    if (addr <= 0x1FFF) {
        state->ram_enable = ((value & 0x0F) == 0x0A);
        return;
    }

    // ROM Bank Number
    if (addr >= 0x2000 && addr <= 0x3FFF) {
        uint8_t bank = value & 0x1F;
        if (bank == 0) bank = 1;
        state->rom_bank_lower = bank;
        return;
    }

    // RAM Bank Number / Upper ROM Bank Bits
    if (addr >= 0x4000 && addr <= 0x5FFF) {
        state->bank_upper = value & 0x03;
        return;
    }

    // Banking Mode Select
    if (addr >= 0x6000 && addr <= 0x7FFF) {
        state->banking_mode = value & 0x01;
        return;
    }

    if (addr >= ERAM_START && addr <= ERAM_END) {
        if (!state->ram || state->num_ram_banks == 0) return;
        if (!state->ram_enable) return;
        
        uint8_t bank_num;
        
        if (state->banking_mode == 0) {
            // simple mode
            bank_num = 0;
        } else {
            // advanced mode
            bank_num = state->bank_upper & state->ram_bank_mask;
        }
        
        uint16_t offset = addr - ERAM_START;
        size_t ram_addr = ((size_t)bank_num * ERAM_LEN) + offset;
        
        if (ram_addr >= (size_t)state->num_ram_banks * ERAM_LEN) {
            WARN("RAM write out of bounds: addr=%04X, bank=%02X", addr, bank_num);
            return;
        }
        
        state->ram[ram_addr] = value;
        return;
    }
}

bool gizmo_cartridge_save_ram_mbc1(gizmo_cartridge_t *cart, const char *path) {
    if (!cart || !cart->state || !path) {
        ERROR("invalid parameters for RAM save");
        return false;
    }

    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;
    
    if (!state->ram || state->num_ram_banks == 0) {
        WARN("cartridge has no RAM to save");
        return false;
    }

    FILE *file = fopen(path, "wb");
    if (!file) {
        ERROR("failed to open save file for writing: %s", path);
        return false;
    }

    size_t ram_size = (size_t)state->num_ram_banks * ERAM_LEN;
    size_t written = fwrite(state->ram, 1, ram_size, file);
    fclose(file);

    if (written != ram_size) {
        ERROR("failed to write complete RAM data: wrote %zu of %zu bytes", written, ram_size);
        return false;
    }

    return true;
}

bool gizmo_cartridge_load_ram_mbc1(gizmo_cartridge_t *cart, const char *path) {
    if (!cart || !cart->state || !path) {
        ERROR("invalid parameters for RAM load");
        return false;
    }

    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;
    
    if (!state->ram || state->num_ram_banks == 0) {
        WARN("cartridge has no RAM to load");
        return false;
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        WARN("save file not found: %s", path);
        return false;
    }

    size_t ram_size = (size_t)state->num_ram_banks * ERAM_LEN;
    size_t read = fread(state->ram, 1, ram_size, file);
    fclose(file);

    if (read != ram_size) {
        WARN("save file size mismatch: expected %zu bytes, got %zu bytes", ram_size, read);
    }

    return true;
}
