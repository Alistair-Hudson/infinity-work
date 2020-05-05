#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t cond_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int ready = 0;
int count = 0;

void* PrintID(void* arg)
{
/*	pthread_mutex_lock(&cond_lock);
*/	while(!ready)
	{
/*		pthread_cond_wait(&condition, &cond_lock);
*/	}
	printf("Thread %d\n", *(int*)arg);
/*	pthread_mutex_unlock(&cond_lock);
*/	return NULL;
}

void Go()
{
/*	pthread_mutex_lock(&cond_lock);
*/	ready = 1;
/*	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&cond_lock);	
*/}

int main()
{
	pthread_t threads[10];
	int i = 0;

	for(i = 0; i < 10; ++i)
	{
		threads[i] = i;
		pthread_create(&threads[i], NULL, PrintID, &threads[i]);
	}
	printf("Ready to Race\n");
	sleep(5);
	Go();
	
	for (i = 0; i < 10; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	return 0;
}
