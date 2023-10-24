/*
 * adc.c
 *
 * Created: 24.10.2023 13:00:45
 *  Author: jorgehav
 */ 

#include "adc.h"

void adc_init(){
	
	// Enable peripheral clock
	PMC->PMC_PCR |= (ID_ADC << PMC_PCR_PID_Pos) | PMC_PCR_DIV_PERIPH_DIV_MCK | PMC_PCR_EN;
	PMC->PMC_PCER1 |= (1 << (ID_ADC-32));
	
	// Enable Channel Register
	ADC->ADC_WPMR &= ~(1);
	ADC->ADC_CHER |= (ADC_CHDR_CH10);
	
	// Single-Ended, Freerun Mode
	ADC->ADC_MR |= (1 << 7);
	ADC->ADC_COR &= ~(1 << 26);
	
	// Begin Analog-to-Digital Conversion
	ADC->ADC_CR |= 1;
	
}

int adc_receive(){
	
}
