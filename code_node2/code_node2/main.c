#include <avr/io.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "pwm.h"

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

		printf("(node 2) %d %d\n", joy_x, joy_y);
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

// max effect = 150 mW
// max voltage = 0.42 V (no light)
// -> max current = I = P/U = 150 mW / 0.42V = 0.357 A

// the resistor needs to make the current in the circuit equal to this
// voltage over resistor is 5V - 0.42V = 4.58V
// U = RI -> R = U/I = 4.58 / 0.357 = 13 ohm

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

		float position = (float)(joy_x-28)/255;
		servo_position(position);

		printf("(node 2) %d %d\n", joy_x, joy_y);
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
	test_ir_adc();
}