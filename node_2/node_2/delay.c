/*
 * delay.c
 *
 * Created: 10.10.2023 10:39:49
 *  Author: jorgehav
 */ 

#include "delay.h"

#include <stdio.h>
#include <stdio.h>
#include <inttypes.h>

// Max ca. 200ms!!
void delay_ms(uint32_t ms){
	uint32_t ticks = (F_CPU / 1000) * ms;
	if(ticks > 0xFFFFFF)
	ticks = 0xFFFFFF;
	SysTick->LOAD = ticks - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
	
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {
		// Wait for the SysTick timer to count down
	}
	
	SysTick->CTRL = 0; // Disable the SysTick timer
}


// Max ca. 200 000us!!
void delay_us(uint32_t us){
	uint32_t ticks = (F_CPU / 1000000) * us;
	if(ticks > 0xFFFFFF)
		ticks = 0xFFFFFF;
	SysTick->LOAD = ticks - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
	
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {
		// Wait for the SysTick timer to count down
	}
	
	SysTick->CTRL = 0; // Disable the SysTick timer
}
