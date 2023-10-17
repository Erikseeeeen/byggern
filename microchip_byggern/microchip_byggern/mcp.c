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
	
    mcp2515_bit_modify(MCP_CANINTE, 0b00000001, 0b00000001); // Enable Message received interrupt
	
	// Can bus Bit timing
	mcp2515_bit_modify(MCP_CNF1, 0b00111111, 0b00000011); // T_Q = 500ns
	mcp2515_bit_modify(MCP_CNF1, 0b11000000, 0b00000000); // Synchronization Jump Width Length = 1*T_Q
	mcp2515_bit_modify(MCP_CNF2, 0b11111111, 0b10110001); // Phase 1 length = 7*T_Q, Propagation Segment = 2*T_Q, BUs Line sampled once and Length of Phase 2 determined by CNF3
	mcp2515_bit_modify(MCP_CNF3, 0b00000111, 0b00000101); // Phase 2 length = 6*T_Q
	
	mcp2515_bit_modify(MCP_RXB0CTRL, 0b01100000, 0b01100000); // Disable masks - receive all messages
	
	
	//printf("%02x ", mcp2515_read(MCP_CNF1));
	//printf("%02x ", mcp2515_read(MCP_CNF2));
	//printf("%02x ", mcp2515_read(MCP_CNF3));
	
    
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