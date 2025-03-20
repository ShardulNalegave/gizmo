
#ifndef GIZMO_IO_TIMER_DIVIDER_H
#define GIZMO_IO_TIMER_DIVIDER_H

#include "stdint.h"

typedef enum {
    TIMER_CONTROL_ENABLE = 0b00000100,
    TIMER_CONTROL_256M = 0b00000000,
    TIMER_CONTROL_4M = 0b00000001,
    TIMER_CONTROL_16M = 0b00000010,
    TIMER_CONTROL_64M = 0b00000011
} timer_control_t;

typedef struct {
    int8_t divider;             // DIV
    int8_t timer_counter;       // TIMA
    int8_t timer_modulo;        // TMA
    int8_t timer_control;       // TAC
} gizmo_io_timer_divider_t;

#endif