#ifndef ADC_H_
#define ADC_H_


#define FREQUENCY_OF_OSCILLATOR 4915200
#define BASE_ADDRESS_ADC 0x1400;
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


typedef enum Direction {
	CENTER,
	UP,
	RIGHT,
	DOWN,
	LEFT
}Direction;

typedef struct input_t
{
	uint8_t joystick_x;
	uint8_t joystick_y;
	uint8_t slider_1;
	uint8_t slider_2;
	uint8_t button_right;
	uint8_t button_left;
	Direction direction;
} input_t;

input_t input_buffer[10];
int input_head = 0;

uint8_t adc_init();
input_t input_read();



#endif