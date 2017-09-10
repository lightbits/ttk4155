#include "common.h"
#include "uart.h"

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

void ext_mem_init(void)
{
    // Enable external memory
    // See atmega162 / page 30
    set_bit(MCUCR, SRE);

    // Mask out 4 MSB of address to release port pins PC7-PC4
    // See atmega162 / page 32 / table 4
    set_bit(SFIOR, XMM2);
    clear_bit(SFIOR, XMM1);
    clear_bit(SFIOR, XMM0);

    // Do we need to do this?
    // DDRC = 0xFF;
    // PORTC = 0x00;

    // Set wait state to wait two cycles per read and write strobe
    // (needed to adhere to ADC timing requirements)
    // See atmega162 / page 30
    // Note: Update this if you want to have different wait state sectors!
    set_bit(MCUCR, SRW11);
    clear_bit(EMCUCR, SRW10);
}

// This will write and read values to the external SRAM.
// You should verify that the SRAM is connected properly
// by seeing how many errors there were. If there are 100%
// errors, it's probably not working; but due to breadboards
// being crappy, there may be some errors anyway.
void sram_test(void)
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
void ext_mem_test_latch(void)
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

void gal_test(void)
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
        // p = (uint8_t*)0x1000; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);

        // SRAM_CS should be 0
        // ADC_CS should be 0
        // OLED_CS should be 1
        //p = (uint8_t*)0x1400; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);

        // SRAM_CS should be 1
        // ADC_CS should be 1
        // OLED_CS should be 1
        p = (uint8_t*)0x1800; *p = 0xff; _delay_ms(100);

        //_delay_ms(1000);
    }
}

// channel is one of 0 (ch1), 1 (ch2), 2 (ch3), 3 (ch4)
uint8_t adc_read(int channel)
{
    volatile uint8_t *ADC = (uint8_t*)0x1400; // should maybe be global const
    uint8_t mux_address = 4+channel;
    *ADC = mux_address;
    _delay_us(50); // Maximum conversion time is 40 microseconds (t_c)
                   // let's wait a bit longer than that...
    uint8_t value = *ADC;
    return value;
}

void adc_test()
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
        _delay_ms(100);
    }
}

void test_joystick()
{
    uart_init(9600);
    ext_mem_init();
    uint8_t min_x = 256;
    uint8_t max_x = 0;
    uint8_t min_y = 256;
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

int main (void)
{
    // uart_test();

    // ext_mem_test_latch();

    // sram_test();

    gal_test();
}
