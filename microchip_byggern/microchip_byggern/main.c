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
	// mcp2515_init();
	//SPI_init();
	
	//mcp2515_write('9');
	/*mcp2515_write(0x36, '8');
	mcp2515_write(0x36, '8');
	mcp2515_write(0x36, '8');
	
	uint8_t result = mcp2515_read(0x36);
	printf("   %d ",result);*/
	
	int j = 0;
	while(1){
		can_message msg;
		msg.id = 0;
		msg.data_length = 8;
		j = (j+1) % 10;
		msg.data[0] = 'A' + j;
		msg.data[1] = '9';
		msg.data[2] = 'A';
		can_message_send(msg);
		printf("    sending mcp msg");
		
		//mcp2515_write(MCP_TXB0D0, msg.data[0]);
		/*_delay_ms(500);
		printf("   mcp data ");
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", mcp2515_read(MCP_TXB0D0+i));
		}*/
		
		
		
		_delay_ms(5000);
		//printf("%d", can_data_receive().data[0]);
	}
	

	
	
	
	
	
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

