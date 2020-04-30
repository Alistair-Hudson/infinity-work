/******************************************************************************
 *	Title:		100k Threads
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
#define MAX_THREADS				(100000)
#define MAX_ERROR_LOOP			(100)
/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static size_t array[MAX_THREADS] = {0};
static size_t thread = 0;

/******FUNCTIONS******/
void* SetIndex(void* arg)
{
	(void)arg;
	return NULL;	
}

int main()
{
	/*Initialise threads*/
	pthread_t threads[MAX_THREADS];
	size_t i = 0;
	time_t start = time(NULL);

	/*for from 0 to the Max number of threads*/
	for (i = 0; i < MAX_THREADS; ++i)
	{
		size_t error_count = 0;
		array[i] = i;
		/*set each thread to the value of its index*/
		while(pthread_create(&threads[i], NULL, SetIndex, &array[i]))
		{
			/*++error_count;
			if (MAX_ERROR_LOOP == error_count)
			{
				perror("Thread create failed");
				printf("Thread break at %ld\n", i);
				return 1;
			}*/
		}
		pthread_detach(threads[i]);
	}
	/*Check time performance*/
	printf("Time take = %ld\n", start - time(NULL));
	/*sleep for 10 seconds*/
	sleep(10);

	/*check each index has the correct value*/
	for (i = 0; i < MAX_THREADS; ++i)
	{
		if (i != array[i])
		{
			printf("failed at index %ld = %ld\n", i, array[i]);
			return 1;
		}
	}
	printf("Success\n");
	return 0;
}
