#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "pwm.h"
#include "motor.h"
#include "solenoid.h"
#include "servo.h"
#include "../../shared.h"
#include "music.h"
#include "music.c"

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

void test_servo()
{
	uart_init(9600);
	printf("Testing pwm!");
	servo_init();
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
	servo_init();
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

void test_solenoid()
{
	uart_init(9600);
	printf("Testing solenoid...\n");
	solenoid_init();
	solenoid_pull();
	while (1)
	{
		solenoid_push();
		_delay_ms(20);
		solenoid_pull();
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

void test_song()
{
	uart_init(9600);
	printf("Testing music!\n");

	#if 0
	int num_notes = (int)(sizeof(music_lost_frequency) / sizeof(music_lost_frequency[0]));
	int *frequency = music_lost_frequency;
	int *length = music_lost_length;
	int *delay = music_lost_delay;
	float multiplier_frequency = LOST_MULTIPLIER_FREQUENCY;
	float multiplier_length = LOST_MULTIPLIER_LENGTH;
	printf("%d\n", num_notes);
	#else
	uint8_t mode = MODE_PLAY;

	int num_notes = (int)(sizeof(music_frequency) / sizeof(music_frequency[0]));
	int *frequency = music_frequency;
	int *length = music_length;
	int *delay = music_delay;
	float multiplier_frequency = MARIO_MULTIPLIER_FREQUENCY;
	float multiplier_length = MARIO_MULTIPLIER_LENGTH;

	if (mode == MODE_LOST)
	{
		num_notes = (int)(sizeof(music_lost_frequency) / sizeof(music_lost_frequency[0]));
		frequency = music_lost_frequency;
		length = music_lost_length;
		delay = music_lost_delay;
		multiplier_frequency = LOST_MULTIPLIER_FREQUENCY;
		multiplier_length = LOST_MULTIPLIER_LENGTH;
	}
	#endif
	
	int counter = 0;
	int note = 0;

	#define MAIN_TICK_MS 5
	while(1){
		
		if (counter <= MAIN_TICK_MS) {
			wave_frequency(frequency[note]*multiplier_frequency);
		}

		if (counter >= length[note]*multiplier_length) {
			wave_frequency(0);
		}

		if (counter >= length[note]*multiplier_length + delay[note]*multiplier_length) {
			note++;
			counter = 0;
		}

		if (note == num_notes)
			note = 0;
		
		_delay_ms(MAIN_TICK_MS);
		counter += MAIN_TICK_MS;
	}
	#undef MAIN_TICK_MS
}

void the_game()
{
	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	motor_init();
	motor_velocity(0);
	servo_init();
	solenoid_init();
	solenoid_pull();

	printf("(node 2) OK\n");

	#define MAIN_TICK_MS 5

	while (1)
	{
		//
		// Read IR light (raw ADC voltage measurement)
		// Voltage is high when light is shining on the diode, and low otherwise
		//
		uint16_t ir_raw = 0;
		{
		    ADCSRA = (1 << ADEN); // Enable ADC
		    ADMUX = (1 << REFS0); // Use AVCC as voltage source
		    set_bit(ADCSRA, ADSC); // Start conversion
		    while (test_bit(ADCSRA, ADSC)) ; // wait until done
		    ir_raw = ADC;
		}

		//
		// Filter IR light into broken/not_broken signal
		//
		uint8_t light_broken = 0;
		{
		    #define num_past_values 20
		    static uint16_t past_values[num_past_values]; // todo: init to zero

		    // shift in latest measurement
		    for (int i = 0; i < num_past_values - 1; i++)
		        past_values[i] = past_values[i+1];
		    past_values[num_past_values-1] = ir_raw;

		    // compute average
		    uint16_t sum = 0;
		    for (int i = 0; i < num_past_values; i++)
		        sum += past_values[i];
		    uint16_t avg = sum / num_past_values;

		    // simple filter... the average is reacts slower than instant measurements
		    light_broken = (avg < 10) ? 1 : 0;
		}

		//
		// Poll game controls from node 1 over CAN
		//
		static uint8_t user_angle = 127;
		static uint8_t user_shoot = 0;
		static uint8_t user_position = 0;
		static uint8_t user_mode = MODE_MENU;
		{
		    uint16_t id;
		    uint8_t data[8];
		    uint8_t length;
		    if (mcp_read_message(&id, data, &length))
		    {
		        user_angle = data[0];
				user_position = data[1];
	        	user_shoot = data[2];
		        user_mode = data[3];
		    }
		}

		//
		// Send IR signal to node 1
		//
		{
		    uint16_t id = 1;
		    uint8_t data[] = { light_broken };
		    mcp_send_message(id, data, (uint8_t)sizeof(data));
		}

		if (user_mode == MODE_PLAY)
		{
			//
			// Control servo angle
			//
			{
				float position = (float)(user_angle-28)/255;
				servo_position(position);
			}

			//
			// Control motor position
			//
			{
				const int32_t ENCODER_MAX = 6000;
				int32_t desired_position = ENCODER_MAX*(int32_t)(256-user_position)/255;
				int32_t actual_position = motor_read_encoder();

				{
					int32_t band = 1000;
					int32_t error = (desired_position - actual_position);
					if (error > band)
						motor_velocity(100);
					else if (error < -band)
						motor_velocity(-100);
					else
					{
						if (error > 0)
							motor_velocity(30 + (40*error)/band);
						else
							motor_velocity(-30 + (40*error)/band);
					}
				}
			}

			//
			// Control solenoid
			//
			{
				if (user_shoot)
					solenoid_push();
				else
					solenoid_pull();
			}
		}

		//
		// Play music
		//
		if (user_mode == MODE_PLAY || user_mode == MODE_LOST)
		{
			static int prev_mode = -1;
			static int counter = 0;
			static int note = 0;
			if (prev_mode != user_mode)
			{
				counter = 0;
				note = 0;
				prev_mode = user_mode;
			}
			
			int num_notes = (int)(sizeof(music_frequency) / sizeof(music_frequency[0]));
			int *frequency = music_frequency;
			int *length = music_length;
			int *delay = music_delay;
			float multiplier_frequency = MARIO_MULTIPLIER_FREQUENCY;
			float multiplier_length = MARIO_MULTIPLIER_LENGTH;

			if (user_mode == MODE_LOST)
			{
				num_notes = (int)(sizeof(music_lost_frequency) / sizeof(music_lost_frequency[0]));
				frequency = music_lost_frequency;
				length = music_lost_length;
				delay = music_lost_delay;
				multiplier_frequency = LOST_MULTIPLIER_FREQUENCY;
				multiplier_length = LOST_MULTIPLIER_LENGTH;
			}
				
			if (counter <= MAIN_TICK_MS) {
				wave_frequency(frequency[note]*multiplier_frequency);
			}

			if (counter >= length[note]*multiplier_length) {
				wave_frequency(0);
			}

			if (counter >= length[note]*multiplier_length + delay[note]*multiplier_length) {
				note++;
				counter = 0;
			}

			if (note == num_notes)
				note = 0;
			
			counter += MAIN_TICK_MS;
		}

		// printf("(node 2) %d %d\n", ir_raw, user_shoot);

		_delay_ms(MAIN_TICK_MS);
	}
}

int main(void)
{
	// uart_test();
	// test_mcp();
	// test_can_loopback();
	// test_can_between_nodes();
	// test_can_and_joystick();
	// test_servo();
	// test_can_joystick_servo();
	// test_ir_adc();
	// test_motor();
	// test_solenoid();
	// test_motor_with_joystick();
	// test_song();
	the_game();
}
