#include <stdio.h>
#include "thread.h"
#include "board.h"
#include "xtimer.h"
#include "periph/uart.h"

#define UART0	UART_DEV(1)

//static char stack[THREAD_STACKSIZE_MAIN];

static char stackISR[THREAD_STACKSIZE_MAIN];

kernel_pid_t	pid;




uint8_t bufferMessage[512];
uint8_t iBuf = 0;

/*void *thread_sendUART_handler(void *arg){
	(void) arg;
	
	uint8_t monMessage[] = "coucou toi\r\n";
	
	while(1) {	
		uart_write(UART0, monMessage, sizeof(monMessage));
		xtimer_usleep(500 * US_PER_MS);
	}
	return NULL;
}*/

void *thread_ISR_handler(void *arg){
	(void) arg;
	
	while(1) {
		printf("Receive : %s\n", bufferMessage);
		thread_sleep();
	}
	return NULL;
}


void callbackUART (void *arg, uint8_t data)
{
	(void) arg;
	
	if (data == '\r') {
		bufferMessage[iBuf++] = '\0';
		thread_wakeup(pid);
		iBuf = 0;
	
	} else {
		bufferMessage[iBuf++] = data;
	}
	
}


// #### MAIN #### //
int main(void)
{	
	uart_init(UART0, 9600, callbackUART, NULL);

	//thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_sendUART_handler, NULL, "send UART");
	pid = thread_create(stackISR, sizeof(stackISR), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_SLEEPING, thread_ISR_handler, NULL, "ISR buffer UART");
	printf("Eh coucou ! Ah que ça marche !\n");	

	return 0;	
}

