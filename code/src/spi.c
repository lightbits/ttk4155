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

