#include "usart.h"

void usart_init(unsigned int usart_baud_rate_register)
{
    // Set baud rate registers
    UBBRH = (unsigned char)(usart_baud_rate_register>>8); // usart_baud_rate_register_high
    UBBRL = (unsigned char)usart_baud_rate_register; // usart_baud_rate_register_low
    
    // Enable RX and TX registers
    UCSRB = (1<<RXEN) | (1<<TXEN); // Universal Synchronous Asynchronous Receiver Transmitter Register B, RX Enable, TX Enable
    
    // Set frame format to 8 data bits, 2 stop bits
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0); // Universal Synchronous Asynchronous Receiver Transmitter Register C, USART Register Select, USART Stop Bit Select, USART Character Size Select

    
}
void USART_Transmit(unsigned char data)
{
    // Wait until the transmitter buffer is empty
    while ( !( UCSRA & (1<<UDRE)) ); // USART Control and Status Register A, USART Data Register Empty
    // Send data
    UDR = data; // USART Data Register
}

unsigned char USART_Receive(void)
{
    // Wait for data to be received
    if ( !(UCSRA & (1<<RXC)) ) // USART Control and Status Register A, USART Receive Complete
        return '\0'
    // Return data received
    return UDR; // USART Data Register
}