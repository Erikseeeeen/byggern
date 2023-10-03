#include "can.h"

void can_init()
{
    // Set to loopback mode
    mcp2515_init();
}
void can_message_send(can_message message)
{
    // Send a message with a given ID and data
    // (for instance, by passing a struct containing the ID, length and data to a send function)
}
can_message can_data_receive()
{

}
void can_int_vect()
{
    
}
