#ifndef OLED_H_
#define OLED_H_


#include "adc.h"
#include "oled.h"
#include "can.h"

const char* menu_items[2][1];

typedef struct MENU_INFO
{
	uint8_t number_of_items;
	uint8_t select_jump[5];
} MENU_INFO;


const MENU_INFO menu_info[2];

input_t last_input;
uint8_t selected_position;
uint8_t current_menu;

void menu_init();
void menu_loop();

#endif