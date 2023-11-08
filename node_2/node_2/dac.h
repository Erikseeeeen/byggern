#ifndef DAC_H_
#define DAC_H_

#include "sam.h"
#include "delay.h"
void dac_init();

void dac_write_voltage(uint16_t signal);


#endif /* DAC_H_ */