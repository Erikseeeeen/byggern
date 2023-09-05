#include "usart.h"

// static FILE usart_stream_write = FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);
// static FILE usart_stream_read = FDEV_SETUP_STREAM(NULL, USART_Transmit, _FDEV_SETUP_READ);

void usart_init(unsigned int usart_baud_rate_register)
{
    // Open read/write stream over USART https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gab599ddf60819df4cc993c724a83cb1a4
    fdevopen(USART_Transmit, USART_Receive);
    // Set baud rate registers
    UBRR0H = (unsigned char)(usart_baud_rate_register>>8); // usart_baud_rate_register_high
    UBRR0L = (unsigned char)usart_baud_rate_register; // usart_baud_rate_register_low
    
    // Enable RX and TX registers
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Universal Synchronous Asynchronous Receiver Transmitter Register B, RX Enable, TX Enable
    
	
    // Set frame format to 8 data bits, 2 stop bits
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // Universal Synchronous Asynchronous Receiver Transmitter Register C, USART Register Select, USART Stop Bit Select, USART Character Size Select

    // Test printf
	char* Jorge_height = "187";
    printf(Jorge_height);
    
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