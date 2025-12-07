
#ifndef GIZMO_INSTRUCTIONS_H
#define GIZMO_INSTRUCTIONS_H

#include "stdint.h"
#include "gizmo/types.h"

typedef uint8_t (*instruction_fn)(gizmo_system_t *sys); // returns number of T-cycles required
extern const instruction_fn INSTRUCTIONS[0x100];

uint8_t gizmo_instruction_00(gizmo_system_t *sys); // NOP
uint8_t gizmo_instruction_01(gizmo_system_t *sys); // LD BC,nn
uint8_t gizmo_instruction_02(gizmo_system_t *sys); // LD [BC],A
uint8_t gizmo_instruction_03(gizmo_system_t *sys); // INC BC

#endif
