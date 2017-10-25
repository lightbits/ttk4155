#ifndef PWM_H_
#define PWM_H_
#include "common.h"

void pwm_init(uint32_t frequency); // frequency is between 0 and 2 000 000 MHz (F_CPU / 8)
void pwm_duty(float duty_cycle); // duty cycle is between 0.0 and 1.0
void pwm_pulse_duration(float seconds);
void pwm_pulse_duration_ms(float milliseconds);

#endif