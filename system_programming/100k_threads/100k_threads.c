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
#define MAX_THREADS				(NUMBER)
#define THREAD_LIMIT			(32000)
#define NUMBER					(1234567890)
#define MAX_RUNS				(MAX_THREADS / THREAD_LIMIT)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static size_t array[THREAD_LIMIT] = {0};
static double sum_of_divisors = 0;

/******FUNCTIONS******/
void* SetIndex(void* arg)
{
	(void)arg;
	return NULL;	
}

void* SumOfDivisors(void* arg)
{
	size_t i = 0;
	size_t num = (*(size_t*)arg +1) * 100;
	
	for (i = (*(size_t*)arg * 100); i < num; ++i)
	{
		if (0 == (NUMBER % i))
		{
			sum_of_divisors += i;
		}
	}
	return NULL;
}

int main()
{
	/*Initialise threads*/
	pthread_t threads[THREAD_LIMIT];
	size_t i = 0;
	size_t j = 0;
	time_t start = time(NULL);
	for (j = 0; j <= MAX_RUNS; ++j)
	{
		size_t offset = THREAD_LIMIT * j;
		/*for from 0 to the Max number of threads*/
		for (i = 0; i < THREAD_LIMIT; ++i)
		{
			if (MAX_THREADS <= (i+offset))
			{
				break;
			}
			array[i] = i + offset;
			/*set each thread to the value of its index*/
			while(pthread_create(&threads[i], NULL, SumOfDivisors, &array[i]))
			{
			}
	/*This is for Ex3
			if(pthread_detach(threads[i]))
			{
				perror("Thread detach failed");
				return 1;
			}
	*/	}

		/*Join threads*/
		for (i = 0; i < THREAD_LIMIT; ++i)
		{
			if (MAX_THREADS <= (i+offset))
			{
				break;
			}
			if (pthread_join(threads[i], NULL))
			{
				perror("Thread join failed");
				printf("run = %ld", j);
				return 1;
			}
		}
	}
	/*Check time performance*/
	printf("Time taken = %ld\n", time(NULL) - start);
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
	printf("for the number %f the sum of all divisors = %f\n", NUMBER, sum_of_divisors);
	return 0;
}
