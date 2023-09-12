#include "usb_card.h"


uint8_t usb_card_init()
{/*
	DDRD |= 1 << 4;
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS11);
	
	OCR1A = (FREQUENCY_OF_OSCILLATOR / (2 * 64 * FREQUENCY_OF_OSCILLATOR)) -1;
	
	TCNT1 = 0; // Enable counter*/
	
	
	joystick_calibrate();
}

uint8_t joystick_angle_from_voltage(uint8_t voltage)
{
	return voltage;
}

pos_t joystick_read(){
	volatile char* adc_out = (char*) BASE_ADDRESS_ADC;
	adc_out[0] = 0;
	
	// Wait for busy
	
	pos_t joystick_pos;
	joystick_pos.x = *adc_out;
	joystick_pos.y = *adc_out;
	
	return joystick_pos;
}

uint8_t joystick_calibrate()
{
	
}