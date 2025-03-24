
#ifndef GIZMO_REGISTERS_H
#define GIZMO_REGISTERS_H

#include "stdint.h"

typedef enum flags_t flags_t;
typedef struct gizmo_registers_t gizmo_registers_t;

enum flags_t {
    FLAG_ZERO = 0b10000000,
    FLAG_SUBTRACT = 0b01000000,
    FLAG_HALF_CARRY = 0b00100000,
    FLAG_CARRY = 0b00010000,
};

struct gizmo_registers_t {
    union {
        struct {
            uint8_t a;
            uint8_t f;
        };
        uint16_t af;
    };
    union {
        struct {
            uint8_t b;
            uint8_t c;
        };
        uint16_t bc;
    };
    union {
        struct {
            uint8_t d;
            uint8_t e;
        };
        uint16_t de;
    };
    union {
        struct {
            uint8_t h;
            uint8_t l;
        };
        uint16_t hl;
    };
    uint16_t sp;
    uint16_t pc;
};

#endif