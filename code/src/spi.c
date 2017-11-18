// This enables SPI on the ATmega162 to communicate with the MCP2515
// and the NRF. Polarity and Phase are 0,0. Rate is F_CPU/16.
// See page 160 for example code which the below is based on.
#include "../../spi.h"
#include "common.h"
#define SPI_SS   PB4  // This must be set as output for SPI to work.
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK  PB7
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

