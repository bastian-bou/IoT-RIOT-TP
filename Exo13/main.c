#include <stdio.h>
#include "thread.h"
#include "board.h"
#include "xtimer.h"
#include "grove_ledbar.h"
#include "grove_ledbar_params.h"

grove_ledbar_t hLedBar;
uint8_t lvl = 0;

static char stack[THREAD_STACKSIZE_MAIN];
//static char stackTHL[THREAD_STACKSIZE_MAIN];

/*
//Thread...
void *thread_monThread_handler(void *arg){
	(void) arg;

	
	return NULL;
}
*/

//XTIMER
void *thread_XTIMER_handler(void *arg){
	(void) arg;
	printf("Hello from level thread (pid=%d\n", thread_getpid());
	while(1) {	
		grove_ledbar_set(&hLedBar, lvl);
		printf("Level = %d\n", lvl);
		if (lvl < GROVE_LEDBAR_MAX) 
			lvl++;
		else
			lvl = 0;
		xtimer_usleep(50 * US_PER_MS);
	}
	return NULL;
}



// #### MAIN #### //
int main(void)
{	

	if (grove_ledbar_init(&hLedBar, &grove_ledbar_params[0]) != 0){
		printf("[FAILED]");
		return 1;
	}
	
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_XTIMER_handler, NULL, "XTIMER");
	//thread_create(stack, sizeof(stackTHL), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_handler_Level, NULL, "thread handler Level");
	printf("Eh coucou ! Ah que ça marche !\n");	

	return 0;	
}

