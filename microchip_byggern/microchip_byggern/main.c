/*
 * microchip_byggern.c
 *
 * Created: 29.08.2023 08:46:19
 * Author : eiviser
 */ 

#include <avr/io.h>
#include <util/delay_basic.h>
#include "usart.h"

int main(void)
{
	usart_init(USART_BAUD_RATE_REGISTER);
    // Mask out some port C address pins for JTAG (datasheet page 32)
    SFIOR |= 1 << XMM0;
    SFIOR &= ~(1 << XMM0 | 1 << XMM1);
	
    // Set port A pin 0 as output
    DDRA |= 1 << 0;
    
    while (1) 
    {
	    USART_Transmit('a');
        // Set port A pin 0 high
		PORTA |= 1 << 0;
        _delay_loop_2(6553);
        // Set port A pin 0 low
        PORTA &= ~(1 << 0);
        _delay_loop_2(6553);
    }
}

