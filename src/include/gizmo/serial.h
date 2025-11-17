
#ifndef GIZMO_SERIAL_H
#define GIZMO_SERIAL_H

#include "stdint.h"

// forward-decl
typedef struct gizmo_system_s gizmo_system_t;

typedef struct gizmo_serial_s {
    gizmo_system_t *sys;
    
    uint8_t sb;  // Serial data (0xFF01)
    uint8_t sc;  // Serial control (0xFF02)
    
    uint8_t cycles;  // Transfer progress counter
} gizmo_serial_t;

gizmo_serial_t* gizmo_serial_create(gizmo_system_t *sys);
void gizmo_serial_destroy(gizmo_serial_t *serial);
void gizmo_serial_reset(gizmo_serial_t *serial);

void gizmo_serial_step(gizmo_serial_t *serial, uint8_t cycles);

#endif
