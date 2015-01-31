#include "dac.h"
#include "spi.h"
void dac_init(void){
		spi_init();
}
void dac_output(unsigned short dac_step){
	//send data through spi to dac
	spi_write16(((0x7<<12)|(0xFFF&dac_step)));
}
