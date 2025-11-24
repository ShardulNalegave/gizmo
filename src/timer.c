
#include "gizmo/timer.h"
#include "gizmo/interrupts.h"
#include "gizmo/system.h"
#include "stdlib.h"

static inline bool gizmo_timer_get_timer_bit(gizmo_timer_t *timer) {
    bool timer_enabled = (timer->tac & 0x04) == 1;
    if (!timer_enabled) return false;
    
    uint8_t freq = timer->tac & 0x03;
    int bit_position;
    
    switch (freq) {
        case TIMER_CLOCK_256_M_CYCLES:
            bit_position = 9; break;
        case TIMER_CLOCK_4_M_CYCLES:
            bit_position = 3; break;
        case TIMER_CLOCK_16_M_CYCLES:
            bit_position = 5; break;
        case TIMER_CLOCK_64_M_CYCLES:
            bit_position = 7; break;

        default: bit_position = 9; break;  // unreachable
    }
    
    return timer->counter >> bit_position;
}

static inline void gizmo_timer_increment_tima(gizmo_timer_t *timer) {
    timer->tima++;
    
    // handle overflow
    if (timer->tima == 0x00) {
        timer->overflow_scheduled = true;
    }
}

static inline void gizmo_timer_process_overflow(gizmo_timer_t *timer) {
    if (!timer->overflow_scheduled) return;
    
    timer->tima = timer->tma;
    gizmo_interrupts_request(timer->sys->interrupts, INT_TIMER);
    timer->overflow_scheduled = false;
}

gizmo_timer_t* gizmo_timer_create(gizmo_system_t *sys) {
    gizmo_timer_t *timer = calloc(1, sizeof(gizmo_timer_t));
    if (!timer) {
        return NULL;
    }
    
    timer->sys = sys;
    gizmo_timer_reset(timer);
    
    return timer;
}

void gizmo_timer_destroy(gizmo_timer_t *timer) {
    if (timer) free(timer);
}

void gizmo_timer_reset(gizmo_timer_t *timer) {
    if (!timer) return;

    timer->counter = 0xABCC; // power on value
    
    timer->tima = 0x00;
    timer->tma = 0x00;
    timer->tac = 0xF8;
    
    timer->prev_timer_bit = false;
    timer->overflow_scheduled = false;
}

void gizmo_timer_step(gizmo_timer_t *timer, uint8_t cycles) {
    if (!timer) return;
    
    for (uint8_t i = 0; i < cycles; i++) {
        gizmo_timer_process_overflow(timer);
        
        bool old_timer_bit = gizmo_timer_get_timer_bit(timer);
        timer->counter += 4;
        bool new_timer_bit = gizmo_timer_get_timer_bit(timer);
        
        if (old_timer_bit && !new_timer_bit) {
            gizmo_timer_increment_tima(timer);
        }
        
        timer->prev_timer_bit = new_timer_bit;
    }
}

void gizmo_timer_write(gizmo_timer_t *timer, uint16_t addr, uint8_t val) {
    if (!timer) return;
    
    switch (addr) {
        case TIMER_DIV: {
            // this can cause a falling edge glitch on the timer bit hence we check it here too
            
            bool old_timer_bit = gizmo_timer_get_timer_bit(timer);
            timer->counter = 0x0000;
            bool new_timer_bit = gizmo_timer_get_timer_bit(timer);
            
            if (old_timer_bit && !new_timer_bit) {
                gizmo_timer_increment_tima(timer);
            }
            
            timer->prev_timer_bit = new_timer_bit;
            break;
        }
        
        case TIMER_TIMA:
            // writing TIMA during the M-cycle when reload is scheduled cancels the reload
            if (timer->overflow_scheduled) {
                timer->overflow_scheduled = false;
            }
            timer->tima = val;
            break;
        
        case TIMER_TMA:
            timer->tma = val;
            break;
        
        case TIMER_TAC: {
            // can cause a falling edge glitch, hence we check it here
            
            bool old_timer_bit = gizmo_timer_get_timer_bit(timer);
            timer->tac = (val & 0x07) | 0xF8; // only bits 0-2 are writeable
            bool new_timer_bit = gizmo_timer_get_timer_bit(timer);
            
            if (old_timer_bit && !new_timer_bit) {
                gizmo_timer_increment_tima(timer);
            }
            
            timer->prev_timer_bit = new_timer_bit;
            break;
        }
        
        default:
            break;
    }
}

uint8_t gizmo_timer_read(gizmo_timer_t *timer, uint16_t addr) {
    if (!timer) return 0xFF;
    
    switch (addr) {
        case TIMER_DIV:
            // DIV is just the upper 8 bits of the internal counter
            return (timer->counter >> 8) & 0xFF;
        
        case TIMER_TIMA:
            return timer->tima;
        
        case TIMER_TMA:
            return timer->tma;
        
        case TIMER_TAC:
            return timer->tac;
        
        default:
            return 0xFF;
    }
}
