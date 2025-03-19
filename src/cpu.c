
#include "gizmo/registers.h"
#include "gizmo/cpu.h"

gizmo_cpu_t cpu;

void gizmo_cpu_init() {
    // TODO: Initialize all registers correctly
}

bool gizmo_cpu_is_flag_set(uint8_t f) {
    return (cpu.registers.f & f) == f;
}