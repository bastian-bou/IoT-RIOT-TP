#include <stdio.h>
#include "shell.h"
#include "thread.h"
#include "board.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "MAX31855.h"

static char stack[THREAD_STACKSIZE_MAIN];


void *thread_temp_handler(void *arg){
	(void) arg;
	unsigned char buffer[4];
	while(1) {
		if(max31855_readtemp(buffer) != 0) {
			printf("ERROR : issue with readTemp of MAX31855\n");
			break;
		}
		printf("Temp : %f\n", max31855_decodetemp(buffer));
		xtimer_usleep(500 * US_PER_MS);
	}
	return NULL;
}


// #### MAIN #### //
int main(void)
{
	
	
	
	if(max31855_init() != 0) {
		printf("ERROR : issue with initialisation of MAX31855\n");
		return -1;
	}
	
	
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_temp_handler, NULL, "Temperature");
	
	printf("Eh coucou ! Ah que ça marche !\n");
	
	
	
	
	//char line_buf[SHELL_DEFAULT_BUFSIZE];	
	//shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	

	

	return 0;	
}

