#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "pwm.h"
#include "motor.h"

void test_mcp()
{
	uart_init(9600);
	SPI_init();
	mcp_reset();
	printf("Testing mcp...\n");
	while (1)
	{
		// The CANCTRL register can be read and written to freely,
		// so we check if it works by writing some binary value and
		// seeing if the value we then read matches.
		uint8_t byte_written = 0b01001011;
		mcp_write(MCP_CANCTRL, byte_written);
		uint8_t byte_read = mcp_read(MCP_CANCTRL);
		printf("Wrote: %d\tGot: %d\n", byte_written, byte_read);
		_delay_ms(100);
	}
}

void test_can_loopback()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_loopback();
	printf("Testing can...\n");
	while (1)
	{
		uint16_t sent_id = 42;
		uint8_t sent_data[] = { 1, 2, 3, 4, 5 };
		uint8_t sent_length = 5;
		mcp_send_message(sent_id, sent_data, sent_length);
		printf("sent message\n");

		_delay_ms(2000);

		uint16_t read_id;
		uint8_t read_data[8];
		uint8_t read_length;
		if (mcp_read_message(&read_id, read_data, &read_length))
		{
			printf("got message\n");
			printf("  id: %d\n", read_id);
			printf("  data: ");
			for (int i = 0; i < read_length; i++)
			printf("%x ", read_data[i]);
			printf("\n");
			printf("  length: %d\n", read_length);
		}

		_delay_ms(2000);
	}
}

void test_can_between_nodes()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	printf("Testing can between nodes...\n");
	while (1)
	{
		printf("(node 2) waiting for message...\n");

		uint16_t read_id;
		uint8_t read_data[8];
		uint8_t read_length;
		while (!mcp_read_message(&read_id, read_data, &read_length))
		{
			// wait for message
		}
		printf("(node 2) got message\n");
		printf("  id: %d\n", read_id);
		printf("  data: ");
		for (int i = 0; i < read_length; i++)
		printf("%x ", read_data[i]);
		printf("\n");
		printf("  length: %d\n", read_length);

		{
			printf("(node 2) sending message...\n");
			uint16_t sent_id = 22;
			uint8_t sent_data[] = { 1, 2, 3, 4, 5 };
			uint8_t sent_length = 5;
			mcp_send_message(sent_id, sent_data, sent_length);
		}
	}
}

void test_can_and_joystick()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	printf("(node 2) Testing can and joystick...\n");
	while (1)
	{
		uint16_t id;
		uint8_t data[8];
		uint8_t length;
		while (!mcp_read_message(&id, data, &length)) { }
		uint8_t joy_x = data[0];
		uint8_t joy_y = data[1];
		uint8_t slider = data[2];

		printf("(node 2) %d %d %d\n", joy_x, joy_y, slider);
	}
}

void servo_position(float x) // x is between 0 and 1
{
	float ms = 0.9 + (2.1-0.9)*x;
	if (ms < 0.9) ms = 0.9;
	if (ms > 2.1) ms = 2.1;
	pwm_pulse_duration_ms(ms);
}

void test_pwm()
{
	uart_init(9600);
	printf("Testing pwm!");
	pwm_init(50);
	servo_position(0);
	while (1)
	{

	}
}

// this will read the voltage connected to ADC channel on pin
void test_ir_adc()
{
	uart_init(9600);
	printf("testing IR and adc\n");

	ADCSRA = (1 << ADEN);

	// Use AVCC as voltage source
	ADMUX = (1 << REFS0);

	// ADC0 is source channel by default

	const int num_past_values = 20;
	uint16_t past_values[num_past_values];

	int score = 0;
	int was_under_threshold = 0;

	while (1)
	{
		set_bit(ADCSRA, ADSC); // Start conversion
		while (test_bit(ADCSRA, ADSC)) ; // wait until done

		uint16_t x = ADC;

		for (int i = 0; i < num_past_values - 1; i++)
			past_values[i] = past_values[i+1];
		past_values[num_past_values-1] = x;

		uint16_t sum = 0;
		for (int i = 0; i < num_past_values; i++)
			sum += past_values[i];
		uint16_t avg = sum / num_past_values;

		if (avg < 10)
		{
			if (was_under_threshold) { }
			else
			{
				score += 1;
				was_under_threshold = 1;
			}
		}
		else
		{
			was_under_threshold = 0;
		}


		printf("%d %d\n", avg, score);

		_delay_ms(100);
	}
}

