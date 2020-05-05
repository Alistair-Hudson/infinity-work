#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void* Thread(void* arg)
{
	sem_wait(&sem);
	printf("Start\n");

	sleep(4);

	printf("Exit\n");
	sem_post(&sem);

	return NULL;
}

int main()
{
	pthread_t tid[2];
	int i = 0;

	sem_init(&sem, 0, 1);

	while (i < 2)
	{
		pthread_create(&tid[i], NULL, Thread, NULL);
		sleep(2);
		++i;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(tid[i], NULL);
		++i;
	}

	sem_destroy(&sem);
	return 0;
}
