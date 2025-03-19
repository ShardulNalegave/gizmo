
#ifndef GIZMO_CPU_H
#define GIZMO_CPU_H

#include "stdbool.h"
#include "gizmo/registers.h"

typedef struct {
    registers_t registers;
} gizmo_cpu_t;

void gizmo_cpu_init();
bool gizmo_cpu_is_flag_set(uint8_t f);

#endif