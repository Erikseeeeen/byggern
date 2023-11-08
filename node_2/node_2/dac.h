#ifndef DAC_H_
#define DAC_H_

#include "sam.h"
#include "delay.h"

uint8_t joystick_y;

void dac_init();

void dac_write_voltage(uint16_t signal);

void dac_write_speed();

void shoot();


#endif /* DAC_H_ */