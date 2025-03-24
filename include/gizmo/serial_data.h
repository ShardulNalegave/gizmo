
#ifndef GIZMO_IO_SERIAL_DATA_H
#define GIZMO_IO_SERIAL_DATA_H

#include "stdint.h"

typedef struct gizmo_io_serial_data_t gizmo_io_serial_data_t;

struct gizmo_io_serial_data_t {
    uint8_t serial_data;                // SB - 0xFF01
    uint8_t serial_transfer_control;    // SC - 0xFF02
};

#endif