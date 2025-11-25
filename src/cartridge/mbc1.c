
#include "gizmo/cartridge/mbc1.h"
#include "gizmo/log.h"
#include "stdlib.h"

bool gizmo_cartridge_load_mbc1(gizmo_cartridge_t *cart) {
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
            CRITICAL("cartridge has an invalid/unsupported type");
            return false;
    }

    // ensure correct rom size
    if (cart->rom_size != cart->num_rom_banks * 0x4000) {
        CRITICAL("provided ROM's actual size does not match size mentioned in header");
        return false;
    }

    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)malloc(sizeof(gizmo_cartridge_mbc1_state_t));
    if (!state) {
        CRITICAL("could not load MBC1 cartridge");
        return false;
    }

    // ram banks
    switch (cart->rom[CART_HEADER_RAM_SIZE]) {
        case CART_SRAM_BANKS_1:
            state->num_ram_banks = 1;
            break;
        case CART_SRAM_BANKS_4:
            state->num_ram_banks = 4;
            break;
        case CART_SRAM_BANKS_8:
            state->num_ram_banks = 8;
            break;
        case CART_SRAM_BANKS_16:
            state->num_ram_banks = 16;
            break;
        case CART_SRAM_BANKS_0:
        default:
            state->ram = NULL;
            state->num_ram_banks = 0;
            break;
    }

    // allocate ram
    if (state->num_ram_banks > 0) {
        state->ram = calloc(1, state->num_ram_banks * 0x2000);
        if (!state->ram) {
            CRITICAL("could not load MBC1 cartridge");
            return false;
        }
    }

    state->ram_enable = false;
    state->rom_bank_number = 0x00;
    state->ram_bank_number = 0x00;
    state->banking_mode = 0x00;

    cart->state = state;
    cart->read = gizmo_cartridge_read_mbc1;
    cart->write = gizmo_cartridge_write_mbc1;
    cart->destroy = gizmo_cartridge_destroy_mbc1;

    cart->save_ram = gizmo_cartridge_save_ram_mbc1;
    cart->load_ram = gizmo_cartridge_load_ram_mbc1;

    return true;
}

void gizmo_cartridge_destroy_mbc1(gizmo_cartridge_t *cart) {
    if (!cart) return;
    free(cart->state);
}

uint8_t gizmo_cartridge_read_mbc1(gizmo_cartridge_t *cart, uint16_t addr) {
    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_0_END) { // 0x0000 - 0x3FFF
        //
    } else if (addr >= ROM_BANK_N_START && addr <= ROM_BANK_N_END) { // 0x4000 - 0x7FFF
        //
    } else if (addr >= ERAM_START && addr <= ERAM_END) { // 0xA000 - 0xBFFF
        //
    }

    WARN("invalid memory address %#X requested for read from cartridge. returning 0xFF", addr);
    return 0xFF;
}

void gizmo_cartridge_write_mbc1(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    gizmo_cartridge_mbc1_state_t *state = (gizmo_cartridge_mbc1_state_t*)cart->state;

    if (addr >= 0x0000 && addr <= 0x1FFF) { // RAM enable register
        if ((value & 0x0F) == 0x0A) {
            state->ram_enable = true;
        } else {
            state->ram_enable = false;
        }
    } else if (addr >= 0x2000 && addr <= 0x3FFF) { // ROM bank number
        uint8_t num = value & 0x1F;
        if (num == 0) num = 1;
        state->rom_bank_number = num;
    } else if (addr >= 0x4000 && addr <= 0x5FFF) { // RAM bank number or upper bits (5,6) of ROM bank number
        state->ram_bank_number = value & 0x3;
    } else if (addr >= 0x6000 && addr <= 0x7FFF) { // Banking mode select
        switch (value & 1) {
            case 1:
                state->banking_mode = CART_MBC1_BANKING_MODE_ADVANCED;
                break;
            case 0:
            default: // default is not possible but keeping it just in case
                state->banking_mode = CART_MBC1_BANKING_MODE_SIMPLE;
                break;
        }
    }

    WARN("invalid memory address %#X requested for write to cartridge registers. ignoring", addr);
}

bool gizmo_cartridge_save_ram_mbc1(gizmo_cartridge_t *cart, const char *path) {}
bool gizmo_cartridge_load_ram_mbc1(gizmo_cartridge_t *cart, const char *path) {}
