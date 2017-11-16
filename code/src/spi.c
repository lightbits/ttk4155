#include <avr/io.h>
#include "spi.h"

#define SPI_SS PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK PB7

void spi_init(void) {
	// Set MOSI, SCK and SS output, all others input
	DDRB = (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
	
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<MSTR) | (1<<SPR0);
	SPCR |= (1<<SPE);
}

uint8_t spi_write(char data) {
 	SPDR = data; // write byte and start transmission
 	while(!(SPSR & (1<<SPIF))); // wait until transmission is done
 	return SPDR; // return data that was shifted in simultaneously from slave
}

uint8_t spi_read(void) {
	return spi_write(0xDC); // write a dummy byte and return the slave data
}

void spi_slave_select(void) {
 	// Set !SS to 0 for activation of slave selection
 	clear_bit(PORTB, SPI_SS);
}


void spi_slave_deselect(void) {
	// Set !SS to 1 to deactivation of slave selection
 	set_bit(PORTB, SPI_SS);
}
