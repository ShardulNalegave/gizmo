
#ifndef GIZMO_VRAM_H
#define GIZMO_VRAM_H

#include "stdint.h"

typedef struct gizmo_vram_t gizmo_vram_t;

struct gizmo_vram_t {
    uint8_t data[0x2000];
};

#endif