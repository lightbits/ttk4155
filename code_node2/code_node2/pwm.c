#include "pwm.h"

// This enables PWM signal generation on OC1B (PB6)
void pwm_init(uint32_t frequency)
{
	// Enable Fast PWM with OCRnA used to define TOP
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11);
	set_bit(TCCR1A, WGM10);

	// Enable non-inverting mode (table 17-4)
	set_bit(TCCR1A, COM1B1);
	set_bit(TCCR1A, COM1B0);

	// Set pin as output
	set_bit(DDRB, 6);

	// Set the clock divisor and start clock
	#define N PWM_CLOCK_DIVISOR
	#if N==1
	TCCR1B = (TCCR1B & 0b11111000) | 0b001; // F_CPU/1
	#elif N==8
	TCCR1B = (TCCR1B & 0b11111000) | 0b010; // F_CPU/8
	#elif N==64
	TCCR1B = (TCCR1B & 0b11111000) | 0b011; // F_CPU/64
	#elif N==256
	TCCR1B = (TCCR1B & 0b11111000) | 0b100; // F_CPU/256
	#elif N==1024
	TCCR1B = (TCCR1B & 0b11111000) | 0b101; // F_CPU/1024
	#else
	#error "PWM_CLOCK_DIVISOR must be one of 1,8,64,256 or 1024"
	#endif

	// Set TOP value
	uint16_t TOP = (uint16_t)( (F_CPU/PWM_CLOCK_DIVISOR)/frequency - 1);
	OCR1A = TOP;
}

void pwm_duty(float duty_cycle)
{
	OCR1B = (uint16_t)((1.0f-duty_cycle)*OCR1A);
}

void pwm_pulse_duration(float seconds)
{
	uint32_t TOP = (uint32_t)OCR1A;
	uint32_t frequency = F_CPU/(PWM_CLOCK_DIVISOR*(1+TOP));
	pwm_duty(seconds*frequency);
}

void pwm_pulse_duration_ms(float milliseconds)
{
	pwm_pulse_duration(milliseconds/1000.0f);
}
