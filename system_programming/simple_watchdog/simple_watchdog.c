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

#include "simple_watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/
void SimpleFork(void)
{
	char* args[] = {"./dummy", NULL};
	/*perform a fork*/
	/*if fork is child*/
	if (0 == fork())
	{
		/*print child response*/
		printf("Hello from child\n");
		execv(args[0], args);
	}
	else
	{
		/*elese print parent response*/
		printf("Hello from parent\n");
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
