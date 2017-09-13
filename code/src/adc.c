#include "adc.h"

// channel is one of 0 (ch1), 1 (ch2), 2 (ch3), 3 (ch4)
uint8_t adc_read(int channel)
{
    volatile uint8_t *ADC = (uint8_t*)0x1400; // should maybe be global const
    uint8_t mux_address = 4+channel;
    *ADC = mux_address;
    _delay_us(50); // Maximum conversion time is 40 microseconds (t_c)
                   // let's wait a bit longer than that...
    uint8_t value = *ADC;
    return value;
}

void adc_test()
{
    uart_init(9600);
    ext_mem_init();
    printf("Starting adc test...\n");
    while (1)
    {
        uint8_t ch1 = adc_read(0);
        uint8_t ch2 = adc_read(1);
        uint8_t ch3 = adc_read(2);
        uint8_t ch4 = adc_read(3);
        printf("%d %d %d %d\n", ch1, ch2, ch3, ch4);
        _delay_ms(100);
    }
}
