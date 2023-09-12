#ifndef ADC_H_
#define ADC_H_


#define FREQUENCY_OF_OSCILLATOR 4915200
#define BASE_ADDRESS_ADC 0x1400;
#include <avr/io.h>
#include <math.h>
#include <util/delay_basic.h>

typedef struct pos_t
{
	uint8_t x;
	uint8_t y;
} pos_t;

pos_t pos_start;

uint8_t adc_init();
uint8_t joystick_angle_from_voltage(uint8_t voltage);
pos_t joystick_read();
uint8_t joystick_calibrate();



#endif