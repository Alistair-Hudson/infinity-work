#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2];
int counter = 0;
pthread_mutex_t lock[2];

void* TryThis(void* arg)
{
	unsigned long i = 0;
	(void)arg;
	pthread_mutex_lock(&lock[0]);

	counter += 1;
	printf("Thread %d start\n", counter);

	for (i = 0; i < 0xFFFFFFFF; ++i)
		;

	printf("Thread %d finished\n", counter);

	pthread_mutex_unlock(&lock[0]);

	return NULL;
}

int main(void)
{
	int i = 0;
	int error;

	if (pthread_mutex_init(&lock[0], NULL))
	{
		perror("mutex init failed");
		return 1;
	}

	while (i < 2)
	{
		if (pthread_create(&tid[i], NULL, &TryThis, NULL))
		{
			perror("failed to create thread");
		}
		++i;
	}
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock[0]);

	return 0;
}
