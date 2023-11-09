#ifndef MOTOR_H_
#define MOTOR_H_

# include "sam.h"
#include <math.h>

uint8_t joystick_y;


void motor_init();
int read_encoder();
void dac_write_speed();
void shoot();

void enable_motor();
void disable_motor();

int motor_enabled;
int motor_write_speed;



#endif /* MOTOR_H_ */