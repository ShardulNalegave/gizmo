
#ifndef GIZMO_PPU_H
#define GIZMO_PPU_H

#include "stdint.h"
#include "stdbool.h"

// forward-decl
typedef struct gizmo_system_s gizmo_system_t;

typedef enum {
    PPU_MODE_HBLANK = 0,
    PPU_MODE_VBLANK = 1,
    PPU_MODE_OAM_SCAN = 2,
    PPU_MODE_DRAWING = 3
} gizmo_ppu_mode_t;

typedef struct {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t flags;
} gizmo_oam_entry_t;

typedef struct gizmo_ppu_s {
    gizmo_system_t *sys;
    
    uint8_t vram[0x2000];
    gizmo_oam_entry_t oam[40];
    
    // Registers (0xFF40-0xFF4B)
    uint8_t lcdc;  // LCD Control
    uint8_t stat;  // LCD Status
    uint8_t scy;   // Scroll Y
    uint8_t scx;   // Scroll X
    uint8_t ly;    // LCD Y coordinate (current scanline)
    uint8_t lyc;   // LY Compare
    uint8_t dma;   // DMA transfer
    uint8_t bgp;   // BG Palette
    uint8_t obp0;  // OBJ Palette 0
    uint8_t obp1;  // OBJ Palette 1
    uint8_t wy;    // Window Y
    uint8_t wx;    // Window X
    
    gizmo_ppu_mode_t mode;
    uint16_t dots;  // Dot counter within current scanline (0-455)
    
    // Frame buffer: 160x144 pixels, each pixel 0-3 (2-bit color)
    uint8_t framebuffer[160 * 144];
    bool frame_ready;
} gizmo_ppu_t;

gizmo_ppu_t* gizmo_ppu_create(gizmo_system_t *sys);
void gizmo_ppu_destroy(gizmo_ppu_t *ppu);
void gizmo_ppu_reset(gizmo_ppu_t *ppu);

// Execution - step by M-cycles (4 dots per M-cycle)
void gizmo_ppu_step(gizmo_ppu_t *ppu, uint8_t cycles);

// DMA transfer
void gizmo_ppu_dma_transfer(gizmo_ppu_t *ppu, uint8_t start_addr);

#endif
