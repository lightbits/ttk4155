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

	// This should access external memory
	while (1)
	{
		// addr should be (0001 1100         1010 1010)
		//                      ^^^^         ^^^^^^^^^
		//                    (PC0-PC3)  (PA0-PA7 -> latch)
		unsigned char *ptr = (unsigned char*)(0x1CAA);

		// data byte should be (1010 1010)
		*ptr = 0xaa;

		_delay_ms(100);
	}
}

int main (void)
{
	// uart_test();

	ext_mem_test_latch();

	// sram_test();
}
