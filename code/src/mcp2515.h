#ifndef MCP2515_H
#define MCP2515_H
#include "common.h"


int mcp_init(void);
uint8_t mcp_read(uint8_t address);
int mcp_write(uint8_t address, uint8_t data);
int mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
int mcp_reset(void);
uint8_t mcp_read_status(void);

// The bitflag describes which of the three buffers that should be sent.
// It can be any combination: e.g. request_to_send(MCP_RTS0 | MCP_RTS2).
#define MCP_RTS0 1
#define MCP_RTS1 2
#define MCP_RTS2 4
int mcp_request_to_send(uint8_t bitflag);

#endif
