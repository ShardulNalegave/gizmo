
#include "stdlib.h"
#include "gizmo/cpu.h"

gizmo_cpu_t* gizmo_cpu_init() {
    gizmo_cpu_t* cpu = malloc(sizeof(gizmo_cpu_t));
    return cpu;
}
