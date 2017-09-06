#define F_CPU 4915200
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "bitops.h"
#include "uart.h"

// This will repeatedly set pin 1 of port D high and low
void test_clock()
{
	set_bit(DDRD, DDD1);
	while (1)
	{
		set_bit(PORTD, PD1);
		_delay_ms(100);
		clear_bit(PORTD, PD1);
		_delay_ms(100);
	}
}

int main (void)
{
	uart_test();
}
