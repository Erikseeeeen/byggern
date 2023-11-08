#include "motor.h"


void motor_init()
{
	// Enable the peripheral clock for the PIO (Peripheral Input/Output) controller
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= (1 << ID_PIOC);
	PMC->PMC_PCER0 |= (1 << ID_PIOD);
	
	// Set pins C1-C9 as input only
	// Should maybe set to be IO driven, not peripheral driven (page 623)
	PIOC->PIO_PER |= PIO_PC8 | PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7;
	PIOC->PIO_ODR |= PIO_PC8 | PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7;
	PIOD->PIO_PER |= PIO_PD10 | PIO_PD2 | PIO_PD1 | PIO_PD0 | PIO_PD9;
	PIOD->PIO_OER |= PIO_PD10 | PIO_PD2 | PIO_PD1 | PIO_PD0 | PIO_PD9;
	
	// Enable motor
	PIOD->PIO_SODR = PIO_PD9;
	
	// Motor Direction Pin: PD10
	
	// Reset
	/*PIOC->PIO_SODR = PIO_PC6;
	PIOC->PIO_CODR = PIO_PC6;*/
	
	// Speed is set using DAC1 pin on shield.
	
	//INIT solenoid
	PIOC->PIO_PER |= PIO_PC13;
	PIOC->PIO_OER |= PIO_PC13;
	PIOC->PIO_SODR |= PIO_PC13;
	 
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
	//Reset encoder
	PIOD->PIO_CODR |= PIO_PD1;
	PIOD->PIO_SODR |= PIO_PD1;
	// Set !OE high
	PIOD->PIO_SODR |= PIO_PD0;
	
	//int pos = ((mj2_low | (mj2_high << 8)) + 131070) % 130616;
	int pos = (mj2_low | (mj2_high << 8));
	printf(" %d ", pos);
	return pos;
	
}


void dac_write_speed()
{
	float normalized_signal = (float)(joystick_y) / 128.0 - 1.0;
	
	if (normalized_signal < -1)
	normalized_signal = -1;
	if (normalized_signal > 1)
	normalized_signal = 1;
	
	if(normalized_signal < 0)
	{
		dac_write_uint_voltage((uint16_t)(-normalized_signal * 65535));
		// Set motor direction left
		PIOD->PIO_CODR = PIO_PD10;
	}
	else
	{
		dac_write_uint_voltage((uint16_t)(normalized_signal * 65535));
		// Set motor direction right
		PIOD->PIO_SODR = PIO_PD10;
	}
}

void shoot()
{
	PIOC->PIO_CODR |= PIO_PC13;
	delay_ms(80);
	PIOC->PIO_SODR |= PIO_PC13;
}

