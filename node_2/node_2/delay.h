/*
 * delay.h
 *
 * Created: 10.10.2023 10:40:05
 *  Author: jorgehav
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include "sam.h"

#define F_CPU 84000000UL // System clock frequency in Hz

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif /* DELAY_H_ */