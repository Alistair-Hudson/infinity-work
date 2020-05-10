#include <stdio.h>
#include <pthread.h>

int global;

void* Map(void* arg)
{
	static int t;
	(void)arg;

	return NULL;
}

int main()
{
	pthread_t thread[5];
	int i;
	
	for (i = 0; i < 5; ++i)
	{
		pthread_create(&thread[i], NULL, Map, NULL);
	}
	for (i = 0; i < 5; ++i)
	{
		pthread_join(thread[i], NULL);
	}

	return 0;
}
