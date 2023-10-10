/*
 * CFile2.c
 *
 * Created: 03.10.2023 13:50:37
 *  Author: jorgehav
 */ 

#include "interrupts.h"

interrupt_init(){
	
	GICR &= ~(1 << INT2); // Disable External Interrupt 2
	SREG |= (1 << 7); // Enable global interrupts
	EMCUCR &= ~(1 << ISC2); // Interrupt on Falling edge
	GICR |= (1 << INT2); // Enable External Interrupt 2

}

ISR(INT2_vect){printf("%d", can_data_receive().data[0]);}