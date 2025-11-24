
#ifndef GIZMO_TYPES_H
#define GIZMO_TYPES_H

typedef struct gizmo_system_s gizmo_system_t;
typedef struct gizmo_cpu_s gizmo_cpu_t;
typedef struct gizmo_ppu_s gizmo_ppu_t;
typedef struct gizmo_timer_s gizmo_timer_t;
typedef struct gizmo_cartridge_s gizmo_cartridge_t;
typedef struct gizmo_joypad_s gizmo_joypad_t;
typedef struct gizmo_interrupts_s gizmo_interrupts_t;
typedef struct gizmo_serial_t gizmo_serial_s;

#define FLAG_ZERO   0x80  // Zero flag
#define FLAG_SUB    0x40  // Subtract flag (BCD)
#define FLAG_HALF   0x20  // Half-carry flag
#define FLAG_CARRY  0x10  // Carry flag

#define INT_VBLANK  0x01  // VBlank interrupt
#define INT_LCD     0x02  // LCD STAT interrupt
#define INT_TIMER   0x04  // Timer interrupt
#define INT_SERIAL  0x08  // Serial interrupt
#define INT_JOYPAD  0x10  // Joypad interrupt

#define TIMER_DIV   0xFF04
#define TIMER_TIMA  0xFF05
#define TIMER_TMA   0xFF06
#define TIMER_TAC   0xFF07

#define TIMER_CLOCK_4_M_CYCLES      0b01
#define TIMER_CLOCK_16_M_CYCLES     0b10
#define TIMER_CLOCK_64_M_CYCLES     0b11
#define TIMER_CLOCK_256_M_CYCLES    0b00

#define JOYPAD_A      0b11011110
#define JOYPAD_B      0b11011101
#define JOYPAD_SELECT 0b11011011
#define JOYPAD_START  0b11010111

#define JOYPAD_RIGHT  0b11101110
#define JOYPAD_LEFT   0b11101101
#define JOYPAD_UP     0b11101011
#define JOYPAD_DOWN   0b11100111

#endif
