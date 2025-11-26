
#ifndef GIZMO_CPU_H
#define GIZMO_CPU_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/types.h"
#include "gizmo/registers.h"

struct gizmo_cpu_s {
    gizmo_registers_t reg;
    gizmo_system_t *sys;
    
    bool halted;
    bool stopped;
};

gizmo_cpu_t* gizmo_cpu_create(gizmo_system_t *sys);
void gizmo_cpu_destroy(gizmo_cpu_t *cpu);
void gizmo_cpu_reset(gizmo_cpu_t *cpu);

// Execute an instruction
uint8_t gizmo_cpu_step(gizmo_cpu_t *cpu);

#endif
