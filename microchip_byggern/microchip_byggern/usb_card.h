#ifndef USB_CARD_H_
#define USB_CARD_H_


#define FREQUENCY_OF_OSCILLATOR 4915200
#define BASE_ADDRESS_ADC 0x1400;
#include <avr/io.h>

typedef struct pos_t
{
	uint8_t x;
	uint8_t y;
} pos_t;

uint8_t usb_card_init();
uint8_t joystick_angle_from_voltage(uint8_t voltage);
pos_t joystick_read();
uint8_t joystick_calibrate();



#endif