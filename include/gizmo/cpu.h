
#ifndef GIZMO_CPU_H
#define GIZMO_CPU_H

#include "stdbool.h"
#include "gizmo/registers.h"
#include "gizmo/memory.h"

typedef struct {
    gizmo_registers_t registers;
    gizmo_memory_t memory;
} gizmo_cpu_t;

gizmo_cpu_t* gizmo_cpu_init();

#endif