
#ifndef GIZMO_TIMER_H
#define GIZMO_TIMER_H

#include "stdint.h"
#include "stdbool.h"

// forward-decl
typedef struct gizmo_system_s gizmo_system_t;

typedef struct gizmo_timer_s {
    gizmo_system_t *sys;
    
    // Registers
    uint8_t div;   // 0xFF04 - Divider (upper 8 bits of internal counter)
    uint8_t tima;  // 0xFF05 - Timer counter
    uint8_t tma;   // 0xFF06 - Timer modulo
    uint8_t tac;   // 0xFF07 - Timer control
    
    uint16_t div_counter;  // Full 16-bit internal divider counter
    uint16_t tima_counter; // Internal counter for TIMA
} gizmo_timer_t;

gizmo_timer_t* gizmo_timer_create(gizmo_system_t *sys);
void gizmo_timer_destroy(gizmo_timer_t *timer);
void gizmo_timer_reset(gizmo_timer_t *timer);

// Execution - step by M-cycles
void gizmo_timer_step(gizmo_timer_t *timer, uint8_t cycles);

// Register access (special behavior for DIV write)
void gizmo_timer_write_div(gizmo_timer_t *timer);

#endif
