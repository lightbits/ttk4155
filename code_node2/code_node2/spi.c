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
	set_bit(DDRB, SPI_MOSI);
	set_bit(DDRB, SPI_SCK);
	set_bit(DDRB, SPI_SS);
	set_bit(SPCR, MSTR); // Master mode
	set_bit(SPCR, SPR0); // F_CPU / 16
	set_bit(SPCR, SPE); // Enable SPI
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
