
#ifndef GIZMO_TYPES_H
#define GIZMO_TYPES_H

typedef struct gizmo_system_s gizmo_system_t;
typedef struct gizmo_cpu_s gizmo_cpu_t;
typedef struct gizmo_memory_s gizmo_memory_t;
typedef struct gizmo_ppu_s gizmo_ppu_t;
typedef struct gizmo_timer_s gizmo_timer_t;
typedef struct gizmo_cartridge_s gizmo_cartridge_t;
typedef struct gizmo_joypad_s gizmo_joypad_t;
typedef struct gizmo_interrupts_s gizmo_interrupts_t;
typedef struct gizmo_serial_s gizmo_serial_t;

#define FLAG_ZERO   0x80  // Zero flag
#define FLAG_SUB    0x40  // Subtract flag (BCD)
#define FLAG_HALF   0x20  // Half-carry flag
#define FLAG_CARRY  0x10  // Carry flag

#define JOYPAD_RIGHT  0b11101110
#define JOYPAD_LEFT   0b11101101
#define JOYPAD_UP     0b11101011
#define JOYPAD_DOWN   0b11100111

#define CART_HEADER_TITLE           0x0134
#define CART_HEADER_CARTRIDGE_TYPE  0x0147
#define CART_HEADER_ROM_SIZE        0x0148
#define CART_HEADER_RAM_SIZE        0x0149

#define CART_SRAM_BANKS_0   0x00
#define CART_SRAM_BANKS_1   0x02
#define CART_SRAM_BANKS_4   0x03
#define CART_SRAM_BANKS_8   0x05
#define CART_SRAM_BANKS_16  0x04

#define ROM_BANK_0_START    0x0000
#define ROM_BANK_0_END      0x3FFF
#define ROM_BANK_0_LEN      0x4000

#define ROM_BANK_N_START    0x4000
#define ROM_BANK_N_END      0x7FFF
#define ROM_BANK_N_LEN      0x4000

#define VRAM_START          0x8000
#define VRAM_END            0x9FFF
#define VRAM_LEN            0x2000

#define ERAM_START          0xA000
#define ERAM_END            0xBFFF
#define ERAM_LEN            0x2000

#define WRAM_START          0xC000
#define WRAM_END            0xDFFF
#define WRAM_LEN            0x2000

#define ECHO_START          0xE000
#define ECHO_END            0xFDFF
#define ECHO_LEN            0x1DFF

#define OAM_START           0xFE00
#define OAM_END             0xFE9F
#define OAM_LEN             0x9F

#define UNUSABLE_START      0xFEA0
#define UNUSABLE_END        0xFEFF
#define UNUSABLE_LEN        0x5F

#define IO_REG_START        0xFF00
#define IO_REG_END          0xFF7F
#define IO_REG_LEN          0x7F

#define HRAM_START          0xFF80
#define HRAM_END            0xFFFE
#define HRAM_LEN            0x7E

#define IE_REG              0xFFFF

#define JOYPAD_REG      0xFF00
#define JOYPAD_A        0b11011110
#define JOYPAD_B        0b11011101
#define JOYPAD_SELECT   0b11011011
#define JOYPAD_START    0b11010111

#define SERIAL_DATA     0xFF01
#define SERIAL_CONTROL  0xFF02

#define TIMER_DIV   0xFF04
#define TIMER_TIMA  0xFF05
#define TIMER_TMA   0xFF06
#define TIMER_TAC   0xFF07

#define TIMER_CLOCK_4_M_CYCLES      0b01
#define TIMER_CLOCK_16_M_CYCLES     0b10
#define TIMER_CLOCK_64_M_CYCLES     0b11
#define TIMER_CLOCK_256_M_CYCLES    0b00

#define INT_FLAG_REG    0xFF0F
#define INT_VBLANK      0x01  // VBlank interrupt
#define INT_LCD         0x02  // LCD STAT interrupt
#define INT_TIMER       0x04  // Timer interrupt
#define INT_SERIAL      0x08  // Serial interrupt
#define INT_JOYPAD      0x10  // Joypad interrupt

#endif
