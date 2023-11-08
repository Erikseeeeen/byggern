#ifndef PWM_H_
#define PWM_H_

#include "sam.h"
#define F_CPU 84000000UL // System clock frequency in Hz

uint8_t joystick_x;
uint32_t servo_period;

void pwm_init();
void set_servo_duty();
float pos_to_duty(uint8_t);


#endif /* PWM_H_ */