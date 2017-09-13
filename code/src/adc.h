// The ADC relies on external memory being enabled
// by calling ext_mem_init(); (see extmem.h).
// It is used to read the joystick and touch slider
// on the P1000 USB card.

#ifndef ADC_H
#define ADC_H
#include "common.h"
uint8_t adc_read(int channel);
#endif
