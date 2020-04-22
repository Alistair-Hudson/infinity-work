/******************************************************************************
 *	Title:		Dummy for Simple Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	21.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */

#include "simple_watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define UPPER_LIMIT				(3)
#define LOWER_LIMIT				(0)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/
int Normal(void)
{
	printf("I executed this....\n");
	return 0;
}

int DivideByZero()
{
	int i = 10;
	printf("Execute failure in\n");
	for (i = 10; i >= 0; --i)
	{
		printf("%d\n", 10/i);
	}
	return 0;
}

int AccessMemoryViolation(void)
{
	char* str = "asdf";
	printf("Execute memory violation\n");
	str[0] = 45;
	return 0;
}

int main(int argc, char* argv[])
{
	char test = *argv[1];
	int status = 0;
	
/*	printf("What should I play with?\n(enter a number to trigger test)\n");
	scanf("%s", test);
*/
	switch(test)
	{
		case '0':
			status = DivideByZero();
			break;
		case '1':
			status = AccessMemoryViolation();
			break;
		default:
			status = Normal();
	}

	return status;
}
