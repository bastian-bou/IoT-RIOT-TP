#include <stdio.h>
#include "shell.h"
#include "thread.h"
#include "board.h"
#include "periph/gpio.h"
#include "msg.h"


static char stack[THREAD_STACKSIZE_MAIN];
/*
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
};*/




//THREAD HANDLER
void *thread_handler(void *arg) {
	
	(void)arg; 
	
	while(1) {
		printf("Coucou c'est moi le thread %d\n", thread_getpid());
		gpio_write(LED0_PIN, gpio_read(BTN0_PIN));
	}
	
	return NULL;
}

void *msg_thread_handler(void *arg) {
	
	(void)arg;
	
	while(1) {
		msg_t msg;
		msg_receive(&msg);
		printf("Message received : %s\n", (char *)msg.content.ptr);
		LED0_TOGGLE;
	}
	
	return NULL;
}

void cb(void *arg)
{
	(void)arg;
	
	
	msg_t msg;
	msg.type = 0;
	msg.content.value = 42;
	msg.sender_pid = 3;
	msg.content.ptr = "coucou";
	
	msg_send(&msg, msg.sender_pid);
}


// #### MAIN #### //
int main(void)
{
	
	gpio_init(LED0_PIN, GPIO_OUT);
	gpio_init_int(BTN0_PIN, GPIO_IN, GPIO_FALLING, cb, (void*) 0);
	
//	gpio_irq_enable(BTN0_PIN);
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, 
				msg_thread_handler, NULL, "thread to handle message");
	
	//thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_handler, NULL, "monThread");
	
	printf("Eh coucou ! Ah que ça marche !\n");
	
	//char line_buf[SHELL_DEFAULT_BUFSIZE];	
	//shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	

	

	return 0;	
}

