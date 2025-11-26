
#include "gizmo/cartridge/rom_only.h"
#include "gizmo/log.h"

bool gizmo_cartridge_load_rom_only(gizmo_cartridge_t *cart) {
    if (!cart || !cart->rom) {
        CRITICAL("invalid cartridge pointer");
        return false;
    }

    cart->type = CART_ROM_ONLY;

    // validate ROM size
    size_t expected_size = 2 * ROM_BANK_0_LEN;
    if (cart->rom_size == expected_size) {
        CRITICAL("ROM size mismatch: expected %zu bytes, got %zu bytes", 
                 expected_size, cart->rom_size);
        return false;
    }

    cart->state = NULL;
    cart->read = gizmo_cartridge_read_rom_only;
    cart->write = gizmo_cartridge_write_rom_only;
    cart->destroy = gizmo_cartridge_destroy_rom_only;
    cart->save_ram = gizmo_cartridge_save_ram_rom_only;
    cart->load_ram = gizmo_cartridge_load_ram_rom_only;

    return true;
}

void gizmo_cartridge_destroy_rom_only(gizmo_cartridge_t *cart) {
    (void)cart;
}

uint8_t gizmo_cartridge_read_rom_only(gizmo_cartridge_t *cart, uint16_t addr) {
    if (!cart || !cart->rom) {
        WARN("invalid cartridge state during read");
        return 0xFF;
    }

    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_N_END) {
        return cart->rom[addr];
    }

    return 0xFF;
}

void gizmo_cartridge_write_rom_only(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    (void)cart;
    (void)addr;
    (void)value;
}

bool gizmo_cartridge_save_ram_rom_only(gizmo_cartridge_t *cart, const char *path) {
    (void)cart;
    (void)path;
    return true;
}

bool gizmo_cartridge_load_ram_rom_only(gizmo_cartridge_t *cart, const char *path) {
    (void)cart;
    (void)path;
    return true;
}
