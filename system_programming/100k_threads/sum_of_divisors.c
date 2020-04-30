/******************************************************************************
 *	Title:		Sum of Divisors
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	30.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */
#include <errno.h>		/* perror */
#include <pthread.h>	/* pthread functions */
#include <time.h>		/* time */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != (ptr)))
#define MAX_THREADS				(NUMBER)
#define THREAD_LIMIT			(32000)
#define NUMBER					(1234567890)
#define MAX_RUNS				(MAX_THREADS / THREAD_LIMIT)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/


/******FUNCTIONS******/
int main()
{
	size_t sum_of_divisors = 0;
	size_t i = 0;
	
	for (i = 1; i < NUMBER; ++i)
	{
		if (0 == (NUMBER % i))
		{
			sum_of_divisors += i;
		}
	}

	printf("Sum of %d is %ld\n", NUMBER, sum_of_divisors);
	return 0;
}
