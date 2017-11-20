#ifndef TIMER_H
#include "common.h"
void timer_start();
uint32_t timer_ms_elapsed();
// Returns the number of milliseconds since the call to timer_start.

// Note:
// Uses Timer/Counter1
// Uses interrupts
// Counts at approximately 1 ms intervals
#endif
