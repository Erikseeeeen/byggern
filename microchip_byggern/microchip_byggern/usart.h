
#ifndef USART_H_

#define USART_H_

#include "stdio.h"
#include <avr/io.h>
#include <stdint.h> 

#define FREQUENCY_OF_OSCILLATOR 4915200
#define BAUD_RATE 9600
#define USART_BAUD_RATE_REGISTER FREQUENCY_OF_OSCILLATOR / 16 / BAUD_RATE - 1

void usart_init(unsigned int baud_rate);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

#endif /* USART_H_ */


