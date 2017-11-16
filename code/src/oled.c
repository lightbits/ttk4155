#include "oled.h"
#include "font.h"
volatile uint8_t *oled_command = (uint8_t*)OLED_COMMAND_MEMORY_START;
volatile uint8_t *oled_data = (uint8_t*)OLED_DATA_MEMORY_START;

void oled_power_on()   { *oled_command = 0xaf; }
void oled_power_off()  { *oled_command = 0xae; }
void oled_invert_off() { *oled_command = 0xa6; }
void oled_invert_on()  { *oled_command = 0xa7; }
void oled_flip_screen()
{
	*oled_command = 0xc8;
	*oled_command = 0xa1;
}
void oled_set_column(uint8_t column)
{
    *oled_command = 0x21;
    *oled_command = column; // start address
    *oled_command = 127; // end address
}
void oled_set_page(uint8_t page)
{
    *oled_command = 0x22;
    *oled_command = page; // start address
    *oled_command = 7; // end address
}
void oled_xy(uint8_t x, uint8_t y)
{
	oled_set_column(x);
	oled_set_page(y);
}
void oled_horizontal_addressing_mode()
{
    *oled_command = 0x20;
    *oled_command = 0x00;
}

void oled_page_addressing_mode()
{
	*oled_command = 0x20;
	*oled_command = 2;
}

void oled_contrast(uint8_t contrast)
{
    *oled_command = 0x81;
    *oled_command = contrast;
}
void oled_reset_contrast()
{
    *oled_command = 0x81;
    *oled_command = 0x7f;
}
void oled_init()
{
    oled_power_off();
    oled_invert_off();
    // oled_horizontal_addressing_mode();
	oled_page_addressing_mode();
    oled_set_page(0);
    oled_set_column(0);
    oled_contrast(0x50);
    oled_power_on();

	// unflip screen
	*oled_command = 0xc0;
	*oled_command = 0xa0;
}
void oled_test()
{
	*oled_command = 0xae;
	*oled_command = 0xa1;
	*oled_command = 0xda;
	*oled_command = 0x12;
	*oled_command = 0xc8;
	*oled_command = 0xa8;
	*oled_command = 0x3f;
	*oled_command = 0xd5;
	*oled_command = 0x80;
	*oled_command = 0x81;
	*oled_command = 0x50;
	*oled_command = 0xd9;
	*oled_command = 0x21;
	*oled_command = 0x20;
	*oled_command = 0x02;
	*oled_command = 0xdb;
	*oled_command = 0x30;
	*oled_command = 0xad;
	*oled_command = 0x00;
	*oled_command = 0xa4;
	*oled_command = 0xa6;
	*oled_command = 0xaf;
	
	while (1)
	{
		*oled_data = 0xff;
		_delay_ms(100);
	}
}
void oled_set_pixels(uint8_t pixels)
{
    *oled_data = pixels;
}
void oled_clear()
{
	oled_xy(0,0);
	for (int y = 0; y < 8; y++)
	{
		oled_xy(0,y);
		for (int x = 0; x < 128; x++)
		oled_set_pixels(0x00);
	}
}
void oled_write_char(char c)
{
	for (int i = 0; i < 5; i++)
	oled_set_pixels(pgm_read_byte(&font5[c - ' '][i]));
}

void oled_print(const char *str)
{
	const char *c = str;
	while (*c)
	{
		oled_write_char(*c);
		oled_set_pixels(0);
		c++;
	}
}