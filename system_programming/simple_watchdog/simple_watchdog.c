/******************************************************************************
 *	Title:		Simple Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	21.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */
#include <sys/types.h>	/* fork */
#include <unistd.h>		/* fork */
#include <sys/wait.h>	/* wait */

#include "simple_watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/

void SimpleFork(void)
{
	int status = 0;
	char* args[] = {"./dummy", NULL};
	pid_t id = fork();
	/*perform a fork*/
	/*if fork is child*/
	if (0 == id)
	{
		/*print child response*/
		printf("Hello from child\n");
		exit(execv(args[0], args));
	}
	else if (0 < id)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			/*elese print parent response*/
			printf("Hello from parent\n");
		}
		else
		{
			printf("I lost my child\n");
		}
	}
	else
	{
		printf("Process aborted\n");
	}
}

int main()
{
	while(1)
	{
		SimpleFork();
	}
	return 0;
}
