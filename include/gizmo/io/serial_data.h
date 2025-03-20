
#ifndef GIZMO_IO_SERIAL_DATA_H
#define GIZMO_IO_SERIAL_DATA_H

#include "stdint.h"

typedef struct {
    int8_t serial_data;
    int8_t serial_transfer_control;
} gizmo_io_serial_data_t;

#endif