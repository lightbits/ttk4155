// The OLED panel and its driver is described in the datasheets
// OLED LY190 and OLED SSD1308. See the datasheets if you want to
// add more of the control command functionality; the ones below
// are only a subset of the available functions.
#ifndef OLED_H
#define OLED_H
#include "common.h"
void oled_init();
void oled_flip_screen();
void oled_invert_on();
void oled_invert_off();
void oled_set_column(uint8_t column); // range: 0 to 127
void oled_set_page(uint8_t page); // range: 0 to 7
void oled_xy(uint8_t column, uint8_t page); // range: [0,127], [0,7]
void oled_contrast(uint8_t contrast); // range: 0 to 255
void oled_set_pixels(uint8_t pixels);
void oled_test();
#endif
