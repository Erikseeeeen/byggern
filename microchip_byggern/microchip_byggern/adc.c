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
	
	// Enable button input
	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD3);
	input_head = 0;
}

uint8_t joystick_angle_from_voltage(uint8_t voltage)
{
	return voltage;
}

input_t input_read(){
	volatile char* adc_out = (char*) BASE_ADDRESS_ADC;
	adc_out[0] = 0;
	
	// Wait for busy
	//_delay_ms(2);
	
	input_t input;
	uint8_t y_raw = *adc_out;
	uint8_t x_raw = *adc_out;
	uint8_t slider1_raw = *adc_out;
	uint8_t slider2_raw = *adc_out;
	
	const double PI =  3.1415926;	
	
	uint8_t y_positive = MAX(y_raw, 175) - 175;
	uint8_t x_positive = MAX(x_raw, 198) - 198;
	
	uint8_t y_positive_scaled = (uint8_t)((float)y_positive * ((float)127/(float)80));
	uint8_t x_positive_scaled = (uint8_t)((float)x_positive * ((float)127/(float)57));
	
	uint8_t y_negative = 175 - MIN(y_raw, 175);
	uint8_t x_negative = 198 - MIN(x_raw, 198);
	
	uint8_t y_negative_scaled = (uint8_t)((float)y_negative * ((float)127/(float)175));
	uint8_t x_negative_scaled = (uint8_t)((float)x_negative * ((float)127/(float)198));
	
	input.joystick_y = (uint8_t)((128 - y_negative_scaled) + y_positive_scaled);
	input.joystick_x = (uint8_t)((128 - x_negative_scaled) + x_positive_scaled);
	
	input.direction = CENTER;
	if(input.joystick_y > 198)
		input.direction = UP;
	if(input.joystick_x > 198)
		input.direction = RIGHT;
	if(input.joystick_y < 68)
		input.direction = DOWN;
	if(input.joystick_x < 68)
		input.direction = LEFT;
	
	input.slider_1 = slider1_raw;
	input.slider_2 = slider2_raw;
	
	input.button_left = PIND & (1 << PD2);
	input.button_right= PIND & (1 << PD3);
	
	input_buffer[input_head] = input;
	input_head = (input_head + 1) % 10;
	
	// smooth_input is average of all 10 last inputs
	input_t smooth_input = input;
	float smooth_joystick_x = 0;
	float smooth_joystick_y = 0;
	for(int i = input_head; i != (input_head + 1 + 10) % 10; i = (i - 1) % 10)
	{
		age = (input_head - i + 10) % 10 + 1;
		smooth_joystick_x += pow(1/2, age) * (float)input_buffer[i % 10].joystick_x / 10.0;
		smooth_joystick_y += (float)input_buffer[i % 10].joystick_y / 10.0;
	}
	smooth_input.joystick_x = (int)smooth_joystick_x;
	smooth_input.joystick_y = (int)smooth_joystick_y;
	

	return smooth_input;
}
