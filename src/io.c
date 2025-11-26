
#include "gizmo/io.h"
#include "gizmo/system.h"
#include "gizmo/joypad.h"
#include "gizmo/serial.h"
#include "gizmo/timer.h"
#include "gizmo/interrupts.h"

uint8_t gizmo_io_registers_read(gizmo_system_t *sys, uint16_t addr) {
    if (addr == JOYPAD_REG) {
        return gizmo_joypad_read(sys->joypad);
    } else if (addr == SERIAL_DATA || addr == SERIAL_CONTROL) {
        // TODO: Implement serial read
        return 0xFF;
    } else if (addr >= TIMER_DIV && addr <= TIMER_TAC) {
        return gizmo_timer_read(sys->timer, addr);
    } else if (addr == INT_FLAG_REG) {
        return sys->interrupts->if_;
    } else {
        return 0xFF;
    }
}

void gizmo_io_registers_write(gizmo_system_t *sys, uint16_t addr, uint8_t value) {
    if (addr == JOYPAD_REG) {
        gizmo_joypad_write(sys->joypad, value);
    } else if (addr == SERIAL_DATA || addr == SERIAL_CONTROL) {
        // TODO: Implement serial write
        return;
    } else if (addr >= TIMER_DIV && addr <= TIMER_TAC) {
        gizmo_timer_write(sys->timer, addr, value);
    } else if (addr == INT_FLAG_REG) {
        sys->interrupts->if_ = value;
    } else {
        return; // ignore
    }
}
