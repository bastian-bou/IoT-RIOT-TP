

#ifndef MAX31855_H
#define MAX31855_H

#include <stdio.h>
#include "periph/spi.h"
#include "periph/gpio.h"
#include "board.h"

#define SPI0				SPI_DEV(0)
#define CS_MAX				GPIO_PIN(PORT_B, 6)


int 	max31855_init		(void);
int 	max31855_readtemp	(unsigned char* pBuffRes);
float 	max31855_decodetemp	(unsigned char* pBuffRes);


#endif
