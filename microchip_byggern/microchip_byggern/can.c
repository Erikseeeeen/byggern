#include "can.h"

void can_init()
{
    // Set to loopback mode
    mcp2515_init();
	
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
}
void can_message_send(can_message message)
{
    // Send a message with a given ID and data
    // (for instance, by passing a struct containing the ID, length and data to a send function)
    // In order to initiate message transmission, the
    // TXBnCTRL.TXREQ bit must be set for each buffer to
    // be transmitted. This can be accomplished by:
    // • Writing to the register via the SPI write command
    mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001000, 0b00001000);
    
    // • Sending the SPI RTS command
    mcp2515_request_to_send();
    // • Setting the TXnRTS pin low for the particular transmit buffer(s) that are to be transmitted
    // If configured to operate as a request-to-send pin, the pin is mapped into the respective TXBnCTRL.TXREQ bit for the transmit buffer
    
    mcp2515_write(TXB0SIDH, message.id >> 8);
    mcp2515_write(TXBnSIDL, message.id);
    mcp2515_write(TXBnDLC, message.data_length);
    

	mcp2515_write_bytes(TXB0D0, message.data, message.data_length);
}
can_message can_data_receive()
{

}
void can_int_vect()
{
    
}
