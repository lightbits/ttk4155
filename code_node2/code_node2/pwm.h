// This enables PWM signal generation on PB6/OC1B on the arduino.
// The prescaler used is hardcoded to 8, meaning that the maximum
// freqency is 2MHz (F_CPU/8) and the minimum frequency is 30 Hz
// (TOP = 65535).
#ifndef PWM_H
#define PWM_H
#include "common.h"
void pwm_init(uint32_t frequency); // between 30 and 2 000 000
void pwm_duty(float duty_cycle); // between 0.0f and 1.0f
void pwm_pulse_duration(float seconds);
void pwm_pulse_duration_ms(float milliseconds);
#endif
