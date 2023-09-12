#include "adc.h"


uint8_t adc_init()
{/*
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS11);
	
	OCR1A = (FREQUENCY_OF_OSCILLATOR / (2 * 64 * FREQUENCY_OF_OSCILLATOR)) -1;
	
	TCNT1 = 0; // Enable counter*/

	DDRD |= 1 << PD4;
	TCCR3A |= (1 << COM3A0); // Toggle on compare
	TCCR3B |= (1 << WGM33) | (1 << WGM32);
	TCCR3A |= (1 << WGM31) | (1 << WGM30); // Fast PWM OCRnA, datasheet p.130
	TCCR3B |= (1 << CS30); // No prescaling, datasheet p.132
	OCR3A = 0;
	
	pos_start.x = 0;
	pos_start.y = 0;
	
	_delay_loop_2(65000);
	_delay_loop_2(65000);
	_delay_loop_2(65000);
	_delay_loop_2(65000);
	_delay_loop_2(65000);
	_delay_loop_2(65000);
	_delay_loop_2(65000);
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
	float y_raw = *adc_out;
	float x_raw = *adc_out;
	
	const double PI =  3.1415926;
	
	/*float y_asin = asin((y_raw / (float)(127.5) - 1) * 0.8);
	float x_asin = asin((x_raw / (float)(127.5) - 1) * 0.8);
	
	
	
	float y_asin_scaled =  (y_asin + PI / 2) / (2 * PI);
	float x_asin_scaled =  (x_asin + PI / 2) / (2 * PI);*/
	
	
	joystick_pos.y = (uint8_t)(y_raw - 175);
	joystick_pos.x = (uint8_t)(x_raw - 198);
	
	return joystick_pos;
}

uint8_t joystick_calibrate()
{
	pos_t joystick_pos = joystick_read();
	pos_start.x = joystick_pos.x;
	pos_start.y = joystick_pos.y;
}