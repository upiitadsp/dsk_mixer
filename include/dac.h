#ifndef _DAC_H_
#define _DAC_H_
//MSP DAC CONNETIONS
/*
	SPI conection to MCP4921 12bit dac
	PIN 	NAME			CONNECT TO  
	1			VDD				3.3v
	2			/CS				spi cs
	3			SCK				spi sck
	4			SDI				spi sdo
	5			/LDAC			10k resistor to gnd
	6			VREFA			vref (2.5v)
	7			AVSS			gnd
	8			VOUTA			output 
	
	spi singnalign
	idle state: /CS=1 SCK=0 SDI=x
							/CS=0 SCK=0 SDI=x/data
							/CS=0 SCK=0 SDI=data_i //repeat this i times  
							/CS=0 SCK=1 SDI=data_i //
							/CS=0 SCK=0 SDI=x
							 CS=1 SCK=0 SDI=x
*/
// PA2(SSI0CLK)	PA3(SSI0Fss) PA4(SSI0Rx) PA5(SSI0Tx)
void dac_init(void);
void dac_output(unsigned short dac_step);
#endif
