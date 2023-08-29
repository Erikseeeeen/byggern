/*
 * microchip_byggern.c
 *
 * Created: 29.08.2023 08:46:19
 * Author : eiviser
 */ 

#include <avr/io.h>
#include <util/delay_basic.h>


int main(void)
{
    DDRA |= 1 << 0;
    /* Replace with your application code */
    while (1) 
    {
        PORTA |= 1 << 0;
        _delay_loop_2(65536);
    }
}

