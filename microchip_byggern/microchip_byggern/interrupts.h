/*
 * interrupts.h
 *
 * Created: 03.10.2023 13:51:07
 *  Author: jorgehav
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/interrupt.h>
#include "can.h"
#include "menu.h"

void interrupt_init();


#endif /* INTERRUPTS_H_ */