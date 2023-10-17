/*
 * node_2.c
 *
 * Created: 10.10.2023 10:26:06
 * Author : jorgehav
 */ 


#include "sam.h"
#include "delay.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "printf-stdarg.h"
#include "uart.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	can_init_def_tx_rx_mb(0x00290165);
	configure_uart();
	
	
	// Enable the peripheral clock for the PIO (Peripheral Input/Output) controller
	PMC->PMC_PCER0 |= (1 << ID_PIOA);
	
	
	PIOA->PIO_PER |= PIO_PA20; // Enable PIO control
	PIOA->PIO_OER |= PIO_PA20; // Set pin as output
	
	PIOA->PIO_SODR |= PIO_PA20; // Set output high
	
	PIOA->PIO_CODR |= PIO_PA20;
	
	printf("Hello world");
	

    /* Replace with your application code */
    while (1)
    {
	    PIOA->PIO_SODR |= PIO_PA20;
	    delay_ms(100000);
	    PIOA->PIO_CODR |= PIO_PA20;
	    delay_ms(100000);
		
		CAN_MESSAGE msg;
		msg.data_length = 8;
		msg.id = 3;
		msg.data[0] = 'I';
	    can_send(&msg, 0);
		
		printf("sent message %d", msg.data[0]);
    }
}
