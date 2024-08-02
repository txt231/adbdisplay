#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void platform_init();

extern bool serial_rx_avail();
extern size_t serial_rx_read(uint8_t* pData, size_t len);
