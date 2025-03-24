
#ifndef GIZMO_IO_TIMER_DIVIDER_H
#define GIZMO_IO_TIMER_DIVIDER_H

#include "stdint.h"

typedef enum timer_control_t timer_control_t;
typedef struct gizmo_io_timer_divider_t gizmo_io_timer_divider_t;

enum timer_control_t {
    TIMER_CONTROL_ENABLE = 0b00000100,
    TIMER_CONTROL_256M = 0b00000000,
    TIMER_CONTROL_4M = 0b00000001,
    TIMER_CONTROL_16M = 0b00000010,
    TIMER_CONTROL_64M = 0b00000011
};

struct gizmo_io_timer_divider_t {
    uint8_t divider;             // DIV - 0xFF04
    uint8_t timer_counter;       // TIMA - 0xFF05
    uint8_t timer_modulo;        // TMA - 0xFF06
    uint8_t timer_control;       // TAC - 0xFF07
};

#endif