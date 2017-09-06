#ifndef UART_H
#define UART_H
#include <avr/io.h> // for uint8_t (stdint.h)
#include "bitops.h"

// This sets up the UART controller with
// * 8 data bits, 2 stop bits, no parity.
// * baud_rate can be one of [9600, ...]
// And also links the printf function.
void uart_init(uint32_t baud_rate);

// This blocks program execution until data can be written
void uart_send_byte(uint8_t data);

// This blocks program execution until data can be read
uint8_t uart_read_byte();

// This will repeatedly send a message over UART
// wait for a response, and print the response back.
void uart_test();
#endif
