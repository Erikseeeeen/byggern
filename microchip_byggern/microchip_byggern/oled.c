#include "oled.h"
#include <avr/pgmspace.h>

void OLED_init()
{
	
	OLED_write_command(0xae); // display off
	OLED_write_command(0xa1); //segment remap
	OLED_write_command(0xda); //common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xc8); //common output scan direction:com63~com0
	OLED_write_command(0xa8); //multiplex ration mode:63
	OLED_write_command(0x3f);
	OLED_write_command(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81); //contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xd9); //set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20); //Set Memory Addressing Mode
	OLED_write_command(0x02);
	OLED_write_command(0xdb); //VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xad); //master configuration
	OLED_write_command(0x00);
	OLED_write_command(0xa4); //out follows RAM content
	OLED_write_command(0xa6); //set normal display
	OLED_write_command(0xaf); // display on
	
	//OLED_write_command(0xa5);
	/*OLED_write_command(0xb0); // Set the page start address of the target display location by command B0h to B7h
	OLED_write_command(0x00); // Set the lower start column address of pointer by command 00h~0Fh.
	OLED_write_command(0x10); // Set the upper start column address of pointer by command 10h~1Fh*/
	
	OLED_reset();
	OLED_pos(0, 0);
	
	
	
	/*for(int i = 0; i < 30; i++){
	OLED_print_character(i);
	
	}*/
	/*OLED_write_data(0b00000000);
	OLED_write_data(0b00000110);
	OLED_write_data(0b01011111);
	OLED_write_data(0b01011111);
	OLED_write_data(0b00000110);
	OLED_write_data(0b00000000);
	OLED_write_data(0b00000000);
	OLED_write_data(0b00000000);*/
	
} // PDF:"OLED LY190-128064" section 9.4



void OLED_reset()
{
	for (int page = 0; page < 8; page++)
	{
		OLED_write_command(0xb0 + page); // Set the page start address of the target display location by command B0h to B7h
		OLED_write_command(0x00); // Set the lower start column address of pointer by command 00h~0Fh.
		OLED_write_command(0x10); // Set the upper start column address of pointer by command 10h~1Fh
		
		for (int i = 0; i < 128; i++)
		{
			OLED_write_data(0);
		}
	}
}
void OLED_home();
void OLED_goto_line(uint8_t line);

void OLED_clear_line(uint8_t line)
{
	
}
void OLED_pos(uint8_t row, uint8_t column)
{
	OLED_write_command(0xb0 + row / 8); // Set the page start address of the target display location by command B0h to B7h
	OLED_write_command(0x00 + column % 16); // Set the lower start column address of pointer by command 00h~0Fh.
	OLED_write_command(0x10 + column / 16); // Set the upper start column address of pointer by command 10h~1Fh
}
void OLED_write_data(char data)
{
	volatile char* oled_data_register = (char*) BASE_ADDRESS_OLED_DATA;
	oled_data_register[0] = data;
}
void OLED_write_command(char data)
{
	volatile char* oled_command_register = (char*) BASE_ADDRESS_OLED_COMMAND;
	oled_command_register[0] = data;
}
void OLED_print(char* string)
{
	int i = 0;
	while(string[i] != '\0')
	{
		OLED_print_character(string[i] - 32);
		i++;
	}
}

void OLED_print_character(char character)
{
	for (int row = 0; row < 8; row++)
	{
		OLED_write_data(pgm_read_byte(&(font8[character][row])));
	}
}
void OLED_set_brightness(uint8_t lvl);

void OLED_print_arrow ( uint8_t row , uint8_t col )
{
	OLED_pos ( row , col );
	OLED_write_data (0b00011000 );
	OLED_write_data (0b00011000 );
	OLED_write_data (0b01111110 );
	OLED_write_data (0b00111100 );
	OLED_write_data (0b00011000 );
}

