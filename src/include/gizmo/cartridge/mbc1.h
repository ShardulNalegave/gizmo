
#ifndef GIZMO_CARTRIDGE_MBC1_H
#define GIZMO_CARTRIDGE_MBC1_H

#include "stdint.h"
#include "stdbool.h"
#include "gizmo/cartridge.h"

typedef struct {
    uint8_t *ram;
    uint8_t num_ram_banks;
    uint8_t rom_bank_mask;
    uint8_t ram_bank_mask;

    bool ram_enable;
    uint8_t rom_bank_lower;  // 5-bit register
    uint8_t bank_upper;      // 2-bit register
    uint8_t banking_mode;    // 0 = simple, 1 = advanced
} gizmo_cartridge_mbc1_state_t;

bool gizmo_cartridge_load_mbc1(gizmo_cartridge_t *cart);
void gizmo_cartridge_destroy_mbc1(gizmo_cartridge_t *cart);

uint8_t gizmo_cartridge_read_mbc1(gizmo_cartridge_t *cart, uint16_t addr);
void gizmo_cartridge_write_mbc1(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value);

bool gizmo_cartridge_save_ram_mbc1(gizmo_cartridge_t *cart, const char *path);
bool gizmo_cartridge_load_ram_mbc1(gizmo_cartridge_t *cart, const char *path);

#endif
