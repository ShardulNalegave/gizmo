
#ifndef GIZMO_SYSTEM_H
#define GIZMO_SYSTEM_H

#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

// forward-decls
typedef struct gizmo_cpu_s gizmo_cpu_t;
typedef struct gizmo_ppu_s gizmo_ppu_t;
typedef struct gizmo_timer_s gizmo_timer_t;
typedef struct gizmo_cartridge_s gizmo_cartridge_t;
typedef struct gizmo_joypad_s gizmo_joypad_t;
typedef struct gizmo_interrupts_s gizmo_interrupts_t;

typedef struct {
    gizmo_cpu_t *cpu;
    gizmo_ppu_t *ppu;
    gizmo_timer_t *timer;
    gizmo_cartridge_t *cartridge;
    gizmo_joypad_t *joypad;
    gizmo_interrupts_t *interrupts;
    
    uint8_t wram[0x2000];
    uint8_t hram[0x7F];
    
    uint64_t cycles;
    bool running;
} gizmo_system_t;

gizmo_system_t* gizmo_system_create(void);
void gizmo_system_destroy(gizmo_system_t *sys);
bool gizmo_system_load_rom(gizmo_system_t *sys, const uint8_t *rom_data, size_t size);
void gizmo_system_reset(gizmo_system_t *sys);

void gizmo_system_step(gizmo_system_t *sys);  // Execute one instruction
void gizmo_system_run_frame(gizmo_system_t *sys);  // Run until VBlank

uint8_t gizmo_system_read(gizmo_system_t *sys, uint16_t addr);
void gizmo_system_write(gizmo_system_t *sys, uint16_t addr, uint8_t value);

#endif
