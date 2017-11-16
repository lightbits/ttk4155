#ifndef SPI_H_
#define SPI_H_
#include "common.h"

int spi_init(void);
uint8_t spi_write(char data);
uint8_t spi_read(void);
void spi_slave_select(void);
void spi_slave_deselect(void);

#endif
