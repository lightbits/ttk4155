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
