
#ifndef GIZMO_IO_H
#define GIZMO_IO_H

#include "stdint.h"
#include "gizmo/serial_data.h"
#include "gizmo/timer_divider.h"
#include "gizmo/audio.h"

typedef enum {
    JOYPAD_DOWN = 0b11100111,
    JOYPAD_UP = 0b11101011,
    JOYPAD_LEFT = 0b11101101,
    JOYPAD_RIGHT = 0b11101110,

    JOYPAD_START = 0b11010111,
    JOYPAD_SELECT = 0b11011011,
    JOYPAD_B = 0b11011101,
    JOYPAD_A = 0b11011110,
} joypad_t;

typedef enum {
    INTERRUPT_FLAG_VBLANK = 0b00000001,
    INTERRUPT_FLAG_LCD = 0b00000010,
    INTERRUPT_FLAG_TIMER = 0b00000100,
    INTERRUPT_FLAG_SERIAL = 0b00001000,
    INTERRUPT_FLAG_JOYPAD = 0b00010000,
} interrupt_flag_t;

typedef struct {
    int8_t joypad;                              // 0xFF00
    gizmo_io_serial_data_t serial_data;         // 0xFF01-0xFF02
    gizmo_io_timer_divider_t timer_divider;     // 0xFF04-0xFF07
    int8_t interrupt_flag;                      // 0xFF0F
    gizmo_audio_t audio;                        // 0xFF10-0xFF26 and 0xFF30-0xFF3F
    // TODO: Add LCD registers (0xFF40-0xFF4B)
    uint8_t boot_rom_disable;                   // 0xFF50
} gizmo_io_t;

#endif