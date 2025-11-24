
#ifndef GIZMO_TIMER_H
#define GIZMO_TIMER_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/types.h"

struct gizmo_timer_s {
    gizmo_system_t *sys;
    
    // Registers
    uint8_t tima;  // 0xFF05 - Timer counter
    uint8_t tma;   // 0xFF06 - Timer modulo
    uint8_t tac;   // 0xFF07 - Timer control
    // DIV is just the upper 8-bits of the internal counter
    
    uint16_t counter;  // internal counter (counts T-cycles)
    uint16_t prev_timer_bit;
    bool overflow_scheduled;
};

gizmo_timer_t* gizmo_timer_create(gizmo_system_t *sys);
void gizmo_timer_destroy(gizmo_timer_t *timer);
void gizmo_timer_reset(gizmo_timer_t *timer);

// Execution - step by M-cycles
void gizmo_timer_step(gizmo_timer_t *timer, uint8_t cycles);

void gizmo_timer_write(gizmo_timer_t *timer, uint16_t addr, uint8_t val);
uint8_t gizmo_timer_read(gizmo_timer_t *timer, uint16_t addr);

#endif
