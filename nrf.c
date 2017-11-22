#ifndef NRF_HEADER
#define NRF_HEADER
//
// nRF24L01 2.4GHz wireless chip
//
// To use the chip, connect it to a SPI bus and enable SPI with
//  Polarity: 0 (SCK idle low)
//  Phase:    0 (Data changes on falling SCK)
//  Datarate: Maximum 8Mbps
//
// Connect CSN and CE to GPIO pins.
//
// Then, implement the following functions for your specific device
//
void nrf_spi_select();   // CSN = 0
void nrf_spi_deselect(); // CSN = 1
void nrf_chip_enable();  // CE = 1
void nrf_chip_disable(); // CE = 0
void nrf_pin_enable();   // Configure CSN,CE as output pins
uint8_t nrf_spi_send(uint8_t data);

//
// You can then call these functions that rely on the SPI interface
//
void    nrf_init();
void    nrf_transmit(uint8_t *data, uint8_t count);
uint8_t nrf_read_payload(uint8_t *data, uint8_t count);
void    nrf_write_payload(uint8_t *data, uint8_t count);
void    nrf_write_register(uint8_t register_address, uint8_t data);
uint8_t nrf_read_status();
uint8_t nrf_read_register(uint8_t register_address);
#endif

//
// Hardware specific implementation for ATmega328p
// hand-controller board. Assumes PC3 -> CSN, PC2 -> CE,
// and connection to SPI interface (MOSI/MISO/SCK).
//
#ifdef NRF_ATMEGA328_IMPLEMENTATION
#define NRF_CSN_PORT C
#define NRF_CSN_PIN  3
#define NRF_CE_PORT  C
#define NRF_CE_PIN   2
uint8_t nrf_spi_send(uint8_t data) { return spi_send(data); }
void nrf_spi_select() { pin_low(NRF_CSN_PORT, NRF_CSN_PIN); }
void nrf_spi_deselect() { pin_high(NRF_CSN_PORT, NRF_CSN_PIN); }
void nrf_chip_enable() { pin_high(NRF_CE_PORT, NRF_CE_PIN); }
void nrf_chip_disable() { pin_low(NRF_CE_PORT, NRF_CE_PIN); }
void nrf_pin_enable()
{
    pin_out(NRF_CSN_PORT, NRF_CSN_PIN);
    pin_out(NRF_CE_PORT, NRF_CE_PIN);
}
#endif

//
// Hardware specific implementation for ATmega162
// node 1 game board. Ensure PB0 -> CSN. PB1 -> CE.
// and connection to SPI interface (MOSI/MISO/SCK).
// Also assumes you level-shift MISO from 3.3v to
// 5v using a single (inverting) transistor. This
// is why I invert the spi_write return value below.
//
#ifdef NRF_ATMEGA162_IMPLEMENTATION
#define NRF_CE_PIN  PB0
#define NRF_CSN_PIN PB1
uint8_t nrf_spi_send(uint8_t data) { return ~spi_write(data); }
void nrf_spi_select() { clear_bit(PORTB, NRF_CSN_PIN); }
void nrf_spi_deselect() { set_bit(PORTB, NRF_CSN_PIN); }
void nrf_chip_enable() { set_bit(PORTB, NRF_CE_PIN); }
void nrf_chip_disable() { clear_bit(PORTB, NRF_CE_PIN); }
void nrf_pin_enable()
{
    set_bit(DDRB, NRF_CE_PIN);
    set_bit(DDRB, NRF_CSN_PIN);
}
#endif

//
// Hardware specific implementation for mbed
// hand-controller board. Assumes PC3 -> CSN, PC2 -> CE,
// and connection to SPI interface (MOSI/MISO/SCK).
//
#ifdef NRF_MBED_IMPLEMENTATION
SPI spi(p5, p6, p7); // mosi, miso, sclk
DigitalOut cs(p8);
DigitalOut ce(p9);
DigitalIn irq(p10);
uint8_t nrf_spi_send(uint8_t data) { return spi.write(data); }
void nrf_spi_select() { cs = 0; }
void nrf_spi_deselect() { cs = 1; }
void nrf_chip_enable() { ce = 1; }
void nrf_chip_disable() { ce = 0; }
void nrf_pin_enable() { }
void _delay_ms(int ms) { wait_ms(ms); }
void _delay_us(int us) { wait_us(us); }
#endif

#ifdef NRF_IMPLEMENTATION
#define NRF_PAYLOAD_LENGTH 32

