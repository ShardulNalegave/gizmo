
#ifndef GIZMO_MEMORY_H
#define GIZMO_MEMORY_H

#include "stdint.h"
#include "gizmo/types.h"

struct gizmo_memory_s {
    gizmo_system_t *sys;

    uint8_t wram[WRAM_LEN];
    uint8_t hram[HRAM_LEN];
};

gizmo_memory_t* gizmo_memory_create(gizmo_system_t *sys);
void gizmo_memory_destroy(gizmo_memory_t *memory);
void gizmo_memory_reset(gizmo_memory_t *memory);

uint8_t gizmo_memory_read8(gizmo_memory_t *memory, uint16_t addr);
void gizmo_memory_write8(gizmo_memory_t *memory, uint16_t addr, uint8_t value);

uint16_t gizmo_memory_read16(gizmo_memory_t *memory, uint16_t addr);
void gizmo_memory_write16(gizmo_memory_t *memory, uint16_t addr, uint16_t value);

#endif
