#include "mcp2515.h"

void mcp_init(void) {

    mcp_spi_init();
    mcp_reset();

    //
    // Enter configuration mode (certain registers are only
    // available in this mode.)
    //
    mcp_mode_config();

    // Disable hardware pins as request to send indicators
    mcp_bit_modify(MCP_TXRTSCTRL, 0b00000111, 0);

    // Disable all interrupts
    mcp_write(MCP_CANINTE, 0b00000000);
    // mcp_write(CANINTE, 0b00000011); // or enable RX0 and RX1 interrupts

    // Clear any pending interrupts (unsure if needed)
    mcp_write(MCP_CANINTF, 0b00000000);

    // Disable CLKOUT
    mcp_bit_modify(MCP_CANCTRL, MCP_CLKEN, 0);

    // Disable all filters and masks
    mcp_bit_modify(MCP_RXB0CTRL, MCP_RXM, 0b00000000);
    mcp_bit_modify(MCP_RXB1CTRL, MCP_RXM, 0b00000000);

    // Disable rollover
    mcp_bit_modify(MCP_RXB0CTRL, MCP_BUKT, 0b00000000);

    // Disable RX0BF and RX1BF pins as message indicators
    mcp_write(MCP_BFPCTRL, 0b00000000);

    // todo: Set bit timing by configuring the CNFn registers
    // (see page 43 section 5.5). This is important when talking
    // with other CAN nodes, but probably not important when in
    // loopback mode.

    mcp_mode_normal();
}

uint8_t mcp_read(uint8_t address) {
    mcp_slave_select();
    mcp_spi_write(MCP_READ);
    mcp_spi_write(address);
    uint8_t data = mcp_spi_read();
    mcp_slave_deselect();
    return data;
}

void mcp_read_many(uint8_t address, uint8_t *data, uint8_t count) {
    mcp_slave_select();
    mcp_spi_write(MCP_READ);
    mcp_spi_write(address);
    for (uint8_t i = 0; i < count; i++)
        data[i] = mcp_spi_read();
    mcp_slave_deselect();
}

void mcp_write(uint8_t address, uint8_t data) {
    mcp_slave_select();
    mcp_spi_write(MCP_WRITE);
    mcp_spi_write(address);
    mcp_spi_write(data);
    mcp_slave_deselect();
}

void mcp_write_many(uint8_t address, uint8_t *data, uint8_t count) {
    mcp_slave_select();
    mcp_spi_write(MCP_WRITE);
    mcp_spi_write(address);
    for (uint8_t i = 0; i < count; i++)
        mcp_spi_write(data[i]);
    mcp_slave_deselect();
}

void mcp_request_to_send(uint8_t bitflag) {
    mcp_slave_select();
    mcp_spi_write(MCP_RTS | (bitflag & 7));
    mcp_slave_deselect();
}

void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
    mcp_slave_select();
    mcp_spi_write(MCP_BIT_MODIFY);
    mcp_spi_write(address);
    mcp_spi_write(mask);
    mcp_spi_write(data);
    mcp_slave_deselect();
}

void mcp_reset(void) {
    mcp_slave_select();
    mcp_spi_write(MCP_RESET);
    mcp_slave_deselect();
}

mcp_status mcp_get_status()
{
    mcp_slave_select();
    mcp_spi_write(MCP_READ_STATUS);
    uint8_t data = mcp_spi_read();
    mcp_slave_deselect();

    // See page 69, figure 12-8 for a description of the return data
    mcp_status status;
    status.message_in_rx0 = data & 0b00000001;
    status.message_in_rx1 = data & 0b00000010;
    status.tx0_pending    = data & 0b00000100;
    status.tx1_pending    = data & 0b00001000;
    status.tx2_pending    = data & 0b00010000;
    status.tx0_sent       = data & 0b00100000;
    status.tx1_sent       = data & 0b01000000;
    status.tx2_sent       = data & 0b10000000;
    return status;
}

mcp_tx_status mcp_get_tx_status(uint8_t which)
{
    uint8_t data = 0;
    if (which == 0) data = mcp_read(MCP_TXB0CTRL);
    if (which == 1) data = mcp_read(MCP_TXB1CTRL);
    if (which == 2) data = mcp_read(MCP_TXB2CTRL);

    // See page 18, register 3-1 for description of the data
    mcp_tx_status status;
    status.aborted = data & 0b01000000; // message aborted
    status.lost    = data & 0b00100000; // message lost arbitration
    status.error   = data & 0b00010000; // a bus error occurred
    status.pending = data & 0b00001000; // still waiting to transmit
    return status;
}

void mcp_mode_config() {
    mcp_bit_modify(MCP_CANCTRL, MCP_REQOP, MCP_REQOP_CONFIG);
}

void mcp_mode_loopback() {
    mcp_bit_modify(MCP_CANCTRL, MCP_REQOP, MCP_REQOP_LOOPBACK);
}

void mcp_mode_normal() {
    mcp_bit_modify(MCP_CANCTRL, MCP_REQOP, MCP_REQOP_NORMAL);
}

void mcp_send_message(uint16_t id, uint8_t *data, uint8_t length) {
	
	// Clamp the length. You can send at most 8 bytes.
	if (length > 8)
		length = 8;
	
    // Write the ID
    uint8_t id_high = (uint8_t)(id >> 3);
    uint8_t id_low = (uint8_t)((id & 0b111) << 5);
    mcp_write(MCP_TXB0SIDH, id_high);
    mcp_write(MCP_TXB0SIDL, id_low);

    // Write length of message (0 to 8 bytes) (last 4 bits of DLC)
    // Note: this also sets RTR to 0 (indicating a data frame)
    // Note: it is possible to set the value greater than 8, but only
    // 8 bytes are allowed anyway.
    mcp_write(MCP_TXB0DLC, length & 0b1111);

    // Write the data bytes
    mcp_write_many(MCP_TXB0D0, data, length);

    // Flag the message buffer as being ready for transmission
    mcp_request_to_send(MCP_RTS0);
}

int mcp_read_message(uint16_t *id, uint8_t *data, uint8_t *length) {
    uint8_t msg[13];

    mcp_status s = mcp_get_status();
    if (s.message_in_rx0)
    {
        mcp_read_many(MCP_RXB0SIDH, msg, 13);
        mcp_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
    }
    else if (s.message_in_rx1)
    {
        mcp_read_many(MCP_RXB1SIDH, msg, 13);
        mcp_bit_modify(MCP_CANINTF, MCP_RX1IF, 0);
    }
    else
    {
        return 0;
    }

    uint16_t id_high = msg[0];
    uint16_t id_low = (msg[1] >> 5);
    *id = (id_high << 3) | (id_low);

    // extended ID (unused)
    // uint8_t eid_high = msg[2];
    // uint8_t eid_low = msg[3];

    *length = msg[4] & 0b1111;
    for (uint8_t i = 0; i < *length; i++)
        data[i] = msg[5+i];

    return 1;
}
