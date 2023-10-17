#include <avr/io.h>
#include <util/delay_basic.h>
#include "usart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "can.h"
#include "interrupts.h"


int main(void)
{
	usart_init(USART_BAUD_RATE_REGISTER);
	printf("hello world ");

	xmem_init();
	adc_init();
	OLED_init();
	menu_init();
	interrupt_init();
	can_init();
	
	int j = 0;
	while(1)
	{
		input_t input;
		for(int i = 0; i < 10; i++)
		{
			input = input_read();
			_delay_ms(25);
			joystick_loop(input);
			menu_input_loop(input);
		}
		menu_draw_loop(input);
	}
	
}

