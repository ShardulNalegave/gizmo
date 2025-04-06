
#ifndef GIZMO_CARTRIDGE_H
#define GIZMO_CARTRIDGE_H

#include "stdint.h"

#define CARTRIDGE_ROM_BANK_SIZE 16  // 16 KiB
#define CARTRIDGE_RAM_BANK_SIZE 8   // 8 KiB
#define CARTRIDGE_HEADER_TITLE_LEN 16

typedef enum cartridge_type_t cartridge_type_t;
typedef struct cartridge_header_t cartridge_header_t;
typedef struct gizmo_cartridge_t gizmo_cartridge_t;

enum cartridge_type_t {
    CARTRIDGE_TYPE_ROM_ONLY = 0x00,
    CARTRIDGE_TYPE_MBC1 = 0x01,
    CARTRIDGE_TYPE_MBC1_RAM = 0x02,
    CARTRIDGE_TYPE_MBC1_RAM_BATTERY = 0x03,
    CARTRIDGE_TYPE_MBC2 = 0x05,
    CARTRIDGE_TYPE_MBC2_BATTERY = 0x06,
    CARTRIDGE_TYPE_ROM_RAM = 0x08,
    CARTRIDGE_TYPE_ROM_RAM_BATTERY = 0x09,
    CARTRIDGE_TYPE_MMM01 = 0x0B,
    CARTRIDGE_TYPE_MMM01_RAM = 0x0C,
    CARTRIDGE_TYPE_MMM01_RAM_BATTERY = 0x0D,
    CARTRIDGE_TYPE_MBC3_TIMER_BATTERY = 0x0F,
    CARTRIDGE_TYPE_MBC3_TIMER_RAM_BATTERY = 0x10,
    CARTRIDGE_TYPE_MBC3 = 0x11,
    CARTRIDGE_TYPE_MBC3_RAM = 0x12,
    CARTRIDGE_TYPE_MBC3_RAM_BATTERY = 0x13,
    CARTRIDGE_TYPE_MBC5 = 0x19,
    CARTRIDGE_TYPE_MBC5_RAM = 0x1A,
    CARTRIDGE_TYPE_MBC5_RAM_BATTERY = 0x1B,
    CARTRIDGE_TYPE_MBC5_RUMBLE = 0x1C,
    CARTRIDGE_TYPE_MBC5_RUMBLE_RAM = 0x1D,
    CARTRIDGE_TYPE_MBC5_RUMBLE_RAM_BATTERY = 0x1E,
    CARTRIDGE_TYPE_MBC6 = 0x20,
    CARTRIDGE_TYPE_MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
    CARTRIDGE_TYPE_POCKET_CAMERA = 0xFC,
    CARTRIDGE_TYPE_BANDAI_TAMA5 = 0xFD,
    CARTRIDGE_TYPE_HuC3 = 0xFE,
    CARTRIDGE_TYPE_HuC1_RAM_BATTERY = 0xFF,
};

struct cartridge_header_t {
    uint8_t* entry_point;               // 0x100-0x103
    char* title;                        // 0x134-0x143
    cartridge_type_t cartridge_type;    // 0x147
};

struct gizmo_cartridge_t {
    cartridge_header_t header;
    uint8_t (*read)(gizmo_cartridge_t*, uint16_t);
    void (*write)(gizmo_cartridge_t*, uint16_t, uint8_t);
    void* state;
};

gizmo_cartridge_t* gizmo_cartridge_init();
void gizmo_cartridge_destroy(gizmo_cartridge_t*);

static inline uint8_t gizmo_cartridge_read(gizmo_cartridge_t* cart, uint16_t addr) {
    return cart->read(cart, addr);
}

static inline void gizmo_cartridge_write(gizmo_cartridge_t* cart, uint16_t addr, uint8_t val) {
    return cart->write(cart, addr, val);
}

#endif // GIZMO_CARTRIDGE_H