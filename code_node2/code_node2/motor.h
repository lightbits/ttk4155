// * Connect Analog Out 2 (I/O board) to MJEX.GND (upper-left on motorbox)
// * Connect Analog Out 1 (I/O board) to MJEX.DA1 (lower-left on motorbox)
// * Connect Port H (MJ1 on shield) to MJ1 (motorbox)
// * Connect Port K (MJ2 shield) to MJ2 (motorbox)
// * Connect I2C pins on the arduino to the MAX520 DAC by connecting
// "I2C" jumper (shield) to "I2C" jumper (I/O board), matching SDA and SCL.
// * Ensure that AD0, AD1 and AD2 on the MAX520 are grounded by connecting
// the pins 1-2, 3-4, 5-6 together on JP2 "DAC ADDR" on the I/O board.

#ifndef MOTOR_H
#define MOTOR_H
#include "common.h"
#define MOTOR_PORT    PORTH
#define MOTOR_DDR     DDRH
#define MOTOR_PIN_RST PH6
#define MOTOR_PIN_OE  PH5
#define MOTOR_PIN_EN  PH4
#define MOTOR_PIN_SEL PH3
#define MOTOR_PIN_DIR PH1
#define ENCODER_DDR   DDRK
#define ENCODER_INPUT PINK
#define MAX520_ADDRESS 0b0101000 // Assumes AD0,AD1,AD2 are grounded
void    motor_init();
void    motor_reset();
int16_t motor_read_encoder();
void    motor_velocity(int16_t velocity);
#endif
