#include "spi.h"

void SPI_init(){
	
	/* Set MOSI, SCK output, all others input */
	DDRB = (1 << PB5) | (1 << PB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

}

void SPI_write(char cData){
	
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)))
		;
	
}

char SPI_read(){
	
	/* Received byte is found on the same register */
	return SPDR;

}