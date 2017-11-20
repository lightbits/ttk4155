#include "common.h"
#include "uart.h"
#include "adc.h"
#include "extmem.h"
#include "oled.h"
#include "../../spi.h"
#include "../../mcp2515.h"
#include "../../shared.h"

#define NRF_IMPLEMENTATION
#define NRF_ATMEGA162_IMPLEMENTATION
#include "../../nrf.c"

#include "tests.c"

void the_game()
{
    uart_init(9600);
	printf("The game...");

	ext_mem_init();
	oled_init();
    mcp_init();
    mcp_mode_normal();

	{
		// External memory interferes with nrf
		// so we disable before we interact with it.
		ext_mem_disable();
		spi_init();
		nrf_init();
		ext_mem_init();
	}

	printf("Ready!\n");

	const uint8_t CONTROLLER_P1000 = 0;
	const uint8_t CONTROLLER_REMOTE = 1;
	#define MAIN_TICK_MS 50

	uint8_t mode = MODE_MENU;
	uint8_t flip_screen = 1;
	uint8_t controller = CONTROLLER_P1000;
	uint32_t time_played = 0;

	if (flip_screen)
		oled_flip_screen();

	while (1)
	{
        //
		// Read joystick and button and slider (from ADC)
        //
		uint8_t joy_x = adc_read(0);
		uint8_t joy_y = adc_read(1);
		uint8_t button = !(adc_read(2) > 128);
		uint8_t slider = adc_read(3);

		//
		// Poll wireless remote controller for updates
		// (we preserve the last update we received)
		//
		static uint8_t remote_button = 0;
		static uint8_t remote_tilt = 127;
		{
			ext_mem_disable();
            static uint8_t data[32];
            if (nrf_read_payload(data, 32))
            {
                remote_button = data[0];
                remote_tilt = data[1];
            }
			ext_mem_init();
		}

        //
		// Check if joystick was moved up, down, left or right once
        // (used to navigate menu)
        //
		uint8_t joy_up,joy_down,joy_left,joy_right;
		{
			static uint8_t joy_was_up = 0;
			static uint8_t joy_was_down = 0;
			static uint8_t joy_was_right = 0;
			static uint8_t joy_was_left = 0;
			uint8_t joy_is_up,joy_is_down,joy_is_right,joy_is_left;
			if (flip_screen)
			{
				joy_is_up = (joy_y > 200);
				joy_is_down = (joy_y < 100);
				joy_is_right = (joy_x > 200);
				joy_is_left = (joy_x < 100);
			}
			else
			{
				joy_is_up = (joy_y < 100);
				joy_is_down = (joy_y > 200);
				joy_is_right = (joy_x < 100);
				joy_is_left = (joy_x > 200);
			}
			joy_up = !joy_was_up && joy_is_up;
			joy_down = !joy_was_down && joy_is_down;
			joy_left = !joy_was_left && joy_is_left;
			joy_right = !joy_was_right && joy_is_right;
			joy_was_up = joy_is_up;
			joy_was_down = joy_is_down;
			joy_was_left = joy_is_left;
			joy_was_right = joy_is_right;
		}

        //
        // Node 2 tells us if the ball is blocking the IR light beam
        // (over CAN bus)
        //
        uint8_t light_blocked = 0;
        {
			can_msg_node2_to_node1 msg = {0};
            uint16_t id;
			uint8_t length;
			if (mcp_read_message(&id, (uint8_t*)&msg, &length))
				light_blocked = msg.light_blocked;
        }

		if (mode == MODE_MENU)
		{
            // todo: ensure that these are synchronized in order with
            // MODE_PLAY, MODE_MUSIC, MODE_CONTROLS, ... if you add
            // new items.
			const char *items[] = { "Play", "Music", "Controls" };
			const uint8_t num_items = 3;
			static uint8_t selected = 0;

			// Move up or down in menu
			if (joy_down && selected < num_items-1)
				selected++;
			if (joy_up && selected > 0)
				selected--;
            if (joy_right)
			{
                mode = selected;
				if (mode == MODE_PLAY)
					time_played = 0;
			}

			// Draw menu items
            oled_clear();
			oled_xy(0,0);
			for (uint8_t i = 0; i < num_items; i++)
			{
				oled_xy(0,i);
				if (selected == i)
					oled_print("--> ");
				oled_print(items[i]);
			}
		}
		else if (mode == MODE_MUSIC)
		{
			const char *songs[] = { "Beethoven", "Mario" };
			const uint8_t num_songs = 2;
			static uint8_t selected = 0;
            oled_clear();
            oled_xy(0,0); oled_print("Up/Down: Select");
            oled_xy(0,1); oled_print("Left: Go back");
			oled_xy(0,3);
            oled_print("Song: <");
			oled_print(songs[selected]);
            oled_print(">");
			if (joy_left)
				mode = MODE_MENU;
            if (joy_down && selected > 0)
                selected--;
            if (joy_up && selected < num_songs-1)
                selected++;
		}
		else if (mode == MODE_CONTROLS)
		{
            oled_clear();
			oled_xy(0,0); oled_print("Up/Down: Select");
            oled_xy(0,1); oled_print("Left: Go back");
            oled_xy(0,3);
            oled_print("Ctrl: ");
            if (controller == CONTROLLER_P1000)
                oled_print("<P1000>");
            if (controller == CONTROLLER_REMOTE)
                oled_print("<Remote>");
            if (joy_up) controller = CONTROLLER_P1000;
            if (joy_down) controller = CONTROLLER_REMOTE;
			if (joy_left)
				mode = MODE_MENU;
		}
		else if (mode == MODE_PLAY)
		{
            oled_clear();
            oled_xy(0,0);
            oled_print("Time: ");
			oled_print_u16((uint16_t)time_played/1000);
			oled_print("s");

			oled_xy(0,1);
			oled_print("REMOTE: ");
			oled_print_u16(remote_button);
			oled_print(" ");
			oled_print_u16(remote_tilt);

			oled_xy(0,2);
			oled_print("P1000: ");
			oled_print_u16(button);
			oled_print(" ");
			oled_print_u16(joy_x);
			oled_print(" ");
			oled_print_u16(slider);

			time_played += MAIN_TICK_MS;

			if (light_blocked)
			{
				mode = MODE_LOST;
				time_played = 0;
			}
		}
		else if (mode == MODE_LOST)
		{
			time_played += MAIN_TICK_MS;
			oled_clear();
			oled_xy(0,0);
			oled_print("You lost!");
			if (time_played >= 3500)
				mode = MODE_MENU;
		}

		//
		// Send controller input to node 2 over CAN
		//
		{
			can_msg_node1_to_node2 msg = {0};
			msg.mode = mode;

			if (controller == CONTROLLER_P1000)
			{
				msg.angle = joy_x;
				msg.position = slider;
				msg.shoot = button;
			}
			else if (controller == CONTROLLER_REMOTE)
			{
				msg.angle = remote_tilt;
				msg.position = 127;
				msg.shoot = remote_button;
			}

			uint8_t id = 0;
			mcp_send_message(id, (uint8_t*)&msg, sizeof(msg));
		}

		_delay_ms(MAIN_TICK_MS);
	}
}

int main (void)
{
    // uart_test();
    // test_latch();
    // test_sram();
    // test_gal();
    // test_adc();
    // test_oled_checkerboard();
    // test_smiley();
    // test_symbols();
    // test_menu();
    // test_mcp();
	// test_can_loopback();
	// test_can_between_nodes();
	// test_can_and_joystick();
	// test_nrf();
	the_game();
}
