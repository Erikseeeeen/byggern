#include "motor.h"


void motor_init()
{
	// Enable the peripheral clock for the PIO (Peripheral Input/Output) controller
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	PMC->PMC_PCER0 |= (1 << ID_PIOD);
	
	// Set pins C1-C9 as input only
	// Should maybe set to be IO driven, not peripheral driven (page 623)
	PIOC->PIO_PER |= PIO_PC8 | PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7;
	PIOC->PIO_ODR = PIO_PC8 | PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7;
	
	
	// Enable motor
	PIOD->PIO_SODR = PIO_PD9;
	
	// Motor Direction Pin: PD10
	
	// Reset
	/*PIOC->PIO_SODR = PIO_PC6;
	PIOC->PIO_CODR = PIO_PC6;*/
	
	// Speed is set using DAC1 pin on shield. 
	 
}

int read_encoder()
{
	// Set !OE low
	PIOD->PIO_CODR |= PIO_PD0;
	// Set SEL low
	PIOD->PIO_CODR |= PIO_PD2;
	// Wait 20us
	delay_us(20);
	// Read MJ2 (high byte)
	int mj2_high = (PIOC->PIO_PDSR) & 0x1FE;
	// Set SEL high
	PIOD->PIO_SODR |= PIO_PD2;
	// Wait 20us
	delay_us(20);
	// Read MJ2 (low byte)
	int mj2_low = (PIOC->PIO_PDSR) & 0x1FE;
	// Set !OE high
	PIOD->PIO_SODR |= PIO_PD0;
	
	printf(" %d ", mj2_low | (mj2_high << 8));
	return mj2_low | (mj2_high << 8);
	
}
