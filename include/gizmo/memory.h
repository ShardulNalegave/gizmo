
#ifndef GIZMO_MEMORY_H
#define GIZMO_MEMORY_H

#include "stdint.h"
#include "gizmo/memory/vram.h"

typedef struct {
    gizmo_vram_t vram;
    int8_t wram[0x2000];
} gizmo_memory_t;

#endif