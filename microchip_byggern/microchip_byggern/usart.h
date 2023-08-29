#include "stdio.h"
#define FREQUENCY_OF_OSCILLATOR 1843200
#define BAUD_RATE 9600
#define USART_BAUD_RATE_REGISTER FREQUENCY_OF_OSCILLATOR / 16 / BAUD_RATE - 1


void usart_init(unsigned int baud_rate);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

