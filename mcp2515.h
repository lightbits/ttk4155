#ifndef MCP2515_H
#define MCP2515_H
#include <avr/io.h>
#include "mcp2515_registers.h"

//
// The MCP2515 needs a SPI interface with Phase/Polarity 0,0 or 1,1
// Maximum data rate 10 MHz. You define these functions.
//
void mcp_spi_init(); // Enable CS output and enable SPI
void mcp_slave_select(); // Set CS low
void mcp_slave_deselect(); // Set CS high
uint8_t mcp_spi_write(uint8_t x);
uint8_t mcp_spi_read();

//
// CAN messaging interface
//
// Note: sending messages will use the 0'th transmission buffer
// Reading a message will return a message from any of the receive
// buffers. The return value is 1 if there was a message available
// and 0 otherwise.
void mcp_send_message(uint16_t id, uint8_t *data, uint8_t length);
int  mcp_read_message(uint16_t *id, uint8_t *data, uint8_t *length);

//
// MCP controller interface
//
void mcp_init(void);
void mcp_mode_config(void);
void mcp_mode_loopback(void);
void mcp_mode_normal(void);
uint8_t mcp_read(uint8_t address);
void mcp_write(uint8_t address, uint8_t data);
void mcp_write_many(uint8_t address, uint8_t *data, uint8_t count);
void mcp_read_many(uint8_t address, uint8_t *data, uint8_t count);
void mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp_reset(void);

// The bitflag describes which of the three buffers that should be sent.
// It can be any combination: e.g. request_to_send(MCP_RTS0 | MCP_RTS2).
#define MCP_RTS0 1
#define MCP_RTS1 2
#define MCP_RTS2 4
void mcp_request_to_send(uint8_t bitflag);

// Return short status of transmission buffers and receive buffers
typedef struct
{
    int message_in_rx0;
    int message_in_rx1;
    int tx0_pending;
    int tx1_pending;
    int tx2_pending;
    int tx0_sent;
    int tx1_sent;
    int tx2_sent;
} mcp_status;
mcp_status mcp_get_status();

// Return detailed status of a specific transmission buffer (0, 1 or 2)
typedef struct
{
    int aborted; // message aborted
    int lost;    // message lost arbitration
    int error;   // a bus error occurred
    int pending; // still waiting to transmit
} mcp_tx_status;
mcp_tx_status mcp_get_tx_status(uint8_t which);

#endif
