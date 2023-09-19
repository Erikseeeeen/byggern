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
	
	_delay_ms(100);
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
	_delay_ms(20);
	
	pos_t joystick_pos;
	float y_raw = *adc_out;
	float x_raw = *adc_out;
	float slider1_raw = *adc_out;
	float slider2_raw = *adc_out;
	
	/*printf("%d\n",y_raw);
	printf("%d\n",x_raw);
	printf("%d\n",slider1_raw);
	printf("%d\n",slider2_raw);*/
	
	const double PI =  3.1415926;
	
	/*float y_asin = asin((y_raw / (float)(127.5) - 1) * 0.8);
	float x_asin = asin((x_raw / (float)(127.5) - 1) * 0.8);
	
	
	
	float y_asin_scaled =  (y_asin + PI / 2) / (2 * PI);
	float x_asin_scaled =  (x_asin + PI / 2) / (2 * PI);*/
	
	
	
	uint8_t y_positive = MAX(y_raw, 175) - 175;
	uint8_t x_positive = MAX(x_raw, 198) - 198;
	
	uint8_t y_positive_scaled = (uint8_t)((float)y_positive * ((float)127/(float)80));
	uint8_t x_positive_scaled = (uint8_t)((float)x_positive * ((float)127/(float)57));
	
	uint8_t y_negative = 175 - MIN(y_raw, 175);
	uint8_t x_negative = 198 - MIN(x_raw, 198);
	
	uint8_t y_negative_scaled = (uint8_t)((float)y_negative * ((float)127/(float)175));
	uint8_t x_negative_scaled = (uint8_t)((float)x_negative * ((float)127/(float)198));
	
	joystick_pos.y = (uint8_t)((128 - y_negative_scaled) + y_positive_scaled);
	joystick_pos.x = (uint8_t)((128 - x_negative_scaled) + x_positive_scaled);
	
	joystick_pos.direction = CENTER;
	if(joystick_pos.y > 198)
		joystick_pos.direction = UP;
	if(joystick_pos.x > 198)
		joystick_pos.direction = RIGHT;
	if(joystick_pos.y < 68)
		joystick_pos.direction = DOWN;
	if(joystick_pos.x < 68)
		joystick_pos.direction = LEFT;
	
	
	_delay_ms(20);
	
	return joystick_pos;
}

uint8_t joystick_calibrate()
{
	pos_t joystick_pos = joystick_read();
	pos_start.x = joystick_pos.x;
	pos_start.y = joystick_pos.y;
}