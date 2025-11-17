
#ifndef GIZMO_MEMORY_H
#define GIZMO_MEMORY_H

#include "stdint.h"
#include "gizmo/types.h"

typedef struct {
    uint8_t vram[VRAM_LEN];
    uint8_t wram[WRAM_LEN];
    uint8_t hram[HRAM_LEN];
    uint8_t ie; // interrupt enable
} gizmo_memory_t;

uint8_t gizmo_memory_get(gizmo_memory_t *mem, uint16_t addr);
void gizmo_memory_set(gizmo_memory_t *mem, uint16_t addr, uint8_t value);

#endif
