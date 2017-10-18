#ifndef MCP2515_H
#define MCP2515_H
#include "common.h"

int mcp_init(void);
uint8_t mcp_read(uint8_t address);
int mcp_write(uint8_t address, uint8_t data);
int mcp_request_to_send(uint8_t instr);
int mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
int mcp_reset(void);
uint8_t mcp_read_status(void);

#endif
