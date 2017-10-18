#include <avr/io.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"

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

int main(void)
{
	// uart_test();
	// test_mcp();
	// test_can_loopback();
	// test_can_between_nodes();
	test_can_and_joystick();
}