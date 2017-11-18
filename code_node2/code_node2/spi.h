#ifndef SPI_H
#define SPI_H
#include "common.h"
void spi_init();
uint8_t spi_write(uint8_t data);
uint8_t spi_read();
#endif
