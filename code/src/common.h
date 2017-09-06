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
#endif
