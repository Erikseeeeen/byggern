#ifndef MOTOR_H_
#define MOTOR_H_

# include "sam.h"

uint8_t joystick_y;


void motor_init();
int read_encoder();
void dac_write_speed();
void shoot();




#endif /* MOTOR_H_ */