#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef TIMER_CLOCK_DIVISOR
#error "You must define TIMER_CLOCK_DIVISOR (one of 1,8,64,256 or 1024)"
#endif
#ifndef TIMER_n
#error "You must define TIMER_n (one of 1,3,4 and 5 ... for ATmega2560)"
#endif

typedef void (*timer_callback_t)(void);
void timer_do_after_milliseconds(timer_callback_t f, uint16_t t);

// When called, timer_do_after_milliseconds will repeatedly execute f
// at intervals of duration t. The maximum possible duration is given
// by F_CPU and the chosen clock divisor, by how long it takes to count
// to 65536:
//
//   duration     = t / F_CPU/DIVISOR
//   max duration = 65536 / F_CPU/DIVISOR
//
// For example, with F_CPU=16MHz we have the following possible ranges:
//   Divisor          Range
//         1       4.096 ms
//         8      32.768 ms
//        64     262.144 ms
//       256    1048.576 ms
//      1024    4194.304 ms
//
// The granularity depends on how wide your range is. For example, you
// will not be able to sleep exactly 32.0 ms with a divisor of 1024 at
// 16 MHz, since the tick value is 509.96, which gets rounded to 509,
// or 32.58 ms.
//

//
// Implementation
//

#define n TIMER_n

volatile timer_callback_t timer_callback = 0;

// see nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
// for other interrupt vector names
ISR(TIMER##n_COMPA_vect)
{
    timer_callback();
}

void timer_do_after_milliseconds(timer_callback_t callback, uint16_t milliseconds)
{
    timer_callback = callback;

    // Enable Clear Timer on Compare Match (CTC) with OCRnA as TOP
    clear_bit(TCCR##nB, WGM##n3);
    set_bit(TCCR##nB, WGM##n2);
    clear_bit(TCCR##nA, WGM##n1);
    clear_bit(TCCR##nA, WGM##n0);

    // Enable global interrupts
    sei();

    // Enable interrupt on Compare Match A (since we use OCRnA)
    set_bit(TIMSK##n, OCIE##nA); // set_bit(TIMSKn, OCIEnA);

    // Set duration with TOP value
    // (I think we're not rounding badly or overflowing?)
    uint32_t ms_32 = (uint32_t)milliseconds;
    uint32_t fr_32 = F_CPU/TIMER_CLOCK_DIVISOR;
    uint16_t TOP = (uint16_t)( (ms_32*fr_32)/1000 - 1 );
    OCR1A = TOP; // OCRnA

    // Start clock
    #if TIMER_CLOCK_DIVISOR==1
    TCCR##nB = (TCCR##nB & 0b11111000) | 0b001;
    #elif TIMER_CLOCK_DIVISOR==8
    TCCR##nB = (TCCR##nB & 0b11111000) | 0b010;
    #elif TIMER_CLOCK_DIVISOR==64
    TCCR##nB = (TCCR##nB & 0b11111000) | 0b011;
    #elif TIMER_CLOCK_DIVISOR==256
    TCCR##nB = (TCCR##nB & 0b11111000) | 0b100;
    #elif TIMER_CLOCK_DIVISOR==1024
    TCCR##nB = (TCCR##nB & 0b11111000) | 0b101;
    #else
    #error "TIMER_CLOCK_DIVISOR must be one of 1,8,64,256 or 1024"
    #endif
}

#undef n
