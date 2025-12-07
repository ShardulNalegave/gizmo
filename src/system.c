
#include "gizmo/system.h"
#include "gizmo/cpu.h"
#include "gizmo/memory.h"

inline void gizmo_system_step(gizmo_system_t *sys) {
    gizmo_cpu_step(sys->cpu);
}

inline uint8_t gizmo_system_read8(gizmo_system_t *sys, uint16_t addr) {
    return gizmo_memory_read8(sys->memory, addr);
}

inline void gizmo_system_write8(gizmo_system_t *sys, uint16_t addr, uint8_t value) {
    return gizmo_memory_write8(sys->memory, addr, value);
}

inline uint16_t gizmo_system_read16(gizmo_system_t *sys, uint16_t addr) {
    return gizmo_memory_read16(sys->memory, addr);
}

inline void gizmo_system_write16(gizmo_system_t *sys, uint16_t addr, uint16_t value) {
    return gizmo_memory_write16(sys->memory, addr, value);
}
