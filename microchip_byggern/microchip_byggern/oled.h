#ifndef OLED_H_
#define OLED_H_

#define BASE_ADDRESS_OLED_COMMAND 0x1000
#define BASE_ADDRESS_OLED_DATA 0x1200

#include <stdint.h>
#include "fonts.h"

// Function prototypes from lab lecture

void OLED_init(); // PDF:"OLED LY190-128064" section 9.4
void OLED_reset();
void OLED_home();
void OLED_goto_line(uint8_t line);
void OLED_clear_line(uint8_t line);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_write_data(char data); //volatile
void OLED_write_command(char data);
void OLED_print(char*);
void OLED_print_character(char);
void OLED_set_brightness(uint8_t lvl);void OLED_print_arrow ( uint8_t row , uint8_t col );

uint16_t offset = 0;



#endif /* OLED_H_ */