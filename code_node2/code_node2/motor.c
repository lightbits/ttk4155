#define MOTOR_PORT    PORTH
#define MOTOR_DDR     DDRH
#define MOTOR_PIN_RST PH6
#define MOTOR_PIN_OE  PH5
#define MOTOR_PIN_EN  PH4
#define MOTOR_PIN_SEL PH3
#define MOTOR_PIN_DIR PH1

#define ENCODER_PORT    ???
#define ENCODER_DDR     ???
#define ENCODER_PORT_IN ???

// Assumes AD0, AD1 and AD2 of the MAX520 are grounded
#define DAC_ADDRESS 0b01010000

#include "motor_i2c.c"

void motor_init()
{
    // Enable motor control pins
    MOTOR_DDR |=
        (1 << MOTOR_PIN_RST) |
        (1 << MOTOR_PIN_OE) |
        (1 << MOTOR_PIN_EN) |
        (1 << MOTOR_PIN_SEL) |
        (1 << MOTOR_PIN_DIR);

    // Set encoder pins as input
    ENCODER_DDR = 0;

    // todo: Should we enable pull-up resistors?
    // ENCODER_PORT = ;

    i2c_init();
}

void motor_velocity(int16_t velocity) // between -255 and +255
{
    // Enable motor and set direction
    // todo: make sure I got these right?
    if (velocity < 0)
        MOTOR_PORT |= (1 << MOTOR_PIN_EN) | (0 << MOTOR_PIN_DIR);
    else
        MOTOR_PORT |= (1 << MOTOR_PIN_EN) | (1 << MOTOR_PIN_DIR);

    // Send 8-bit speed to the MAX520's DAC0
    // See figure 6 in MAX520 page 11
    uint16_t speed = 0;
    if (velocity < 0)
        speed = (uint16_t)(-velocity);
    else
        speed = (uint16_t)(velocity);
    uint8_t dac_byte = (uint8_t)(velocity & 0xff);
    i2c_start_write(DAC_ADDRESS);
    i2c_write(0b00000000);
    i2c_write(dac_byte);
    i2c_stop();

    // todo: ensure that you call this function with sufficient time
    // spacing for the digital value to get converted.
}

int16_t motor_read_encoder()
{
    // Enable output
    clear_bit(MOTOR_PORT, MOTOR_PIN_OE);

    // Select high byte
    clear_bit(MOTOR_PORT, MOTOR_PIN_SEL);
    _delay_us(20);
    uint16_t high_byte = ENCODER_PORT_IN;

    // Select low byte
    set_bit(MOTOR_PORT, MOTOR_PIN_SEL);
    _delay_us(20);
    uint16_t high_byte = ENCODER_PORT_IN;

    // Reset encoder
    clear_bit(MOTOR_PORT, MOTOR_PIN_RST);
    _delay_us(20);
    set_bit(MOTOR_PORT, MOTOR_PIN_RST);

    // Disable output
    set_bit(MOTOR_PORT, MOTOR_PIN_OE);

    int16_t delta = (int16_t)((high_byte << 8) | low_byte);
    return delta;
}

void test_motor_velocity()
{
    uart_init(9600);
    printf("Testing motor velocity...\n");
    motor_init();
    while (1)
    {
        motor_velocity(32);
        _delay_ms(1000);
        motor_velocity(-32);
        _delay_ms(1000);
    }
}

void test_motor_encoder()
{
    uart_init(9600);
    printf("Testing motor...\n");

    int32_t absolute = 0;
    motor_init();
    while (1)
    {
        int16_t delta = motor_read_encoder();
        printf("%d %d\n", delta, absolute);
        absolute += delta;
        _delay_ms(100);
    }
}
