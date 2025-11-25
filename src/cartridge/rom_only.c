
#include "gizmo/cartridge/rom_only.h"
#include "gizmo/log.h"

bool gizmo_cartridge_load_rom_only(gizmo_cartridge_t *cart) {
    cart->type = CART_ROM_ONLY;

    // ensure correct rom size
    if (cart->rom_size != cart->num_rom_banks * 0x4000) {
        CRITICAL("provided ROM's actual size does not match size mentioned in header");
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
    //
}

uint8_t gizmo_cartridge_read_rom_only(gizmo_cartridge_t *cart, uint16_t addr) {
    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_N_END) { // 0x0000 - 0x7FFF
        return cart->rom[addr];
    }

    WARN("invalid memory address %#X requested for read from cartridge. returning 0xFF", addr);
    return 0xFF;
}

void gizmo_cartridge_write_rom_only(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    // ignore all writes
    WARN("write requested to a ROM-only cartridge. ignoring");
}

bool gizmo_cartridge_save_ram_rom_only(gizmo_cartridge_t *cart, const char *path) {
    ERROR("save RAM requested on ROM-only cartridge");
    return false;
}

bool gizmo_cartridge_load_ram_rom_only(gizmo_cartridge_t *cart, const char *path) {
    ERROR("load RAM requested on ROM-only cartridge");
    return false;
}
