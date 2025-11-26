
#include "gizmo/cartridge.h"
#include "gizmo/log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "gizmo/cartridge/rom_only.h"
#include "gizmo/cartridge/mbc1.h"

static bool gizmo_cartridge_read_rom(gizmo_cartridge_t *cart, const char *path) {
    if (!cart || !path) {
        CRITICAL("invalid parameters for ROM read");
        return false;
    }

    FILE *file = fopen(path, "rb");
    if (!file) {
        CRITICAL("failed to open ROM file: %s", path);
        return false;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        CRITICAL("failed to seek ROM file");
        fclose(file);
        return false;
    }

    long size = ftell(file);
    if (size <= 0) {
        CRITICAL("invalid ROM file size: %ld", size);
        fclose(file);
        return false;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        CRITICAL("failed to rewind ROM file");
        fclose(file);
        return false;
    }

    cart->rom = malloc(size);
    if (!cart->rom) {
        CRITICAL("failed to allocate %ld bytes for ROM", size);
        fclose(file);
        return false;
    }

    size_t read = fread(cart->rom, 1, size, file);
    fclose(file);

    if (read != (size_t)size) {
        CRITICAL("failed to read complete ROM: got %zu of %ld bytes", read, size);
        free(cart->rom);
        cart->rom = NULL;
        return false;
    }

    cart->rom_size = size;
    return true;
}

gizmo_cartridge_t* gizmo_cartridge_create(void) {
    gizmo_cartridge_t *cart = calloc(1, sizeof(gizmo_cartridge_t));
    if (!cart) {
        CRITICAL("failed to allocate cartridge structure");
        return NULL;
    }
    return cart;
}

void gizmo_cartridge_destroy(gizmo_cartridge_t *cart) {
    if (!cart) return;
    if (cart->destroy) cart->destroy(cart);
    if (cart->rom) {
        free(cart->rom);
        cart->rom = NULL;
    }
    free(cart);
}

bool gizmo_cartridge_load(gizmo_cartridge_t *cart, const char* rom_path) {
    if (!cart) {
        CRITICAL("null cartridge pointer");
        return false;
    }

    if (!rom_path) {
        CRITICAL("null ROM path");
        return false;
    }

    if (!gizmo_cartridge_read_rom(cart, rom_path)) {
        return false;
    }

    // check if atleast header size bytes are there or not
    if (cart->rom_size < 0x0150) {
        CRITICAL("ROM too small to contain valid header");
        return false;
    }

    memcpy(cart->title, &cart->rom[CART_HEADER_TITLE], 16);
    cart->title[15] = '\0';
    
    uint8_t rom_size_code = cart->rom[CART_HEADER_ROM_SIZE];
    if (rom_size_code > 8) {
        CRITICAL("invalid ROM size code: %02X", rom_size_code);
        return false;
    }
    cart->num_rom_banks = 2 << rom_size_code;

    gizmo_cart_type_t cart_type = cart->rom[CART_HEADER_CARTRIDGE_TYPE];
    
    switch (cart_type) {
        case CART_ROM_ONLY:
            return gizmo_cartridge_load_rom_only(cart);

        case CART_MBC1:
        case CART_MBC1_RAM:
        case CART_MBC1_RAM_BATTERY:
            return gizmo_cartridge_load_mbc1(cart);

        case CART_MBC2:
        case CART_MBC2_BATTERY:
        case CART_MBC3:
        case CART_MBC3_RAM:
        case CART_MBC3_RAM_BATTERY:
        case CART_MBC5:
        case CART_MBC5_RAM:
        case CART_MBC5_RAM_BATTERY:
        case CART_MBC6:
            CRITICAL("cartridge type %02X not yet supported", cart_type);
            return false;

        default:
            CRITICAL("unknown/invalid cartridge type: %02X", cart_type);
            return false;
    }
}

uint8_t gizmo_cartridge_read(gizmo_cartridge_t *cart, uint16_t addr) {
    if (!cart || !cart->read) return 0xFF;
    return cart->read(cart, addr);
}

void gizmo_cartridge_write(gizmo_cartridge_t *cart, uint16_t addr, uint8_t value) {
    if (!cart || !cart->write) return;
    cart->write(cart, addr, value);
}

bool gizmo_cartridge_save_ram(gizmo_cartridge_t *cart, const char *path) {
    if (!cart || !cart->save_ram) return false;
    return cart->save_ram(cart, path);
}

bool gizmo_cartridge_load_ram(gizmo_cartridge_t *cart, const char *path) {
    if (!cart || !cart->load_ram) return false;
    return cart->load_ram(cart, path);
}
