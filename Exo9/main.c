#include <stdio.h>
#include "thread.h"
#include "board.h"
#include "xtimer.h"
#include "lib_lcd_backlight.h"
#include "periph/hwrng.h"


static char stack[THREAD_STACKSIZE_MAIN];


void *thread_randColor_handler(void *arg){
	(void) arg;
	unsigned char red, green, blue;

	while(1) {	
		hwrng_read(&red, 1);
		hwrng_read(&green, 1);
		hwrng_read(&blue, 1);
		lcd_setRGB(I2C0, red, green, blue);
		xtimer_usleep(500 * US_PER_MS);
	}
	
	return NULL;
}


// #### MAIN #### //
int main(void)
{	
	hwrng_init();
	int err;
	if((err = lcd_init(I2C0)) != 0) {
		printf("ERROR : issue with initialisation of LCD : %d\n", err);
		return -1;
	}
	
	lcd_puts(I2C0, (unsigned char *)"Coucou toi");

	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_randColor_handler, NULL, "Color Random");
	
	printf("Eh coucou ! Ah que ça marche !\n");	

	return 0;	
}

