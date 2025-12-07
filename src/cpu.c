
#include "gizmo/cpu.h"
#include "gizmo/system.h"
#include "gizmo/memory.h"
#include "gizmo/instructions.h"
#include "stdlib.h"

gizmo_cpu_t* gizmo_cpu_create(gizmo_system_t *sys) {
    gizmo_cpu_t *cpu = calloc(1, sizeof(gizmo_cpu_t));
    if (!cpu) {
        return NULL;
    }
    
    cpu->sys = sys;
    gizmo_cpu_reset(cpu);
    
    return cpu;
}

void gizmo_cpu_destroy(gizmo_cpu_t *cpu) {
    if (!cpu) return;
    free(cpu);
}

void gizmo_cpu_reset(gizmo_cpu_t *cpu) {
    if (!cpu) return;
    cpu->halted = false;
    cpu->stopped = false;
}

uint8_t gizmo_cpu_step(gizmo_cpu_t *cpu) {
    uint8_t opcode = gizmo_memory_read8(cpu->sys->memory, cpu->reg.pc);
    cpu->reg.pc += 1;

    uint8_t t_cycles = INSTRUCTIONS[opcode](cpu->sys);
    // TODO: Sleep for the right amount of time

    return 0;
}
