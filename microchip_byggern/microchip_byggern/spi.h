#ifndef SPI_H_
#define SPI_H_


void SPI_init();

// The MCU starts the clock signal SCK when the program writes to the SPI data register
// (SPDR; given that SPI module is enabled). For each clock period one bit of the SPDR will
// be shifted from the master to the slave (MOSI), and one bit from the slave to the master (MISO).

// When transmission completes after eight clock periods, SS will be pulled high to indicate
// that the operation has completed and release the slave. The datasheets of the MCU and ICs
// that uses SPI provide a good description of the bus.


void SPI_write(char cData);
char SPI_read(); //Remember, to read something from a slave the master must transmit a dummy byte



#endif /* SPI_H_ */