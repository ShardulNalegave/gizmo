
#ifndef GIZMO_CARTRIDGE_ROM_ONLY_H
#define GIZMO_CARTRIDGE_ROM_ONLY_H

#include "stdint.h"
#include "gizmo/cartridge.h"

bool gizmo_cartridge_load_rom_only(gizmo_cartridge_t *cart);
void gizmo_cartridge_destroy_rom_only(gizmo_cartridge_t *cart);

bool gizmo_cartridge_read_rom_only(gizmo_cartridge_t *cart, uint16_t addr);
void gizmo_cartridge_write_rom_only(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value);

#endif
