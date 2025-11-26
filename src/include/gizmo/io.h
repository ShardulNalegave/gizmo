
#ifndef GIZMO_IO_H
#define GIZMO_IO_H

#include "stdint.h"
#include "gizmo/types.h"

uint8_t gizmo_io_registers_read(gizmo_system_t *sys, uint16_t addr);
void gizmo_io_registers_write(gizmo_system_t *sys, uint16_t addr, uint8_t value);

#endif
