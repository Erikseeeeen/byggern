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
    mcp2515_bit_modify(MCP_TXRTSCTRL, 0b00000001, 0b00000001);
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

void mcp2515_write(uint8_t address, uint8_t data)
{
    // MCU selects one of the slaves by setting its corresponding SS signal to low
    PORTB &= ~(1 << PB4 ); // Select CAN - controller
    
    SPI_write (MCP_WRITE);
    SPI_write (address);
    SPI_write (data);
    
    PORTB |= (1 << PB4 ); // Deselect CAN - controller
}

void mcp2515_write_bytes(uint8_t address, uint8_t* data, uint8_t data_length)
{
    // MCU selects one of the slaves by setting its corresponding SS signal to low
    PORTB &= ~(1 << PB4 ); // Select CAN - controller
    
    SPI_write (MCP_WRITE);
    SPI_write (address);
    for(int i = 0; i < data_length; i++)
    {
        SPI_write (data[i]);
    }
    
    PORTB |= (1 << PB4 ); // Deselect CAN - controller
}

void mcp2515_request_to_send()
{
    SPI_write(MCP_RTS_TX0);
}
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	PORTB &= ~(1 << PB4 ); // Select CAN - controller
    SPI_write(MCP_BITMOD);
    SPI_write(address);
    SPI_write(mask);
    SPI_write(data);
    PORTB |= (1 << PB4 ); // Deselect CAN - controller
}
void mcp2515_reset()
{
    SPI_write(MCP_RESET);
	
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);
}
uint8_t mcp2515_read_status()
{
    SPI_write ( MCP_READ_STATUS ); // Send address
    uint8_t result = SPI_read () ; // Read result
    return result;
}