#include "usart.h"

void usart_init(unsigned int usart_baud_rate_register)
{
    // Set baud rate registers
    UBBR0H = (unsigned char)(usart_baud_rate_register>>8); // usart_baud_rate_register_high
    UBBR0L = (unsigned char)usart_baud_rate_register; // usart_baud_rate_register_low
    
    // Enable RX and TX registers
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Universal Synchronous Asynchronous Receiver Transmitter Register B, RX Enable, TX Enable
    
    // Set frame format to 8 data bits, 2 stop bits
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ0); // Universal Synchronous Asynchronous Receiver Transmitter Register C, USART Register Select, USART Stop Bit Select, USART Character Size Select

    
}
void USART_Transmit(unsigned char data)
{
    // Wait until the transmitter buffer is empty
    while ( !( UCSR0A & (1<<UDRE0)) ); // USART Control and Status Register A, USART Data Register Empty
    // Send data
    UDR0 = data; // USART Data Register
}

unsigned char USART_Receive(void)
{
    // Wait for data to be received
    if ( !(UCSR0A & (1<<RXC0)) ) // USART Control and Status Register A, USART Receive Complete
        return '\0';
    // Return data received
    return UDR0; // USART Data Register
}