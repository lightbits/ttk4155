#ifndef MCP2515_H
#define MCP2515_H
#include "common.h"
#include "mcp2515_registers.h"

void mcp_init(void);
void mcp_mode_config(void);
void mcp_mode_loopback(void);
void mcp_mode_normal(void);
uint8_t mcp_read(uint8_t address);
int mcp_write(uint8_t address, uint8_t data);
int mcp_write_many(uint8_t address, uint8_t *data, uint8_t count);
void mcp_read_many(uint8_t address, uint8_t *data, uint8_t count);
int mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
int mcp_reset(void);

// The bitflag describes which of the three buffers that should be sent.
// It can be any combination: e.g. request_to_send(MCP_RTS0 | MCP_RTS2).
#define MCP_RTS0 1
#define MCP_RTS1 2
#define MCP_RTS2 4
int mcp_request_to_send(uint8_t bitflag);

// Return short status of transmission buffers and receive buffers
struct mcp_status
{
    bool message_in_rx0;
    bool message_in_rx1;
    bool tx0_pending;
    bool tx1_pending;
    bool tx2_pending;
    bool tx0_sent;
    bool tx1_sent;
    bool tx2_sent;
};
mcp_status mcp_get_status();

// Return detailed status of a specific transmission buffer (0, 1 or 2)
struct mcp_tx_status
{
    bool aborted; // message aborted
    bool lost;    // message lost arbitration
    bool error;   // a bus error occurred
    bool pending; // still waiting to transmit
};
mcp_tx_status mcp_get_tx_status(uint8_t which);

#endif
