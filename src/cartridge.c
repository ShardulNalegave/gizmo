
#include "gizmo/cartridge.h"
#include "gizmo/log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "gizmo/cartridge/rom_only.h"

static inline bool gizmo_cartridge_read_rom(gizmo_cartridge_t *cart, const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        CRITICAL("could not open ROM file");
        return false;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    cart->rom = malloc(size);
    if (!cart->rom) {
        CRITICAL("could not open ROM file");
        fclose(file);
        return false;
    }

    cart->rom_size = size;
    fread(cart->rom, 1, size, file);
    fclose(file);
    return true;
}

gizmo_cartridge_t* gizmo_cartridge_create(void) {
    gizmo_cartridge_t *cart = calloc(1, sizeof(gizmo_cartridge_t));
    if (!cart) {
        CRITICAL("could not create cartridge instance");
        return NULL;
    }

    return cart;
}

void gizmo_cartridge_destroy(gizmo_cartridge_t *cart) {
    if (!cart) return;
    free(cart->rom);
    free(cart);
}

bool gizmo_cartridge_load(gizmo_cartridge_t *cart, const char* rom_path) {
    if (!cart) return false;
    if (gizmo_cartridge_read_rom(cart, rom_path)) return false;

    // read title
    memcpy(cart->title, &cart->rom[CART_HEADER_TITLE], 16);

    // read cartridge type
    switch (cart->rom[0][CART_HEADER_CARTRIDGE_TYPE]) {
        case CART_ROM_ONLY:
            return gizmo_cartridge_load_rom_only(cart);

        case CART_MBC1:
        case CART_MBC1_RAM:
        case CART_MBC1_RAM_BATTERY:
        case CART_MBC2:
        case CART_MBC2_BATTERY:
        case CART_MBC3:
        case CART_MBC3_RAM:
        case CART_MBC3_RAM_BATTERY:
        case CART_MBC5:
        case CART_MBC5_RAM:
        case CART_MBC5_RAM_BATTERY:
        case CART_MBC6:
        default:
            CRITICAL("cartridge has an invalid type");
            return false;
    }

    return true;
}

uint8_t gizmo_cartridge_read(gizmo_cartridge_t *cart, uint16_t addr) {
    if (!cart) return 0xFF;
    return cart->read(cart, addr);
}

void gizmo_cartridge_write(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    if (!cart) return;
    return cart->write(cart, addr, value);
}

bool gizmo_cartridge_save_ram(gizmo_cartridge_t *cart, const char *path);
bool gizmo_cartridge_load_ram(gizmo_cartridge_t *cart, const char *path);
