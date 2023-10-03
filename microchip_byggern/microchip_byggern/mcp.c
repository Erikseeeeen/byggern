#include "mcp.h"

uint8_t mcp2515_init ()
{
    DDRB |= (1 << PB4 ); // Set CS - pin as output

    
    SPI_init () ; // Initialize SPI
    mcp2515_reset () ; // Send reset - command
    // Self - test
    uint8_t value = mcp2515_read ( MCP_CANSTAT  );
    if (( value & MODE_MASK ) != MODE_CONFIG ) {
        printf (" MCP2515 is NOT in configuration mode after reset !\n");
        return 1;
    }
    // More initialization
    return 0;
}
uint8_t mcp2515_read ( uint8_t address )
{
    uint8_t result ;
    PORTB &= ~(1 << PB4 ); // Select CAN - controller
    SPI_write ( MCP_READ ); // Send read instruction
    SPI_write ( address ); // Send address
    result = SPI_read () ; // Read result
    PORTB |= (1 << PB4 ); // Deselect CAN - controller
    return result ;
}

void mcp2515_write(uint8_t data)
{
    // MCU selects one of the slaves by setting its corresponding SS signal to low
    PORTB &= ~(1 << PB4 ); // Select CAN - controller
    // In order to initiate message transmission, the
    // TXBnCTRL.TXREQ bit must be set for each buffer to
    // be transmitted. This can be accomplished by:
    // • Writing to the register via the SPI write command
	SPI_write(MCP_TXB0CTRL);
	SPI_write(0b00001000);
	
    // • Sending the SPI RTS command
	mcp2515_request_to_send();
    // • Setting the TXnRTS pin low for the particular transmit buffer(s) that are to be transmitted
	// SPI_write(TXnRTS)??????
    
    SPI_write (data); 
    PORTB |= (1 << PB4 ); // Deselect CAN - controller
}
void mcp2515_request_to_send()
{
    SPI_write(MCP_RTS_TX0);
}
void mcp2515_bit_modify()
{
    SPI_write(MCP_BITMOD);
}
void mcp2515_reset()
{
    SPI_write(MCP_RESET);
	
    SPI_write(MCP_CANCTRL);
    SPI_write(MODE_CONFIG);
}
uint8_t mcp2515_read_status()
{
    SPI_write ( MCP_READ_STATUS ); // Send address
    result = SPI_read () ; // Read result
    return result;
}