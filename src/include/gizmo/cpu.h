
#ifndef GIZMO_CPU_H
#define GIZMO_CPU_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/registers.h"

// forward-decl
typedef struct gizmo_system_s gizmo_system_t;

typedef struct gizmo_cpu_s {
    gizmo_registers_t reg;
    gizmo_system_t *sys;
    
    bool halted;
    bool stopped;
} gizmo_cpu_t;

gizmo_cpu_t* gizmo_cpu_create(gizmo_system_t *sys);
void gizmo_cpu_destroy(gizmo_cpu_t *cpu);
void gizmo_cpu_reset(gizmo_cpu_t *cpu);

// Execute an instruction
uint8_t gizmo_cpu_step(gizmo_cpu_t *cpu);

uint8_t gizmo_cpu_read8(gizmo_cpu_t *cpu, uint16_t addr);
void gizmo_cpu_write8(gizmo_cpu_t *cpu, uint16_t addr, uint8_t value);

uint16_t gizmo_cpu_read16(gizmo_cpu_t *cpu, uint16_t addr);
void gizmo_cpu_write16(gizmo_cpu_t *cpu, uint16_t addr, uint16_t value);

void gizmo_cpu_push(gizmo_cpu_t *cpu, uint16_t value);
uint16_t gizmo_cpu_pop(gizmo_cpu_t *cpu);

#endif
