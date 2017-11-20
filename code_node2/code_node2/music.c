#include "music.h"

void wave_frequency(uint32_t frequency)
{
	if (frequency == 0)
	{
		clear_bit(DDRE, 3);
	}
	else
	{

		// Enable Fast PWM with OCRnA used to define TOP
		set_bit(TCCR3B, WGM33);
		set_bit(TCCR3B, WGM32);
		set_bit(TCCR3A, WGM31);
		set_bit(TCCR3A, WGM30);

		// Enable toggling of OCnA on compare match
		clear_bit(TCCR3A, COM3A1);
		set_bit(TCCR3A, COM3A0);

		// Set OCnA pin as output
		set_bit(DDRE, 3);

		// Set the clock divisor and start clock
		#define N MUSIC_CLOCK_DIVISOR
		#define N 8
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
		#error "MUSIC_CLOCK_DIVISOR must be one of 1,8,64,256 or 1024"
		#endif

		uint16_t TOP = (uint16_t)( (F_CPU/N)/(2*frequency) - 1);
		OCR3A = TOP;

		#undef N
	}
}
