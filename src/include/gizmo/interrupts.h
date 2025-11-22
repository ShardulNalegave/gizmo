
#ifndef GIZMO_INTERRUPTS_H
#define GIZMO_INTERRUPTS_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/types.h"

struct gizmo_interrupts_s {
    uint8_t ie;     // interrupt enable
    uint8_t if_;    // interrupt flags
};

gizmo_interrupts_t* gizmo_interrupts_create(void);
void gizmo_interrupts_destroy(gizmo_interrupts_t *interrupts);
void gizmo_interrupts_reset(gizmo_interrupts_t *interrupts);

// Request an interrupt
void gizmo_interrupts_request(gizmo_interrupts_t *interrupts, uint8_t interrupt_bit);

// Check if any interrupt should be serviced
bool gizmo_interrupts_pending(gizmo_interrupts_t *interrupts);

// Get the highest priority pending interrupt (returns bit position or -1)
int gizmo_interrupts_get_next(gizmo_interrupts_t *interrupts);

// Acknowledge/clear an interrupt
void gizmo_interrupts_acknowledge(gizmo_interrupts_t *interrupts, uint8_t interrupt_bit);

#endif
