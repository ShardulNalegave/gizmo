
#include "gizmo/interrupts.h"
#include "stdlib.h"

gizmo_interrupts_t* gizmo_interrupts_create(void) {
    gizmo_interrupts_t *interrupts = calloc(1, sizeof(gizmo_interrupts_t));
    if (!interrupts) {
        return NULL;
    }
    
    gizmo_interrupts_reset(interrupts);
    return interrupts;
}

void gizmo_interrupts_destroy(gizmo_interrupts_t *interrupts) {
    if (interrupts) {
        free(interrupts);
    }
}

void gizmo_interrupts_reset(gizmo_interrupts_t *interrupts) {
    if (!interrupts) {
        return;
    }
    
    interrupts->ie = 0x00;
    interrupts->if_ = 0x00;
}

void gizmo_interrupts_request(gizmo_interrupts_t *interrupts, uint8_t interrupt_bit) {
    if (!interrupts) {
        return;
    }
    
    interrupts->if_ |= (interrupt_bit & 0x1F);
}

bool gizmo_interrupts_pending(gizmo_interrupts_t *interrupts) {
    if (!interrupts) {
        return false;
    }
    
    return (interrupts->ie & interrupts->if_ & 0x1F) != 0;
}

int gizmo_interrupts_get_next(gizmo_interrupts_t *interrupts) {
    if (!interrupts) {
        return -1;
    }
    
    uint8_t pending = interrupts->ie & interrupts->if_ & 0x1F;
    
    if (pending == 0) {
        return -1;
    }
    
    // priority:-
    // VBlank > LCD > Timer > Serial > Joypad
    
    if (pending & INT_VBLANK) return 0;
    else if (pending & INT_LCD) return 1;
    else if (pending & INT_TIMER) return 2;
    else if (pending & INT_SERIAL)return 3;
    else if (pending & INT_JOYPAD) return 4;
    
    return -1;  // unreachable
}

void gizmo_interrupts_acknowledge(gizmo_interrupts_t *interrupts, uint8_t interrupt_bit) {
    if (!interrupts) {
        return;
    }
    
    interrupts->if_ &= ~(interrupt_bit & 0x1F);
}
