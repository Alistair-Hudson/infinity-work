pthread_mutex _t cond_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int ready = 0;
int winner = 0;
int tid = 0

void* RaceTrack(void* arg)
{
	int thread = 0;
	pthread_mutex_lock(cond_lock);
	while (!ready)
	{
		pthread_cond_wait(&condition, &cond_lock);
	}
	thread =  _sync_fetch_and_add(&tid, 1);
_sync_compare_and_swap(&winner, 0, thread)
}

void Go(void)
{
	pthread_mutex_lock(&cond_lock);
	ready = 1;
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&cond_lock);
}

int main()
{
	pthread_t threads[8]
	int i = 0;
	
	for (i = 0, i < 8, ++i)
	{
		pthread_create(&threads[i], NULL, RaceTrack, NULL);
	}
	
	sleep(5);
	Go();
	sleep(5);

for (i =0; i < 8; ++i)
{
	pthread_join(threads[i], NULL);
}

printf(?The winner is %d\n?, winner);
	return 0;
}

