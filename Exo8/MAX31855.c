#include "MAX31855.h"


int max31855_init (void)
{
	spi_init(SPI0);
	return spi_init_cs(SPI0, CS_MAX);
}


int max31855_readtemp (unsigned char* pBuffRes)
{
	if(spi_acquire (SPI0, CS_MAX, SPI_MODE_0, SPI_CLK_5MHZ) != SPI_OK) return -1;
	
	spi_transfer_bytes (SPI0, CS_MAX, false, NULL, pBuffRes, 4);
	
	spi_release(SPI0);
	
	return SPI_OK;
}


float max31855_decodetemp (unsigned char* pBuffRes)
{
	int32_t Temp = pBuffRes[0];
	
	Temp <<= 8;
	Temp += pBuffRes[1];
	Temp >>= 2;
	
	return Temp * (0.25);
}
