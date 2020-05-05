#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int global = 0;

void* Thread(void* arg)
{
	int i = 0;
	for (i = 0; i < 1000; ++i)
	{
/*		__sync_fetch_and_add(&global, 1);
*/		++global;
	}
	return NULL;
}

int main()
{
	int i = 0;
	pthread_t threads[1000];
	
	for(i = 0; i < 1000; ++i)
	{
		pthread_create(&threads[i], NULL, Thread, NULL);
	}
	for(i = 0; i < 1000; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	printf("%d\n", global);

	return 0;
}
