
#ifndef GIZMO_MEMORY_H
#define GIZMO_MEMORY_H

#include "stdint.h"
#include "gizmo/vram.h"
#include "gizmo/io.h"

typedef struct {
    uint8_t cartridge[0x8000];
    gizmo_vram_t vram;
    uint8_t wram[0x2000];
    gizmo_io_t io;
    uint8_t interrupt_enable_register;
} gizmo_memory_t;

#endif