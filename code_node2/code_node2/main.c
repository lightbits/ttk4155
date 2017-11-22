#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../spi.h"
#include "../../mcp2515.h"
#include "../../shared.h"
#include "uart.h"
#include "pwm.h"
#include "motor.h"
#include "solenoid.h"
#include "servo.h"
#include "music.c"
#include "tests.c"

void the_game()
{
	// Note: the wireless remote is only compatible with the velocity regulator
	#define USE_VELOCITY_REGULATOR 1
	#define USE_POSITION_REGULATOR 0
	#define USE_PI_REGULATOR 0

	uart_init(9600);
	mcp_init();
	mcp_mode_normal();
	motor_init();
	motor_velocity(0);
	servo_init();
	solenoid_init();
	solenoid_pull();
	wave_frequency(0);

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
			can_msg_node1_to_node2 msg = {0};
			uint8_t length;
			if (mcp_read_message(&id, (uint8_t*)&msg, &length))
			{
				user_angle = msg.angle;
				user_position = msg.position;
				user_shoot = msg.shoot;
				user_mode = msg.mode;
			}
		}

		//
		// Send IR signal to node 1
		//
		{
			uint16_t id = 1;
			can_msg_node2_to_node1 msg = {0};
			msg.light_blocked = light_broken;
			mcp_send_message(id, (uint8_t*)&msg, sizeof(msg));
		}

		if (user_mode == MODE_PLAY)
		{
			//
			// Control servo position and motor speed
			//
			#if USE_VELOCITY_REGULATOR==1
			{
				if (user_angle < 127-10)
					motor_velocity(100);
				else if (user_angle > 127+10)
					motor_velocity(-100);
				else
					motor_velocity(0);

				servo_position((float)(user_position-28)/255);
			}
			#elif USE_POSITION_REGULATOR==1
			{
				const int32_t ENCODER_MAX = 6000;
				int32_t desired_position = ENCODER_MAX*(int32_t)(255-user_position)/255;
				int32_t actual_position = motor_read_encoder();
				int32_t band = 1000;
				int32_t error = (desired_position - actual_position);
				if (error > band)
					motor_velocity(100);
				else if (error < -band)
					motor_velocity(-100);
				else if (error > 0)
					motor_velocity(30 + (40*error)/band);
				else if (error < 0)
					motor_velocity(-30 + (40*error)/band);
				else
					motor_velocity(0);

				servo_position((float)(user_angle-28)/255);
			}
			#elif USE_PI_REGULATOR==1
			{
				const int32_t ENCODER_MAX = 6000;
				int32_t desired_position = ENCODER_MAX*(int32_t)(255-user_position)/255;
				int32_t actual_position = motor_read_encoder();
				int32_t band = 1000;
				int32_t error = (desired_position - actual_position); // between -6000 and 6000

				static int32_t sum_e_dt = 0;
				sum_e_dt += error*MAIN_TICK_MS;

				static int32_t last_error = 0;
				int32_t de = (1000*(error-last_error))/MAIN_TICK_MS;
				if (abs(error - last_error) < 100) // disable D-gain within a band to reduce jitter
					de = 0;

				// P gain is found by looking at what speed we want at a specific error
				int32_t e_at_max_speed = 500;
				int32_t max_speed = 200;
				int32_t u_p = (max_speed*error)/e_at_max_speed;

				// Thumb-hand rule: I gain is twice P gain
				int32_t u_i = (2*max_speed*(sum_e_dt/1000))/e_at_max_speed;

				// Kinda randomly chosen scaling factor
				int32_t u_d = (de/100);
				int32_t u = u_p + u_i + u_d;

				if (u > max_speed) u = max_speed;
				if (u < -max_speed) u = -max_speed;

				motor_velocity(u); // between -255 and +255
				last_error = error;
				servo_position((float)(user_angle-28)/255);
			}
			#endif

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
		else
		{
			motor_reset();
			motor_velocity(0);
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

		// Note: todo: this assumes that all the work above took 0 milliseconds, which
		// is not exactly correct. But, for now it is close enough.
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
