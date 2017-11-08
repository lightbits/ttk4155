#ifndef MOTOR_H
#define MOTOR_H
#include "common.h"
void motor_init();
int16_t motor_read_encoder();
void motor_velocity(int16_t velocity);
#endif