void test_can_joystick_servo()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	pwm_init(50);
	printf("(node 2) Testing servo control with joystick via CAN...\n");

	while (1)
	{
		uint16_t id;
		uint8_t data[8];
		uint8_t length;
		while (!mcp_read_message(&id, data, &length)) { }
		uint8_t joy_x = data[0];
		uint8_t joy_y = data[1];
		uint8_t slider = data[2];

		float position = (float)(joy_x-28)/255;
		servo_position(position);

		printf("(node 2) %d %d %d\n", joy_x, joy_y, slider);
	}
}

void test_motor()
{
	uart_init(9600);
	printf("Testing motor...\n");
	motor_init();

	int16_t x = 70;
	while (1)
	{
		printf("Sending %d\n", x);
		motor_velocity(x);
		int16_t encoder = motor_read_encoder();
		printf("Encoder: %d\n", encoder);
		_delay_ms(500);
	}
}

#define SOLENOID_PORT PORTB
#define SOLENOID_DDR  DDRB
#define SOLENOID_PIN  PB4
void test_solenoid()
{
	uart_init(9600);
	printf("Testing solenoid...\n");
	set_bit(SOLENOID_DDR, PB4);
	while (1)
	{
		set_bit(SOLENOID_PORT, SOLENOID_PIN);
		_delay_ms(20);
		clear_bit(SOLENOID_PORT, SOLENOID_PIN);
		_delay_ms(20);
		set_bit(SOLENOID_PORT, SOLENOID_PIN);
		_delay_ms(1000);
	}
}

void test_motor_with_joystick()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	printf("Testing motor with joystick...\n");
	motor_init();

	motor_velocity(0);

	#if 1
	while (1) ;
	#else
	const int32_t ENCODER_MAX = 6000;
	for (uint16_t i = 0; ; i++)
	{
		// read joystick and slider from CAN message
		uint8_t joy_x,joy_y,slider;
		{
			uint16_t id;
			uint8_t data[8];
			uint8_t length;
			while (!mcp_read_message(&id, data, &length)) { }
			joy_x = data[0];
			joy_y = data[1];
			slider = data[2];
		}

		int32_t desired_position = ENCODER_MAX*(int32_t)slider/255;
		int32_t actual_position = motor_read_encoder();
		
		{
			int32_t band = 1000;
			int32_t error = (desired_position - actual_position);
			if (error > band)
				motor_velocity(80);
			else if (error < -band)
				motor_velocity(-80);
			else
			{
				if (error > 0)
					motor_velocity(30 + (40*error)/band);
				else
					motor_velocity(-30 + (40*error)/band);
			}
		}

		if (i % 10 == 0)
		{
			printf("%d %d\n", (int)desired_position, (int)actual_position);
		}

		_delay_ms(1);
	}
	#endif
}

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

		// Hardcode N value to be 8 (this divides clock frequency by 8)
		const uint32_t N = 1024;
		set_bit(TCCR3B, CS32);
		clear_bit(TCCR3B, CS31);
		set_bit(TCCR3B, CS30);

		// Set TOP value
		uint16_t TOP = (uint16_t)( (F_CPU/N)/frequency - 1);
		OCR3A = TOP;
	}
}

