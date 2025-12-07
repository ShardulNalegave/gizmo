
#include "gizmo/memory.h"
#include "stdlib.h"

#include "gizmo/system.h"
#include "gizmo/cartridge.h"
#include "gizmo/interrupts.h"
#include "gizmo/io.h"

gizmo_memory_t* gizmo_memory_create(gizmo_system_t *sys) {
    gizmo_memory_t *memory = calloc(1, sizeof(gizmo_memory_t));
    if (!memory) {
        return NULL;
    }
    
    memory->sys = sys;
    gizmo_memory_reset(memory);
    
    return memory;
}

void gizmo_memory_destroy(gizmo_memory_t *memory) {
    free(memory);
}

void gizmo_memory_reset(gizmo_memory_t *memory) {
    if (!memory) {
        return;
    }

    // set all values to zero
    for (int i = 0; i < WRAM_LEN; i++) {
        if (i < HRAM_LEN) memory->hram[i] = 0;
        memory->wram[i] = 0;
    }
}

uint8_t gizmo_memory_read8(gizmo_memory_t *memory, uint16_t addr) {
    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_N_END) { // 0x0000 - 0x7FFF
        return gizmo_cartridge_read(memory->sys->cartridge, addr);
    } else if (addr >= VRAM_START && addr <= VRAM_END) { // 0x8000 - 9FFF
        // TODO: Implement read for VRAM
        return 0xFF;
    } else if (addr >= ERAM_START && addr <= ERAM_END) { // 0xA000 - 0xBFFF
        return gizmo_cartridge_read(memory->sys->cartridge, addr);
    } else if (addr >= WRAM_START && addr <= WRAM_END) { // 0xC000 - 0xDFFF
        return memory->wram[addr - WRAM_START];
    } else if (addr >= ECHO_START && addr <= ECHO_END) { // 0xE000 - 0xFDFF
        return memory->wram[addr - ECHO_START];
    } else if (addr >= OAM_START && addr <= OAM_END) {
        // TODO: Implement OAM read
        return 0xFF;
    } else if (addr >= UNUSABLE_START && addr <= UNUSABLE_END) {
        // TODO: Implement the unusable section of memory (OAM blocks, etc)
        return 0xFF;
    } else if (addr >= IO_REG_START && addr <= IO_REG_END) {
        return gizmo_io_registers_read(memory->sys, addr);
    } else if (addr >= HRAM_START && addr <= HRAM_END) {
        return memory->hram[addr - HRAM_START];
    } else { // Interrupt Enable Register
        return memory->sys->interrupts->ie;
    }
}

void gizmo_memory_write8(gizmo_memory_t *memory, uint16_t addr, uint8_t value) {
    if (addr >= ROM_BANK_0_START && addr <= ROM_BANK_N_END) { // 0x0000 - 0x7FFF
        gizmo_cartridge_write(memory->sys->cartridge, addr, value);
    } else if (addr >= VRAM_START && addr <= VRAM_END) { // 0x8000 - 9FFF
        // TODO: Implement write for VRAM
    } else if (addr >= ERAM_START && addr <= ERAM_END) { // 0xA000 - 0xBFFF
        gizmo_cartridge_write(memory->sys->cartridge, addr, value);
    } else if (addr >= WRAM_START && addr <= WRAM_END) { // 0xC000 - 0xDFFF
        memory->wram[addr - WRAM_START] = value;
    } else if (addr >= ECHO_START && addr <= ECHO_END) { // 0xE000 - 0xFDFF
        memory->wram[addr - ECHO_START] = value;
    } else if (addr >= OAM_START && addr <= OAM_END) {
        // TODO: Implement OAM write
    } else if (addr >= UNUSABLE_START && addr <= UNUSABLE_END) {
        // TODO: Implement the unusable section of memory (OAM blocks, etc)
    } else if (addr >= IO_REG_START && addr <= IO_REG_END) {
        return gizmo_io_registers_write(memory->sys, addr, value);
    } else if (addr >= HRAM_START && addr <= HRAM_END) {
        memory->hram[addr - HRAM_START] = value;
    } else { // Interrupt Enable Register
        memory->sys->interrupts->ie = value;
    }
}

uint16_t gizmo_memory_read16(gizmo_memory_t *memory, uint16_t addr) {
    uint16_t low = (uint16_t)gizmo_memory_read8(memory, addr);
    uint16_t high = (uint16_t)gizmo_memory_read8(memory, addr + 1);
    return (high << 8) | low;
}

void gizmo_memory_write16(gizmo_memory_t *memory, uint16_t addr, uint16_t value) {
    uint8_t low = (uint8_t)(value & 0xFF);
    uint8_t high = (uint8_t)((value >> 8) & 0xFF);
    gizmo_memory_write8(memory, addr, low);
    gizmo_memory_write8(memory, addr + 1, high);
}
