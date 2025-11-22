
#ifndef GIZMO_JOYPAD_H
#define GIZMO_JOYPAD_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/types.h"

struct gizmo_joypad_s {
    gizmo_system_t *sys;    
    uint8_t reg;      // 0xFF00
};

gizmo_joypad_t* gizmo_joypad_create(gizmo_system_t *sys);
void gizmo_joypad_destroy(gizmo_joypad_t *joypad);
void gizmo_joypad_reset(gizmo_joypad_t *joypad);

void gizmo_joypad_press(gizmo_joypad_t *joypad, uint8_t button);
void gizmo_joypad_release(gizmo_joypad_t *joypad, uint8_t button);

uint8_t gizmo_joypad_read(gizmo_joypad_t *joypad);
void gizmo_joypad_write(gizmo_joypad_t *joypad, uint8_t value);

#endif
