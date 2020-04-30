/******************************************************************************
 *	Title:		100k Threads
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	28.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */
#include <errno.h>		/* perror */
#include <pthread.h>	/* pthread functions */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != (ptr)))
#define MAX_THREADS				(100000)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/

int main()
{
	/*Initialise threads*/
	pthreads_t threads[MAX_THREADS];
	size_t i = 0;

	/*for from 0 to the Max number of threads*/
	for (i = 0; i < MAX_THREADS; ++i)
	{
		/*set each thread to the value of its index*/
		pthread_create(&threads[i], NULL, , (void*)NULL );
	}
	/*Check time performance*/

	/*sleep for 10 seconds*/
	sleep(10);

	/*check each index has the correct value*/

	return 0;
}
