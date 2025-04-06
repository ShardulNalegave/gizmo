
#ifndef GIZMO_CARTRIDGE_ROM_ONLY_H
#define GIZMO_CARTRIDGE_ROM_ONLY_H

#include "stdint.h"

typedef struct gizmo_cartridge_t gizmo_cartridge_t;

uint8_t rom_only_read(gizmo_cartridge_t*, uint16_t);
void rom_only_write(gizmo_cartridge_t*, uint16_t, uint8_t);

#endif