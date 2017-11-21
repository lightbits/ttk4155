#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// For F_CPU=4915200 and DIVISOR=1 an interval of 1 ms will be
// rounded to 0.99996 ms.
#define TIMER_CLOCK_DIVISOR 1
#define TIMER_TICK_DURATION_MS 1
volatile uint32_t _timer_ms_elapsed = 0;
uint32_t timer_ms_elapsed() { return _timer_ms_elapsed; }

// See http://nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
ISR(TIMER1_COMPA_vect) { _timer_ms_elapsed += TIMER_TICK_DURATION_MS; }

void timer_start()
{
    _timer_ms_elapsed = 0;

    // Enable Clear Timer on Compare Match (CTC) with OCR1A as TOP
    clear_bit(TCCR1B, WGM13);
    set_bit(TCCR1B, WGM12);
    clear_bit(TCCR1A, WGM11);
    clear_bit(TCCR1A, WGM10);

    // Enable global interrupts
    sei();

    // Enable interrupt on Compare Match A (since we use OCR1A)
    set_bit(TIMSK, OCIE1A);

    // Set duration with TOP value

    uint32_t frequency = F_CPU/TIMER_CLOCK_DIVISOR;
    uint16_t TOP = (uint16_t)( (TIMER_TICK_DURATION_MS*frequency)/1000 - 1 );
    OCR1A = TOP;

    #if TIMER_CLOCK_DIVISOR==1
    TCCR1B = (TCCR1B & 0b11111000) | 0b001; // F_CPU/1
    #elif TIMER_CLOCK_DIVISOR==8
    TCCR1B = (TCCR1B & 0b11111000) | 0b010; // F_CPU/8
    #elif TIMER_CLOCK_DIVISOR==64
    TCCR1B = (TCCR1B & 0b11111000) | 0b011; // F_CPU/64
    #elif TIMER_CLOCK_DIVISOR==256
    TCCR1B = (TCCR1B & 0b11111000) | 0b100; // F_CPU/256
    #elif TIMER_CLOCK_DIVISOR==1024
    TCCR1B = (TCCR1B & 0b11111000) | 0b101; // F_CPU/1024
    #else
    #error "TIMER_CLOCK_DIVISOR must be one of 1,8,64,256 or 1024"
    #endif
}
