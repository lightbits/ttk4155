// This enables SPI on the ATmega2560 to communicate with the MCP2510
// on the I/O board. Polarity and Phase are 0,0. Rate is F_CPU/16.
// See page 193 for example code which the below is based on.
#include "../../spi.h"
#include "common.h"
#define SPI_MISO   PB3
#define SPI_MOSI   PB2
#define SPI_SCK    PB1
#define SPI_SS     PB0 // Page 195: This must be set as output for SPI to work.
void spi_init()
{
    DDRB = (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
    SPCR = (1<<MSTR) | (1<<SPR0);
    SPCR |= (1<<SPE); // For some reason we need to |= this in after the above.
}
uint8_t spi_write(uint8_t data)
{
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}
uint8_t spi_read()
{
    return spi_write(0xDC);
}
