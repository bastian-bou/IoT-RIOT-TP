#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "board.h"




int main(void)
{
	printf("Eh coucou ! Ah que ça marche !\n");

	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
	

	return 0;	
}

