
#include "gizmo/instructions.h"
#include "gizmo/system.h"
#include "gizmo/cpu.h"

const instruction_fn INSTRUCTIONS[0x100] = {
    [0x00] = gizmo_instruction_00,
    [0x01] = gizmo_instruction_01,
    [0x02] = gizmo_instruction_02,
    [0x03] = gizmo_instruction_03,
};

uint8_t gizmo_instruction_00(gizmo_system_t *sys) { // NOP
    return 4;
}

uint8_t gizmo_instruction_01(gizmo_system_t *sys) { // LD BC,nn
    uint16_t value = gizmo_system_read16(sys, sys->cpu->reg.pc);
    sys->cpu->reg.pc += 2;
    sys->cpu->reg.bc = value;
    return 12;
}

uint8_t gizmo_instruction_02(gizmo_system_t *sys) { // LD [BC],A
    gizmo_system_write8(sys, sys->cpu->reg.bc, sys->cpu->reg.a);
    return 8;
}

uint8_t gizmo_instruction_03(gizmo_system_t *sys) { // INC BC
    sys->cpu->reg.bc += 1;
    return 8;
}
