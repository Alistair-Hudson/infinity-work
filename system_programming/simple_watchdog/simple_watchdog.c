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
	char* args[] = {"./dummy", 0, NULL};
	pid_t id = fork();
	/*perform a fork*/
	/*if fork is child*/
	if (0 == id)
	{
		
		/*print child response*/
		printf("Hello from child\n");
		printf("What should I play with?\n(enter a number to trigger test)\n");
		scanf("%s", args[1]);
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
			printf("My child was terminated\n");
		}
	}
	else
	{
		printf("Process aborted\n");
	}
}

void SimpleSystem(void)
{
	char target[100];
	int status = 0;

	printf("Input file path and which test number\n");
	scanf("%s", target);
	
	status = system(target);	
	if (-1 == status)
	{
		printf("child failed to execute\n");
	}
	else if (0 == status)
	{
		printf("Child successfully ran\n");
	}
	else
	{
		printf("child terminated\n");
	}
}

int main()
{
	while(1)
	{
		char function[100];
		printf("fork or system?\n");
		scanf("%s", function);
		if (0 == strcmp(function, "fork"))
		{
			SimpleFork();
		}
		else if (0 == strcmp(function, "system"))
		{
			SimpleSystem();
		}
		else if (0 == strcmp(function, "exit"))
		{
			break;
		}
		else
		{
			printf("incorrect input\n\n");
		}
	}
	return 0;
}
