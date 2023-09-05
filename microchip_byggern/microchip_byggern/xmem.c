/*
 * xmem.c
 *
 * Created: 05.09.2023 09:58:32
 *  Author: jorgehav
 */ 
#include "xmem.h"

// From lab lecture
void xmem_init(void) {
	// Enable XMEM
	MCUCR |= (1 << SRE);
	// Mask out some port C address pins for JTAG (datasheet page 32)
	SFIOR |= 1 << XMM0;
	SFIOR &= ~(1 << XMM0 | 1 << XMM1);
}

// From lab lecture
void xmem_write(uint8_t data, uint16_t addr){
	volatile char* ext_mem = (char*) BASE_ADDRESS;
	ext_mem[addr] = data;
}

// From lab lecture
uint8_t xmem_read(uint16_t addr){
	volatile char* ext_mem = (char*) BASE_ADDRESS;
	uint8_t ret_val = ext_mem[addr];
	return ret_val;
}