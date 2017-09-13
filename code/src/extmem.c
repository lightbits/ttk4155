#include "extmem.h"

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
