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
	OLED_init();
	menu_init();
	
	printf("hello world\n");
	
	
	
	int i = 0;
	while(1)
	{
		if(!(i % 1000000))
		{
			input_t input = input_read();
			menu_loop(input);
		}
		
		//input_t input = input_read();
		//printf("Joystick x: %8d y: %8d                                                ", input.joystick_x, input.joystick_y);
		//printf("Button   l: %8d r: %8d                                                ", input.button_left, input.button_right);
		//printf("Slider   1: %8d 2: %8d                                                ", input.slider_1, input.slider_2);
		
		
		/*volatile char* ext_mem = (char*) 0x1100;
		ext_mem[10] = 0;*/
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