#define NRF_CONFIG        0x00
#define NRF_MASK_RX_DR    6 //
#define NRF_MASK_TX_DS    5 //
#define NRF_MASK_MAX_RT   4 //
#define NRF_EN_CRC        3 // Enable CRC
#define NRF_CRCO          2 // CRC encoding (1: 2 byte, 0: 1 byte)
#define NRF_PWR_UP        1 // 1: Power up, 0: Power down
#define NRF_PRIM_RX       0 // 1: PRX, 0: PTX
#define NRF_EN_AA         0x01
#define NRF_ENAA_P5       5 // Enable auto acknowledgment pipe 5 [1]
#define NRF_ENAA_P4       4 // Enable auto acknowledgment pipe 4 [1]
#define NRF_ENAA_P3       3 // Enable auto acknowledgment pipe 3 [1]
#define NRF_ENAA_P2       2 // Enable auto acknowledgment pipe 2 [1]
#define NRF_ENAA_P1       1 // Enable auto acknowledgment pipe 1 [1]
#define NRF_ENAA_P0       0 // Enable auto acknowledgment pipe 0 [1]
#define NRF_EN_RXADDR     0x02 // Enabled RX addresses
#define NRF_ERX_P5        5 // Enable data pipe 5 [0]
#define NRF_ERX_P4        4 // Enable data pipe 4 [0]
#define NRF_ERX_P3        3 // Enable data pipe 3 [0]
#define NRF_ERX_P2        2 // Enable data pipe 2 [0]
#define NRF_ERX_P1        1 // Enable data pipe 1 [1]
#define NRF_ERX_P0        0 // Enable data pipe 0 [1]
#define NRF_SETUP_AW      0x03 // Address width
#define NRF_SETUP_RETR    0x04
#define NRF_RF_CH         0x05
#define NRF_RF_SETUP      0x06
#define NRF_RF_DR         3
#define NRF_RF_PWR        1
#define NRF_LNA_HCURR     0
#define NRF_STATUS        0x07
#define NRF_RX_DATA_READY 6
#define NRF_TX_DATA_SENT  5
#define NRF_MAX_RETRIES   4
#define NRF_RX_PIPE_NO    1
#define NRF_TX_FULL       0
#define NRF_RX_PW_P0      0x11 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_RX_PW_P1      0x12 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_RX_PW_P2      0x13 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_RX_PW_P3      0x14 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_RX_PW_P4      0x15 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_RX_PW_P5      0x16 // 0: Pipe not used, 1-32: Length in bytes
#define NRF_FIFO_STATUS   0x17
#define NRF_FIFO_TX_FULL  5
#define NRF_FIFO_TX_EMPTY 4
#define NRF_FIFO_RX_FULL  1
#define NRF_FIFO_RX_EMPTY 0

typedef struct
{
    int rx_data_ready;  // New data is available for reading from RX FIFO (1)
    int tx_data_sent;   // Data has been sent from TX FIFO (1)
    int max_retries;    // Max retransmits has been reached (1)
    int rx_pipe_number; // Pipe number for the payload available for reading
                        // (7 = Empty, 6 = Reserved, 0-5 = Data pipe number)
    int tx_full;        // TX FIFO is full (1) or not (0)
} nrf_status_t;

nrf_status_t nrf_decode_status()
{
    uint8_t r = nrf_read_status();
    nrf_status_t s;
    s.rx_data_ready  = (r >> NRF_RX_DATA_READY) & 1;
    s.tx_data_sent   = (r >> NRF_TX_DATA_SENT) & 1;
    s.max_retries    = (r >> NRF_MAX_RETRIES) & 1;
    s.rx_pipe_number = (r >> NRF_RX_PIPE_NO) & 7;
    s.tx_full        = (r >> NRF_TX_FULL) & 1;
    return s;
}

uint8_t nrf_read_status()
{
    nrf_spi_select();
    uint8_t status = nrf_spi_send(0b11111111);
    nrf_spi_deselect();
    return status;
}

uint8_t nrf_read_register(uint8_t register_address)
{
    nrf_spi_select();
    nrf_spi_send(0b00000000 | (register_address & 0b00011111));
    uint8_t data = nrf_spi_send(0b11111111);
    nrf_spi_deselect();
    return data;
}

void nrf_write_register(uint8_t register_address, uint8_t data)
{
    nrf_spi_select();
    nrf_spi_send(0b00100000 | (register_address & 0b00011111));
    nrf_spi_send(data);
    nrf_spi_deselect();
}

