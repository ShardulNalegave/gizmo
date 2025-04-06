
#include "gizmo/cartridge.h"
#include "gizmo/cartridge/rom_only.h"

uint8_t rom_only_read(gizmo_cartridge_t* cart, uint16_t addr) {
    //
}

void rom_only_write(gizmo_cartridge_t* cart, uint16_t addr, uint8_t val) {
    (void)cart;
    (void)addr;
    (void)val;
}