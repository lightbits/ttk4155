#include <avr/io.h>
#include "spi.h"

#define SPI_SS PB7
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK PB1


int SPI_init(void) {
	// Set MOSI, SCK and SS output, all others input
	// note: we need to enable pb0 as output even though we use pb7 as ss
	// because arduino requires the SPI SS pin to be an output
	DDRB = (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS) | (1<<PB0);
	
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<MSTR) | (1<<SPR0);
	SPCR |= (1<<SPE);
	
	return 0;
}


int SPI_write(char data) {
 	// Start transmission
 	SPDR = data;

 	// Wait for transmission complete
 	while(!(SPSR & (1<<SPIF)));

 	return 0;
}


uint8_t SPI_read(void) {
 	// Wait reception complete
	 SPDR = 0xDC;
 	while(!(SPSR & (1<<SPIF)));

	// Return data register
 	return SPDR;
}


void SPI_slave_select(void) {
 	// Set !SS to 0 for activation of slave selection
 	clear_bit(PORTB, SPI_SS);
}


void SPI_slave_deselect(void) {
	// Set !SS to 1 to deactivation of slave selection
 	set_bit(PORTB, SPI_SS);
}
