#include <stdio.h>
#include "shell.h"

static int target_handler(int argc, char **argv){
	(void)argv;
	
	if(argc != 1) {
		printf("Usage : target\n");
		return 1;
	}
	printf("Board : %s, CPU : %s\n", RIOT_BOARD, RIOT_CPU);
	return 1;
}

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

static const shell_command_t shell_commands[] = {
    { "target", "display the type of host board", target_handler},
    { "echo", "display your arguments", echo_handler},
    { NULL, NULL, NULL }
};


int main(void)
{
	printf("Eh coucou ! Ah que ça marche !\n");

	char line_buf[SHELL_DEFAULT_BUFSIZE];
	//shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
	shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	

	return 0;	
}

