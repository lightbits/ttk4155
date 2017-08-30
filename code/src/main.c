#define F_CPU 4915200
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))

// see atmega162 page 174
void uart_send_byte(uint8_t data)
{
	// wait until transmit buffer is ready to receive new data
	while (!test_bit(UCSR0A, UDRE0)) { }

	// put data into the buffer
	UDR0 = data;
}

// see atmega162 page 
uint8_t uart_recv_byte()
{
	// wait until a byte has been received
	while (!test_bit(UCSR0A, RXC0)) { }

	return UDR0;
}

int printf_put(char c, FILE *file)
{
	uart_send_byte(c);
}

int printf_get(FILE *file)
{	
	return uart_recv_byte();
}

// see Atmega162 page 172
void uart_initialize()
{
	uint32_t baud_rate = 9600;
	uint32_t ubrr = F_CPU / (16*baud_rate) - 1;

	// set baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);

	// enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// set frame format (8 data bits, 2 stop bits, no parity)
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

int main (void)
{
	// TEST PROGRAM: SET AND UNSET PD1
	/*
	set_bit(DDRD, DDD1); // Set pin 1 of port D to output
	while (1) 
	{
		set_bit(PORTD, PD1);
		_delay_ms(100);
		clear_bit(PORTD, PD1);
		_delay_ms(100);
	}
	*/

	// UART DRIVER
	#if 1
	fdevopen(printf_put, printf_get);
	uart_initialize();
	while (1)
	{
		printf("Enter a value: ");
		uint8_t x = uart_recv_byte();
		printf("\nYou wrote: %c\n", x);
		_delay_ms(1000);
	}
	#endif
}
