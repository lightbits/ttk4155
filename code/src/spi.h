#ifndef SPI_H_
#define SPI_H_
#include "common.h"

int SPI_init(void);
uint8_t SPI_write(char data);
uint8_t SPI_read(void);
void SPI_slave_select(void);
void SPI_slave_deselect(void);

#endif
