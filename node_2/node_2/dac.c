
#include "dac.h"

void dac_init()
{
	// Enable peripheral clock
	PMC->PMC_PCR |= (ID_DACC << PMC_PCR_PID_Pos) | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_EN;
	PMC->PMC_PCER1 |= (1 << (ID_DACC-32));
	
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF | DACC_MR_STARTUP_8;
	
	// Enable channel
	DACC->DACC_CHER = DACC_CHER_CH1;
	
	dac_write_uint_voltage(0xFFFF);
	dac_write_uint_voltage(0);
	
}

void dac_write_uint_voltage(uint16_t signal)
{
	DACC->DACC_CDR = signal;
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
