#ifndef SERVO_H
#define SERVO_H
#include "common.h"
#include "pwm.h"
void servo_init() { pwm_init(50); } // 50 Hz (20 ms period)
void servo_position(float x) // between 0 and 1
{
    float ms = 0.9 + (2.1-0.9)*x;
    if (ms < 0.9) ms = 0.9;
    if (ms > 2.1) ms = 2.1;
    pwm_pulse_duration_ms(ms);
}
#endif
