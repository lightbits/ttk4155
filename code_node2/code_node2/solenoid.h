// Connect SOLENOID_PIN (e.g. PB4) to an external transistor as shown in
// figure 18 in assignment.pdf.
#ifndef SOLENOID_H
#define SOLENOID_H
#include "common.h"
#define SOLENOID_PORT PORTB
#define SOLENOID_DDR  DDRB
#define SOLENOID_PIN  PB4
void solenoid_init() { set_bit(SOLENOID_DDR, SOLENOID_PIN); }
void solenoid_pull() { set_bit(SOLENOID_PORT, SOLENOID_PIN); }
void solenoid_push() { clear_bit(SOLENOID_PORT, SOLENOID_PIN); }
#endif
