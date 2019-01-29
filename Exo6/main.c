#include <stdio.h>
#include "shell.h"
#include "thread.h"
#include "xtimer.h"
#include "board.h"

static char stack[THREAD_STACKSIZE_MAIN];
static char stackLED[THREAD_STACKSIZE_MAIN];


//TARGET HANDLER
static int target_handler(int argc, char **argv){
	(void)argv;
	
	if(argc != 1) {
		printf("Usage : target\n");
		return 1;
	}
	printf("Board : %s, CPU : %s\n", RIOT_BOARD, RIOT_CPU);
	return 1;
}


//ECHO HANDLER
static int echo_handler(int argc, char **argv){
	int cmpt = 1;
	if (argc == 1) {
		printf("Usage : echo [arg] [arg] ...\n");
		return 1;
	} else {
		while(cmpt < argc) {
			printf("%s ",argv[cmpt++]);
		}
		printf("\n");
	}
	return 1;
}

//SHELL
static const shell_command_t shell_commands[] = {
    { "target", "display the type of host board", target_handler},
    { "echo", "display your arguments", echo_handler},
    { NULL, NULL, NULL }
};




//THREAD HANDLER
void *thread_handler(void *arg) {
	
	(void)arg; 
	
	while(1) {
		printf("Coucou c'est moi le thread %d\n", thread_getpid());
		xtimer_usleep(500 * US_PER_MS);
	}
	
	return NULL;
}


void *threadLED_handler(void *arg) {
	
	(void)arg; 
	
	while(1) {
		xtimer_ticks32_t last_wakeup = xtimer_now();
		xtimer_periodic_wakeup(&last_wakeup, 100 * US_PER_MS);
		LED0_TOGGLE;
	}
	
	return NULL;
}



// #### MAIN #### //
int main(void)
{
	
	gpio_init(LED0_PIN, GPIO_OUT);
	//kernel_pid_t pid;
	//pid = thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_handler, NULL, "monThread");
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_handler, NULL, "monThread");
	thread_create(stackLED, sizeof(stackLED), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, threadLED_handler, NULL, "monThread_LED");
	
	printf("Eh coucou ! Ah que ça marche !\n");
	
	char line_buf[SHELL_DEFAULT_BUFSIZE];	
	shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	

	

	return 0;	
}

