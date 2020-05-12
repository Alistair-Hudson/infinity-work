/******************************************************************************
 *	Title:		Dog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	11/05/2020.0
 ******************************************************************************/
#include <stdio.h> /*TODO*/

#include "watchdog.c"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static int watcher_is_alive = 0;

static void DogIsAliveReceived(int signum);
static int DogSendSignal(void* watcher_id);
static int DogIsAliveCheck(void* arg);

/******FUNCTIONS******/
int main (int argc, char* argv[])
{
	watchdog_t* dog;
	action_handler_t sig_handler = {0};
	pid_t watcher_id = 0;
	int count = 0;

	assert(0 < argc);

	dog = argv[1];

	sig_handler.sa_handler = DogIsAliveReceived;
	
	sem_post(dog->ready_to_start);

	if(0 > sigaction(SIGUSR1, &sig_handler, NULL))
	{
		perror("Sigaction error");
		return 1;
	}

	watcher_id = getppid();

	while(1)
	{
		sleep(1);
		DogSendSignal(&watcher_id);
		
		++count;
		if(5 == count)
		{
			DogIsAliveCheck(&watcher_is_alive);
			count = 0;
		}
	}
	return 1;
}


static void DogIsAliveReceived(int signum)
{
	printf("Dog recieved\n");
	watcher_is_alive = 1;
}

static int DogSendSignal(void* watcher_id)
{
	pid_t id = *(int*)watcher_id;
	printf("dog sent\n");
	/*send signal to other process*/
	if (0 > kill(id, SIGUSR1))
	{
		perror("Signal error");
		return 0;
	}
	return 1;
}

static int DogIsAliveCheck(void* arg)
{
	int watcher_is_alive = *(int*)arg;
	printf("dog check\n");
	if (!watcher_is_alive)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}






























