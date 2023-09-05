/*
 * xmem.h
 *
 * Created: 05.09.2023 09:59:05
 *  Author: jorgehav
 */ 


#ifndef XMEM_H_

#define XMEM_H_
#define BASE_ADDRESS 0x1800;

#include <stdint.h> 
#include <avr/io.h>

void xmem_init(void);
void xmem_write(uint8_t data, uint16_t addr); 
uint8_t xmem_read(uint16_t addr);

#endif /* XMEM_H_ */