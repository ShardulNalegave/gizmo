
#ifndef GIZMO_CARTRIDGE_H
#define GIZMO_CARTRIDGE_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "gizmo/types.h"

typedef enum {
    CART_ROM_ONLY = 0x00,
    CART_MBC1 = 0x01,
    CART_MBC1_RAM = 0x02,
    CART_MBC1_RAM_BATTERY = 0x03,
    CART_MBC2 = 0x05,
    CART_MBC2_BATTERY = 0x06,
    CART_MBC3 = 0x11,
    CART_MBC3_RAM = 0x12,
    CART_MBC3_RAM_BATTERY = 0x13,
    CART_MBC5 = 0x19,
    CART_MBC5_RAM = 0x1A,
    CART_MBC5_RAM_BATTERY = 0x1B,
    CART_MBC6 = 0x20,
} gizmo_cart_type_t;

struct gizmo_cartridge_s {
    gizmo_cart_type_t type;
    char title[16];

    uint8_t **rom;
    uint8_t num_rom_banks;
    size_t rom_size;

    uint8_t **ram_banks;
    uint8_t num_ram_banks;

    void *state;

    uint8_t (*read)(struct gizmo_cartridge_s *cart, uint16_t addr);
    void (*write)(struct gizmo_cartridge_s *cart, uint16_t addr, uint8_t value);
    void (*destroy)(struct gizmo_cartridge_s *cart);
};

gizmo_cartridge_t* gizmo_cartridge_create(void);
void gizmo_cartridge_destroy(gizmo_cartridge_t *cart);
bool gizmo_cartridge_load(gizmo_cartridge_t *cart, const char* rom_path);

uint8_t gizmo_cartridge_read(gizmo_cartridge_t *cart, uint16_t addr);
void gizmo_cartridge_write(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value);

bool gizmo_cartridge_save_ram(gizmo_cartridge_t *cart, const char *path);
bool gizmo_cartridge_load_ram(gizmo_cartridge_t *cart, const char *path);

#endif
