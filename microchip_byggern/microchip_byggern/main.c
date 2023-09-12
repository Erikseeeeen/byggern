#include <avr/io.h>
#include <util/delay_basic.h>
#include "usart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"


int main(void)
{
	usart_init(USART_BAUD_RATE_REGISTER);
	xmem_init();
	adc_init();
	
	printf("Hello world\n");
	
	while(1)
	{
		pos_t joystick_pos = joystick_read();
		printf("Joystick x: %8d y: %8d                                                ", joystick_pos.x, joystick_pos.y);
	}
	
	//SRAM_test();
	
	/*volatile char* ext_mem = (char*) 0x1800;
	for(uint8_t i = 0; i < 255; i++)
	{
		for(uint8_t j = 0; j < 255; j++)
		{
			_delay_loop_2(6);
			printf("%d\n", i);
			ext_mem[15] = 0;
		}
	}*/
    
    /*while (1) 
    {
		PORTA |= 1 << 0;
        // Set port A pin 0 high
        xmem_write(0, 15);
        _delay_loop_2(65000);
        // Set port A pin 0 low
        xmem_write(0, 0);
        _delay_loop_2(65000);
		// printf("Please work");
    }*/
}

