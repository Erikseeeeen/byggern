#include <avr/io.h>
#include <util/delay_basic.h>
#include "usart.h"
#include "xmem.h"
#include "sram_test.h"

int main(void)
{
	usart_init(USART_BAUD_RATE_REGISTER);
	xmem_init();
	
	
    // Set port A pin 0 as output
    DDRA |= 1 << 0;
    
    while (1) 
    {
        // Set port A pin 0 high
		PORTA |= 1 << 0;
		xmem_write(14, 255);
        _delay_loop_2(65530);
        // Set port A pin 0 low
        PORTA &= ~(1 << 0);
        xmem_write(14, 0);
        _delay_loop_2(65530);
		// printf("Please work");
    }
}

