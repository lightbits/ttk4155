#include "oled.h"
volatile uint8_t *oled_command = OLED_COMMAND_MEMORY_START;
volatile uint8_t *oled_data = OLED_DATA_MEMORY_START;

void oled_power_on()   { *oled_command = 0xaf; }
void oled_power_off()  { *oled_command = 0xae; }
void oled_invert_off() { *oled_command = 0xa6; }
void oled_invert_on()  { *oled_command = 0xa7; }
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
void oled_horizontal_addressing_mode()
{
    *oled_command = 0x20;
    *oled_command = 0x00;
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
    oled_horizontal_addressing_mode();
    // oled_set_page(0);
    // oled_set_column(0);
    oled_contrast(0x50);
    oled_power_on();
}