void test_song()
{
	uart_init(9600);
	printf("Testing music!");

	#define NOTE_B0  31
	#define NOTE_C1  33
	#define NOTE_CS1 35
	#define NOTE_D1  37
	#define NOTE_DS1 39
	#define NOTE_E1  41
	#define NOTE_F1  44
	#define NOTE_FS1 46
	#define NOTE_G1  49
	#define NOTE_GS1 52
	#define NOTE_A1  55
	#define NOTE_AS1 58
	#define NOTE_B1  62
	#define NOTE_C2  65
	#define NOTE_CS2 69
	#define NOTE_D2  73
	#define NOTE_DS2 78
	#define NOTE_E2  82
	#define NOTE_F2  87
	#define NOTE_FS2 93
	#define NOTE_G2  98
	#define NOTE_GS2 104
	#define NOTE_A2  110
	#define NOTE_AS2 117
	#define NOTE_B2  123
	#define NOTE_C3  131
	#define NOTE_CS3 139
	#define NOTE_D3  147
	#define NOTE_DS3 156
	#define NOTE_E3  165
	#define NOTE_F3  175
	#define NOTE_FS3 185
	#define NOTE_G3  196
	#define NOTE_GS3 208
	#define NOTE_A3  220
	#define NOTE_AS3 233
	#define NOTE_B3  247
	#define NOTE_C4  262
	#define NOTE_CS4 277
	#define NOTE_D4  294
	#define NOTE_DS4 311
	#define NOTE_E4  330
	#define NOTE_F4  349
	#define NOTE_FS4 370
	#define NOTE_G4  392
	#define NOTE_GS4 415
	#define NOTE_A4  440
	#define NOTE_AS4 466
	#define NOTE_B4  494
	#define NOTE_C5  523
	#define NOTE_CS5 554
	#define NOTE_D5  587
	#define NOTE_DS5 622
	#define NOTE_E5  659
	#define NOTE_F5  698
	#define NOTE_FS5 740
	#define NOTE_G5  784
	#define NOTE_GS5 831
	#define NOTE_A5  880
	#define NOTE_AS5 932
	#define NOTE_B5  988
	#define NOTE_C6  1047
	#define NOTE_CS6 1109
	#define NOTE_D6  1175
	#define NOTE_DS6 1245
	#define NOTE_E6  1319
	#define NOTE_F6  1397
	#define NOTE_FS6 1480
	#define NOTE_G6  1568
	#define NOTE_GS6 1661
	#define NOTE_A6  1760
	#define NOTE_AS6 1865
	#define NOTE_B6  1976
	#define NOTE_C7  2093
	#define NOTE_CS7 2217
	#define NOTE_D7  2349
	#define NOTE_DS7 2489
	#define NOTE_E7  2637
	#define NOTE_F7  2794
	#define NOTE_FS7 2960
	#define NOTE_G7  3136
	#define NOTE_GS7 3322
	#define NOTE_A7  3520
	#define NOTE_AS7 3729
	#define NOTE_B7  3951
	#define NOTE_C8  4186
	#define NOTE_CS8 4435
	#define NOTE_D8  4699
	#define NOTE_DS8 4978

	int song[] = {
		NOTE_E7, NOTE_E7, 0, NOTE_E7,
		0, NOTE_C7, NOTE_E7, 0,
		NOTE_G7, 0, 0,  0,
		NOTE_G6, 0, 0, 0,

		NOTE_C7, 0, 0, NOTE_G6,
		0, 0, NOTE_E6, 0,
		0, NOTE_A6, 0, NOTE_B6,
		0, NOTE_AS6, NOTE_A6, 0,
		
		NOTE_G6, NOTE_E7, NOTE_G7,
		NOTE_A7, 0, NOTE_F7, NOTE_G7,
		0, NOTE_E7, 0, NOTE_C7,
		NOTE_D7, NOTE_B6, 0, 0,
		
		NOTE_C7, 0, 0, NOTE_G6,
		0, 0, NOTE_E6, 0,
		0, NOTE_A6, 0, NOTE_B6,
		0, NOTE_AS6, NOTE_A6, 0,
		
		NOTE_G6, NOTE_E7, NOTE_G7,
		NOTE_A7, 0, NOTE_F7, NOTE_G7,
		0, NOTE_E7, 0, NOTE_C7,
		NOTE_D7, NOTE_B6, 0, 0
	};

	int num_notes = (int)(sizeof(song) / sizeof(song[0]));

	while(1){
		_delay_ms(2000);
		for (int i = 0; i < num_notes; i++){
			if (song[i] == 0){
				wave_frequency(0);
				_delay_ms(100);
			}
			else {
				wave_frequency(song[i]);
				_delay_ms(100);
				wave_frequency(0);
				_delay_ms(50);
			}
		}
	}
}

int main(void)
{
	// uart_test();
	// test_mcp();
	// test_can_loopback();
	// test_can_between_nodes();
	// test_can_and_joystick();
	// test_pwm();
	// test_can_joystick_servo();
	// test_ir_adc();
	// test_motor();
	// test_solenoid();
	// test_motor_with_joystick();
	test_song();
}
