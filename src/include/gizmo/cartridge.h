
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
    CART_MBC3 = 0x0F,
    CART_MBC3_RAM = 0x10,
    CART_MBC3_RAM_BATTERY = 0x13,
    CART_MBC5 = 0x19,
    CART_MBC5_RAM = 0x1A,
    CART_MBC5_RAM_BATTERY = 0x1B,
} gizmo_cart_type_t;

struct gizmo_cartridge_s {
    uint8_t *rom;           // Full ROM data
    size_t rom_size;        // ROM size in bytes
    uint8_t *ram;           // External RAM (if present)
    size_t ram_size;        // RAM size in bytes
    
    gizmo_cart_type_t type;
    bool has_battery;
    
    // MBC state
    uint16_t rom_bank;      // Current ROM bank (for MBC1/3/5)
    uint8_t ram_bank;       // Current RAM bank
    bool ram_enabled;       // RAM enable flag
    
    // MBC1 specific
    uint8_t banking_mode;   // 0 = ROM banking, 1 = RAM banking
    
    // Header info
    char title[16];
};

gizmo_cartridge_t* gizmo_cartridge_create(void);
void gizmo_cartridge_destroy(gizmo_cartridge_t *cart);
bool gizmo_cartridge_load(gizmo_cartridge_t *cart, const uint8_t *rom_data, size_t size);

// Memory access (handles MBC logic)
uint8_t gizmo_cartridge_read(gizmo_cartridge_t *cart, uint16_t addr);
void gizmo_cartridge_write(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value);

// Save/load battery-backed RAM
bool gizmo_cartridge_save_ram(gizmo_cartridge_t *cart, const char *path);
bool gizmo_cartridge_load_ram(gizmo_cartridge_t *cart, const char *path);

#endif
