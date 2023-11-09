#include <avr/io.h>
#include <util/delay_basic.h>
#include "usart.h"
#include "xmem.h"
#include "sram_test.h"
#include "adc.h"
#include "can.h"
#include "interrupts.h"
#include "menu.h"

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
	
	//int j = 0;
	input_t input;
	while(1)
	{
		for(int i = 0; i < 100; i++)
		{
			input = input_read();
			menu_input_loop(input);
			joystick_loop(input, current_menu);
			_delay_ms(1);
		}
		menu_draw_loop(input);
	}
	
}

