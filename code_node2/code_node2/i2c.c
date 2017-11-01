// This enables I2C on the ATmega2560 by using the Two-Wire Interface
// in master transmitter and master receiver mode. This enables I2C on
// PD1 (SDA) and PD0 (SCL).
// The bitrate is hardcoded to 100 kHz assuming F_CPU is 16 MHz

void i2c_init();
int  i2c_start_write(uint8_t address);
int  i2c_write(uint8_t *data, uint8_t count);
int  i2c_start_read(uint8_t address);
int  i2c_read(uint8_t *data, uint8_t count);
void i2c_stop();

//
// Implementation
//

void i2c_init()
{
    // See Master Transmitter Mode (page 227)
    clear_bit(TWSR, TWPS1);
    clear_bit(TWSR, TWPS0);

    // F_CPU=16MHz
    // TWBR=12 TWPS=0 : 400 kHz
    // TWBR=72 TWPS=0 : 100 kHz
    TWBR = 72;
}

int i2c_start_write(uint8_t address)
{
    // See page 228

    // Send start condition
    TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);
    while (!test_bit(TWCR, TWINT)) ;
    if ( (TWSR & 0xF8) != 0x08 && // START transmitted
         (TWSR & 0xF8) != 0x10 )  // Repeated START transmitted
        return 0;

    // Send address and write bit (0)
    TWDR = (address << 1) | 0;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!test_bit(TWCR, TWINT)) ;
    if ((TWSR & 0xF8) != 0x18) // SLA+W transmitted and ACK received
        return 0;

    return 1;
}

// todo: this assumes start_write succeeded
int i2c_write(uint8_t *data, uint8_t count)
{
    for (uint8_t i = 0; i < count; i++)
    {
        TWDR = data[i];
        TWCR = (1 << TWINT) | (1 << TWEN);
        while (!test_bit(TWCR, TWINT)) ;
        if ((TWSR & 0xF8) != 0x28) // Data transmitted and ACK received
            return 0;
    }
    return 1;
}

// todo: this assumes i2c_write or i2c_read succeeded
// note: that TWINT is NOT set after a stop condition is set
void i2c_stop()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
}

int i2c_start_read(uint8_t address)
{
    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!test_bit(TWCR, TWINT)) ;
    if ( (TWSR & 0xF8) != 0x08 && // START transmitted
         (TWSR & 0xF8) != 0x10 )  // Repeated START transmitted
        return 0;

    // Send address and read bit (1)
    TWDR = (address << 1) | 1;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!test_bit(TWCR, TWINT)) ;
    if ((TWSR & 0xF8) != 0x40) // SLA+R transmitted and ACK received
        return 0;

    return 1;
}

// todo: this assumes i2c_start_read succeeded
int i2c_read(uint8_t *data, uint8_t count)
{
    uint8_t i = 0;
    for (i = 0; i < count-1; i++)
    {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        while (!test_bit(TWCR, TWINT)) ;
        if ((TWSR & 0xF8) != 0x50) // Data received and ACK returned
            return 0;
        data[i] = TWDR;
    }

    TWCR = (1 << TWINT) | (1 << TWEN) | (0 << TWEA);
    while (!test_bit(TWCR, TWINT)) ;
    if ((TWSR & 0xF8) != 0x58) // Data received and NACK returned
        return 0;
    data[i] = TWDR;

    return 1;
}
