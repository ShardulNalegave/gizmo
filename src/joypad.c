
#include "gizmo/joypad.h"
#include "gizmo/system.h"
#include "gizmo/interrupts.h"
#include "stdlib.h"

gizmo_joypad_t* gizmo_joypad_create(gizmo_system_t *sys) {
    gizmo_joypad_t *joypad = calloc(1, sizeof(gizmo_joypad_t));
    if (!joypad) {
        return NULL;
    }
    
    joypad->sys = sys;
    gizmo_joypad_reset(joypad);
    
    return joypad;
}

void gizmo_joypad_destroy(gizmo_joypad_t *joypad) {
    free(joypad);
}

void gizmo_joypad_reset(gizmo_joypad_t *joypad) {
    if (!joypad) {
        return;
    }
    
    joypad->reg = 0xFF;
}

void gizmo_joypad_press(gizmo_joypad_t *joypad, uint8_t button) {
    if (!joypad) {
        return;
    }
    
    uint8_t old = joypad->reg;
    joypad->reg &= ~button;
    
    // request interrupt
    if (old != joypad->reg && joypad->sys && joypad->sys->interrupts) {
        gizmo_interrupts_request(joypad->sys->interrupts, INT_JOYPAD);
    }
}

void gizmo_joypad_release(gizmo_joypad_t *joypad, uint8_t button) {
    if (!joypad) {
        return;
    }
    
    joypad->reg |= button;
}

uint8_t gizmo_joypad_read(gizmo_joypad_t *joypad) {
    if (!joypad) {
        return 0xFF;
    }

    if ((joypad->reg & 0b00110000) == 0b00110000) return 0xFF; // if none selected then return all ones
    return joypad->reg | 0b11000000;  // bits 7-6 always 1
}

void gizmo_joypad_write(gizmo_joypad_t *joypad, uint8_t value) {
    if (!joypad) {
        return;
    }
    
    // only bits 4-5 are writeable
    joypad->reg = value & 0b00110000;
}
