#include "spi.h"
#include <avr/io.h>

void SPI_init(){
	
	/* Set MOSI, SCK output, all others input */
	DDRB |= (1 << PB5) | (1 << PB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	//SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE) ;
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0) ;
	SPCR &= ~(1 << SPR1) ;
	SPSR &= ~(1 << SPI2X) ;
	

}

void SPI_write(char cData){
	
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)))
	;
	
	
	
}

char SPI_read(){
	
	/* Start transmission */
	SPDR = 0b00000000;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)))
	;
	/* Received byte is found on the same register */
	return SPDR;

}