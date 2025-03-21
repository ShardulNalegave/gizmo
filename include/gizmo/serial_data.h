
#ifndef GIZMO_IO_SERIAL_DATA_H
#define GIZMO_IO_SERIAL_DATA_H

#include "stdint.h"

typedef struct {
    uint8_t serial_data;                // SB - 0xFF01
    uint8_t serial_transfer_control;    // SC - 0xFF02
} gizmo_io_serial_data_t;

#endif