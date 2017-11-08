#define MOTOR_PORT    PORTH
#define MOTOR_PIN_RST PH6
#define MOTOR_PIN_OE  PH5
#define MOTOR_PIN_EN  PH4
#define MOTOR_PIN_SEL PH3
#define MOTOR_PIN_DIR PH1

#define ENCODER_DDR   DDRK
#define ENCODER_INPUT PINK

// Assumes AD0,AD1,AD2 are grounded
// (the three LSB of the address are 0)
#define MAX520_ADDRESS 0b0101000

void motor_init()
{
    // Enable motor control pins
    set_bit(DDRH, MOTOR_PIN_RST);
    set_bit(DDRH, MOTOR_PIN_OE);
    set_bit(DDRH, MOTOR_PIN_EN);
    set_bit(DDRH, MOTOR_PIN_SEL);
    set_bit(DDRH, MOTOR_PIN_DIR);

    // Enable encoder pins as input
    ENCODER_DDR = 0;

    // Reset motor
    clear_bit(MOTOR_PORT, MOTOR_PIN_RST);
    _delay_us(20);
    set_bit(MOTOR_PORT, MOTOR_PIN_RST);

    // Enable I2C
    TWI_Master_Initialise();
    sei(); // enable interrupts
}

int16_t motor_read_encoder()
{
    clear_bit(MOTOR_PORT, MOTOR_PIN_OE);
    clear_bit(MOTOR_PORT, MOTOR_PIN_SEL);
    _delay_us(20);
    uint8_t high_byte = ENCODER_INPUT;
    set_bit(MOTOR_PORT, MOTOR_PIN_SEL);
    _delay_us(20);
    uint8_t low_byte = ENCODER_INPUT;
    //clear_bit(MOTOR_PORT, MOTOR_PIN_RST);
    //_delay_us(20);
    //set_bit(MOTOR_PORT, MOTOR_PIN_RST);
    set_bit(MOTOR_PORT, MOTOR_PIN_OE);
    return ((int16_t)high_byte)<<8 | (low_byte);
}

void motor_velocity(int16_t velocity)
{
    set_bit(PORTH, MOTOR_PIN_EN);
    uint8_t speed;
    if (velocity < 0)
    {
        set_bit(PORTH, MOTOR_PIN_DIR);
        speed = (-velocity) & 0xff;
    }
    if (velocity > 0)
    {
        clear_bit(PORTH, MOTOR_PIN_DIR);
        speed = (velocity) & 0xff;
    }

    uint8_t command = 0b00000000;
    uint8_t msg[] = { MAX520_ADDRESS<<1, command, speed };
    TWI_Start_Transceiver_With_Data(msg, sizeof(msg));
    while (TWI_Transceiver_Busy()) ;
}
