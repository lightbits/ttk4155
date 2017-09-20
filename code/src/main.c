#include "common.h"
#include "uart.h"
#include "adc.h"
#include "extmem.h"
#include "oled.h"

// This will repeatedly set pin 1 of port D high and low
void test_clock(void)
{
    set_bit(DDRD, DDD1);
    while (1)
    {
        set_bit(PORTD, PD1);
        _delay_ms(100);
        clear_bit(PORTD, PD1);
        _delay_ms(100);
    }
}

// This will write and read values to the external SRAM.
// You should verify that the SRAM is connected properly
// by seeing how many errors there were. If there are 100%
// errors, it's probably not working; but due to breadboards
// being crappy, there may be some errors anyway.
void test_sram(void)
{
    uart_init(9600);
    ext_mem_init();

    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");

    // We will use rand to generate random-looking but deterministic numbers
    uint16_t seed = rand();

    //
    // Write phase: Immediately check that the correct value was stored
    //
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value)
        {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            write_errors++;
        }
    }

    //
    // Read phase: Check that no values were changed during or after writing
    //
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value)
        {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

// This will repeatedly try to access external memory.
// You should verify that the latch is locking on to
// the correct values, by measuring its pins and comparing
// the value with the address used (see inside function).
void test_latch(void)
{
    uart_init(9600);
    ext_mem_init();

    printf("Starting external memory latch test...\n");

    // This should access external memory and the MCU will
    // thereby use its external memory addressing machinery.
    // This loop repeatedly writes to destination 0x1CAA,
    // (address 0001 1100 1010 1010), the value 0xAA (1010 1010).

    // Check that the latch is working correctly by seeing if
    // its output (the 8 LSB of the address) are the same as the
    // address that is written to below.

    // This pinout might also be useful for debugging if it doesn't work:
    //            8 MSB          8 LSB
    // Address: XXXX  XXXX     XXXX XXXX
    //               PC0:PC3    PA0:PA7 (goes to latch)
    //
    while (1)
    {
        uint8_t *ptr = (uint8_t*)(0x1CAA);
        uint8_t value_to_write = 0xff;

        *ptr = value_to_write;
        _delay_ms(100);

        uint8_t written_value = *ptr;
        if (written_value == value_to_write) printf("OK\n");
        else printf("NO (%x)\n", written_value);
        _delay_ms(100);
    }
}

void test_gal(void)
{
    uart_init(9600);
    ext_mem_init();

    printf("Starting GAL test...\n");

    while (1)
    {
        uint8_t *p;

        // SRAM_CS should be 0
        // ADC_CS should be 1
        // OLED_CS should be 0
        //p = (uint8_t*)0x1000; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);

        // SRAM_CS should be 0
        // ADC_CS should be 0
        // OLED_CS should be 1
        p = (uint8_t*)0x1400; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);

        // SRAM_CS should be 1
        // ADC_CS should be 1
        // OLED_CS should be 1
        // p = (uint8_t*)0x1800; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);
    }
}

void test_joystick()
{
    uart_init(9600);
    ext_mem_init();
    uint8_t min_x = 255;
    uint8_t max_x = 0;
    uint8_t min_y = 255;
    uint8_t max_y = 0;
    uint8_t button_threshold = 128;
    while (1)
    {
        uint8_t x_volt = adc_read(ADC_CHANNEL_JOY_X);
        uint8_t y_volt = adc_read(ADC_CHANNEL_JOY_Y);
        uint8_t b_volt = adc_read(ADC_CHANNEL_JOY_B);
        uint8_t is_down = (b_volt < button_threshold);

        _delay_ms(100);
    }
}

// This will repeatedly sample the four channels of
// the ADC, and display their levels via printf.
void test_adc()
{
	uart_init(9600);
	ext_mem_init();
	printf("Starting adc test...\n");
	while (1)
	{
		uint8_t ch1 = adc_read(0);
		uint8_t ch2 = adc_read(1);
		uint8_t ch3 = adc_read(2);
		uint8_t ch4 = adc_read(3);
		printf("%d %d %d %d\n", ch1, ch2, ch3, ch4);
		_delay_ms(500);
	}
}

void oled_test_checkerboard()
{
	uart_init(9600);
	ext_mem_init();
    oled_init();
	printf("Testing oled...\n");
    int i = 0; // flips between 0 and 1 to animate the checkerboard
    while (1)
    {
        i = (i+1) % 2;
        for (int p = 0; p < 8; p++) // for each page (group of 8 pixels)
        for (int x = 0; x < 128; x++) // for each column
        {
            uint8_t data = 0; // the 8 pixel values in the page
            for (int y = p*8; y < (p+1)*8; y++)
            {
                if ((x+y) % 2 == i)
                    data |= 1 << y;
            }

            // We write pixels to the OLED one "page" at a time. A page
            // consists of eight pixels (one bit each). oled_init will
            // enable the "horizontal addressing mode", which means that
            // by writing one page at a time, the OLED driver chip will
            // automatically advance the current pixel pointer by eight
            // pixels. It goes horizontally (column-wise) until the end
            // then it resets to the next row, and continues like this
            // until it reaches the bottom right, and then resets to
            // the top left.
            oled_set_pixels(data);
        }
        _delay_ms(500);
    }
}

void oled_test_symbols()
{
    // The following static tables define these characters.
    // They are stored page by page (going to the right).
    // One page encodes a vertical strip of pixels. For
    // example, the left-most bar of the A is 0x1f =
    // 00011111 in binary. I'm assuming least significant
    // bit corresponds to top-most.
    // #### #### #### ###  #### ####
    // #  # #  # #    #  # #    #
    // #### ###  #    #  # ###  ###
    // #  # #  # #    #  # #    #
    // #  # #### #### ###  #### #
    static uint8_t sym_a[] = { 0x1f, 0x05, 0x05, 0x1f };
    static uint8_t sym_b[] = { 0x1f, 0x15, 0x15, 0x1b };
    static uint8_t sym_c[] = { 0x1f, 0x11, 0x11, 0x11 };
    static uint8_t sym_d[] = { 0x1f, 0x11, 0x11, 0x0e };
    static uint8_t sym_e[] = { 0x1f, 0x15, 0x15, 0x11 };
    static uint8_t sym_f[] = { 0x1f, 0x05, 0x05, 0x01 };

    uint8_t *symbols[] = { sym_a, sym_b, sym_c, sym_d, sym_e, sym_f };

    oled_init();
    while (1)
    {
        uint8_t symbol_index = 0;
        for (uint8_t y = 0; y < 8; y++)
        {
            oled_set_page(y);

            // Each symbol is 4 pixels wide + 1 pixel spacing.
            // That gives us 128/5 = 25 symbols per row.
            for (uint8_t x = 0; x < 128/5; x++)
            {
                uint8_t *sym = symbols[symbol_index];

                // draw the symbol
                for (uint8_t i = 0; i < 4; i++)
                    oled_set_pixels(sym[i]);

                // blank space between symbols
                oled_set_pixels(0x00);
            }
        }
        _delay_ms(500);
    }
}

int main (void)
{
    // uart_test();

    // test_latch();

    // test_sram();

    // test_gal();

	// test_adc();
	
	{
		uart_init(9600);
		ext_mem_init();
		printf("testing oled...\n");
		_delay_ms(100);	
		oled_test();	
	}
	
	// oled_test_checkerboard();
}
