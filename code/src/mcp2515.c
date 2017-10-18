#include <avr/io.h>
#include "spi.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"

int mcp_init(void) {

	// Initialize SPI
	SPI_init();

	// Reset CAN-controller
	mcp_reset();

	return 0;
}

uint8_t mcp_read(uint8_t address) {

	uint8_t data;

	// Activate slave select
	SPI_slave_select();

	// Read instruction
	SPI_write(MCP_READ);
	SPI_write(address);
	data = SPI_read();

	// Deactivate slave select
	SPI_slave_deselect();

	return data;
}

void mcp_read_many(uint8_t address, uint8_t *data, uint8_t count) {

	// Activate slave select
	SPI_slave_select();

	// Read instruction
	SPI_write(MCP_READ);
	SPI_write(address);
	for (uint8_t i = 0; i < count; i++)
		data[i] = SPI_read();

	// Deactivate slave select
	SPI_slave_deselect();
}

int mcp_write(uint8_t address, uint8_t data) {

	// Activate slave select
	SPI_slave_select();

	// Byte write instruction
	SPI_write(MCP_WRITE);
	SPI_write(address);
	SPI_write(data);

	// Deactivate slave select
	SPI_slave_deselect();

	return 0;
}

int mcp_write_many(uint8_t address, uint8_t *data, uint8_t count) {

	// Activate slave select
	SPI_slave_select();

	// Byte write instruction
	SPI_write(MCP_WRITE);
	SPI_write(address);
	for (uint8_t i = 0; i < count; i++)
		SPI_write(data[i]);

	// Deactivate slave select
	SPI_slave_deselect();

	return 0;
}

int mcp_request_to_send(uint8_t bitflag) {
	// Activate slave select
	SPI_slave_select();

	// Request-to-send instruction
	SPI_write(MCP_RTS | (instr & 7));

	// Deactivate slave select
	SPI_slave_deselect();

	return 0;
}

int mcp_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {

	// Activate slave select
	SPI_slave_select();

	// Bit modify instruction
	SPI_write(MCP_BIT_MODIFY);
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);

	// Deactivate slave select
	SPI_slave_deselect();

	return 0;
}

int mcp_reset(void) {

	// Activate slave select
	SPI_slave_select();

	// Reset instruction
	SPI_write(MCP_RESET);

	// Deactivate slave select
	SPI_slave_deselect();

	return 0;
}



uint8_t mcp_read_status(void) {
	uint8_t status;

	// Activate slave select
	SPI_slave_select();

	// Read status instruction
	SPI_write(MCP_READ_STATUS);
	status = SPI_read();

	// Deactivate slave select
	SPI_slave_deselect();

	return status;
}
