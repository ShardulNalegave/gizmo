
#ifndef GIZMO_VRAM_H
#define GIZMO_VRAM_H

#include "stdint.h"

typedef struct {
    uint8_t data[0x2000];
} gizmo_vram_t;

#endif