uint8_t nrf_read_payload(uint8_t *data, uint8_t count)
{
    nrf_spi_select();
    uint8_t status = nrf_spi_send(0b01100001);
    uint8_t empty = ((status >> NRF_RX_PIPE_NO) & 7) == 0b111;
    if (empty)
    {
        nrf_spi_deselect();
        return 0;
    }
    else
    {
        uint8_t i = 0;
        for (i = 0; i < count && i < NRF_PAYLOAD_LENGTH; i++)
            data[i] = nrf_spi_send(0b11111111);

        // todo: I think we may have to clock out all the bytes
        // for the payload to be deleted from the FIFO?
        for (; i < NRF_PAYLOAD_LENGTH; i++)
            nrf_spi_send(0b11111111);

        // clear flag by writing '1'
        nrf_write_register(NRF_STATUS, 1 << NRF_RX_DATA_READY);
        nrf_spi_deselect();
        return 1;
    }
}

void nrf_write_payload(uint8_t *data, uint8_t count)
{
    nrf_spi_select();
    nrf_spi_send(0b10100000);

    uint8_t i = 0;
    for (i = 0; i < count && i < NRF_PAYLOAD_LENGTH; i++)
        nrf_spi_send(data[i]);

    // Always write 32 bytes because we hardcode the static payload length
    // to be 32 bytes, and the number of bytes we clock in must match the
    // RX_PW_Px register set on the receiver (which we set in nrf_init).
    for (; i < NRF_PAYLOAD_LENGTH; i++)
        nrf_spi_send(0);

    nrf_spi_deselect();
}

void nrf_init()
{
    nrf_pin_enable();
    nrf_chip_disable();
    nrf_spi_deselect();

    _delay_ms(15); // Power-on-reset delay is 10.3ms

    nrf_write_register(NRF_CONFIG, (1 << NRF_PWR_UP) | (1 << NRF_EN_CRC));

    _delay_ms(5); // PWR_UP->Standby delay is 1.5ms

    nrf_write_register(NRF_EN_RXADDR,  0b00000011); // Enable data pipe 0,1

    nrf_write_register(NRF_SETUP_AW,   0b00000011); // 5 byte address width

    // nrf_write_register(NRF_EN_AA,      0b00111111); // Auto-ack on pipe 0:5
    nrf_write_register(NRF_EN_AA,      0b00000000); // No auto-ack

    // nrf_write_register(NRF_SETUP_RETR, 0b00000011); // Enable auto retransmit
    nrf_write_register(NRF_SETUP_RETR, 0b00000000); // No auto retransmit

    nrf_write_register(NRF_RF_CH, 2); // Set radio frequency to 2400 + N [MHz]

    nrf_write_register(NRF_RF_SETUP,
        (0 << NRF_RF_DR)  |         // 1Mbps air data rate
        (3 << NRF_RF_PWR) |         // 0dBm output power in TX mode
        (1 << NRF_LNA_HCURR));      // wtf?

    // RX_ADDR_P0 is 0xE7E7E7E7E7 on reset
    // RX_ADDR_P1 is 0xC2C2C2C2C2 on reset
    // TX_ADDR is 0xE7E7E7E7E7 on reset
    nrf_write_register(NRF_RX_PW_P0, NRF_PAYLOAD_LENGTH);
    nrf_write_register(NRF_RX_PW_P1, NRF_PAYLOAD_LENGTH);

    // Enter rx mode
    nrf_write_register(NRF_CONFIG, (1 << NRF_PWR_UP) | (1 << NRF_EN_CRC) | (1 << NRF_PRIM_RX));
    nrf_chip_enable();
    _delay_us(200);

    nrf_write_register(NRF_STATUS, 0b01111110); // Clear interrupt flags by writing '1'
}

void nrf_transmit(uint8_t *data, uint8_t count)
{
    // leave rx mode
    nrf_chip_disable();

    // enter tx mode
    nrf_write_payload(data, count);
    nrf_write_register(NRF_CONFIG, (1 << NRF_PWR_UP) | (1 << NRF_EN_CRC) | (0 << NRF_PRIM_RX));
    nrf_chip_enable();
    _delay_us(20);
    nrf_chip_disable();
    _delay_us(200);

    // wait until transmitted
    while (!(nrf_read_status() & (1 << NRF_TX_DATA_SENT))) ;

    // clear flag by writing '1'
    nrf_write_register(NRF_STATUS, 1 << NRF_TX_DATA_SENT);

    // return to rx mode
    nrf_write_register(NRF_CONFIG, (1 << NRF_PWR_UP) | (1 << NRF_EN_CRC) | (1 << NRF_PRIM_RX));
    nrf_chip_enable();
    _delay_us(200);
}
#endif
