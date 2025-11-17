
#ifndef GIZMO_JOYPAD_H
#define GIZMO_JOYPAD_H

#include "stdint.h"
#include "stdbool.h"

// forward-decl
typedef struct gizmo_system_s gizmo_system_t;

typedef enum {
    JOYPAD_BTN_A      = 0,
    JOYPAD_BTN_B      = 1,
    JOYPAD_BTN_SELECT = 2,
    JOYPAD_BTN_START  = 3,
    JOYPAD_BTN_RIGHT  = 4,
    JOYPAD_BTN_LEFT   = 5,
    JOYPAD_BTN_UP     = 6,
    JOYPAD_BTN_DOWN   = 7
} gizmo_joypad_btn_t;

typedef struct gizmo_joypad_s {
    gizmo_system_t *sys;
    
    uint8_t reg;          // JOYPAD register (0xFF00)
} gizmo_joypad_t;

gizmo_joypad_t* gizmo_joypad_create(gizmo_system_t *sys);
void gizmo_joypad_destroy(gizmo_joypad_t *joypad);
void gizmo_joypad_reset(gizmo_joypad_t *joypad);

void gizmo_joypad_press(gizmo_joypad_t *joypad, gizmo_joypad_btn_t button);
void gizmo_joypad_release(gizmo_joypad_t *joypad, gizmo_joypad_btn_t button);

uint8_t gizmo_joypad_read(gizmo_joypad_t *joypad);
void gizmo_joypad_write(gizmo_joypad_t *joypad, uint8_t value);

#endif
