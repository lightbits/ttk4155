#ifndef COMMON_H
#define COMMON_H
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h> // rand
#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))

#define OLED_COMMAND_MEMORY_START 0x1000
#define OLED_DATA_MEMORY_START    0x1200
#define ADC_MEMORY_START          0x1400
#define SRAM_MEMORY_START         0x1800

#define ADC_CHANNEL_JOY_X 0
#define ADC_CHANNEL_JOY_Y 1
#define ADC_CHANNEL_JOY_B 2
#define ADC_CHANNEL_TOUCH 3

#endif
