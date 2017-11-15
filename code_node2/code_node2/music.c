#include "music.h"

void wave_frequency(uint32_t frequency)
{
	if (frequency == 0)
	{
		clear_bit(DDRE, 3);
	}
	else
	{
		// Enable PWM on PE3/OC3A

		// Enable Fast PWM with OCRnA used to define TOP
		set_bit(TCCR3B, WGM33);
		set_bit(TCCR3B, WGM32);
		set_bit(TCCR3A, WGM31);
		set_bit(TCCR3A, WGM30);

		clear_bit(TCCR3A, COM3A1);
		set_bit(TCCR3A, COM3A0);

		// Set pin as output (see pinout overview)
		set_bit(DDRE, 3);

		// Hardcode N value to be 1024
		clear_bit(TCCR3B, CS32);
		set_bit(TCCR3B, CS31);
		clear_bit(TCCR3B, CS30);

		// Set TOP value
		uint16_t TOP = (uint16_t)( (F_CPU/8)/frequency - 1);
		OCR3A = TOP;
	}
}