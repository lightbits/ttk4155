#include "uart.h"

// These functions are used to link the printf function
int printf_put(char c, FILE *file) { uart_send_byte(c); }
int printf_get(FILE *file) { return uart_read_byte(); }

void uart_init(uint32_t baud_rate)
{
    // link printf to the really slow send/read functions.
    fdevopen(printf_put, printf_get);

    // This is based on the example initialization code found
    // in the atmega2560 datasheet, page 206

    uint32_t ubrr = F_CPU / (16*baud_rate) - 1;

    // set baud rate
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)(ubrr);

    // enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // set frame format (8 data bits, 2 stop bits, no parity)
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void uart_send_byte(uint8_t data)
{
    // wait until transmit buffer is ready to receive new data
    while (!test_bit(UCSR0A, UDRE0)) { }

    // put data into the buffer
    UDR0 = data;
}

uint8_t uart_read_byte(void)
{
    // wait until a byte has been received
    while (!test_bit(UCSR0A, RXC0)) { }

    return UDR0;
}

void uart_test(void)
{
    uart_init(9600);
    while (1)
    {
        printf("Enter a value: ");
        uint8_t x = uart_read_byte();
        printf("\nYou wrote: %c\n", x);
        _delay_ms(1000);
    }
}
