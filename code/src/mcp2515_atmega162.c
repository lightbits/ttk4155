//
// This is code specific to the Arduino (ATmega162) for using the MCP2515.
// It assumes the MCP is connected to the SPI port, with CS (chip select)
// connected to PB4.
//
#include "../../mcp2515.h"
#include "../../spi.h"
#include "common.h"
#define MCP_SS PB4
void mcp_spi_init() { set_bit(DDRB, MCP_SS); spi_init(); }
void mcp_slave_select() { clear_bit(PORTB, MCP_SS); }
void mcp_slave_deselect() { set_bit(PORTB, MCP_SS); }
uint8_t mcp_spi_write(uint8_t x) { return spi_write(x); }
uint8_t mcp_spi_read() { return spi_read(); }
