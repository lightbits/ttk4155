// This enables PWM output on PB6/OC1B on the ATmega2560.
// The range of acceptable frequencies depends on PWM_CLOCK_DIVISOR
// (one of 1, 8, 256 or 1024). See note below.
#ifndef PWM_H
#define PWM_H
#ifndef PWM_CLOCK_DIVISOR
#define PWM_CLOCK_DIVISOR 8
#endif
#include "common.h"
void pwm_init(uint32_t frequency); // between 30 and 2 000 000
void pwm_duty(float duty_cycle); // between 0.0f and 1.0f
void pwm_pulse_duration(float seconds);
void pwm_pulse_duration_ms(float milliseconds);
#endif

//
//                    F_CPU = 16 MHz
//    N  | Min frequency | Max frequency |  Max period |
// ------+---------------+---------------+-------------+
//    1  |     244 Hz    |       16 MHz  |    4.096 ms |
//    8  |    30.5 Hz    |        2 MHz  |   32.768 ms |
//   64  |    3.81 Hz    |     0.25 MHz  |  262.144 ms |
//  256  |    0.95 Hz    |     62.5 kHz  | 1048.576 ms |
// 1024  |    0.24 Hz    |     15.6 kHz  | 4194.304 ms |
//
// To generate a PWM signal the MCU has a counter that goes from 0 to TOP.
// When the counter is above a set threshold, the output is 1, and otherwise
// 0. The duty cycle (0-100%) can then be adjusted by varying this threshold
// between 0 and TOP.
//
// The period of the signal (or its frequency) is defined by the clock
// (how fast to count) and TOP (how long to count). The clock source can
// be divided by N=1, 8, 64, 256 or 1024. In other words:
//
//   frequency = (F_CPU/N)/TOP
//
// You choose N such that the TOP is between 0 and 65535 for frequencies in
// the range you are interested in. For a given N, the frequency range is
//   min = (F_CPU/N)/65535
//   max = F_CPU/N
//
