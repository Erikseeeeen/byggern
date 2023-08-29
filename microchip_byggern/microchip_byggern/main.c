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
	
    DDRA |= 1 << 0;
    /* Replace with your application code */
    while (1) 
    {
		USART_Transmit('a');
        PORTA |= 1 << 0;
        _delay_loop_2(6553);
        PORTA &= ~(1 << 0);
        _delay_loop_2(6553);
    }
	
	
}

