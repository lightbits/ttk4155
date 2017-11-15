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

	// Set pin as output (see pinout overview)
	set_bit(DDRB, DDD6);

	// Hardcode N value to be 8 (this divides clock frequency by 8)
	clear_bit(TCCR1B, CS12);
	set_bit(TCCR1B, CS11);
	clear_bit(TCCR1B, CS10);

	// Set TOP value
	uint16_t TOP = (uint16_t)( (F_CPU/8)/frequency - 1);
	OCR1A = TOP;
}

void pwm_duty(float duty_cycle)
{
	OCR1B = (uint16_t)((1.0f-duty_cycle)*OCR1A);
}

void pwm_pulse_duration(float seconds)
{
	uint32_t TOP = (uint32_t)OCR1A;
	uint32_t frequency = F_CPU/(8*(1+TOP));
	pwm_duty(seconds*frequency);
}

void pwm_pulse_duration_ms(float milliseconds)
{
	pwm_pulse_duration(milliseconds/1000.0f);
}
