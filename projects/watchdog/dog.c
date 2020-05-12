/******************************************************************************
 *	Title:		Dog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	11/05/2020.0
 ******************************************************************************/

#include "watchdog.c"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sigaction action_handler_t;

static watcher_is_alive = 0;

static void IsAliveReceived(int signum);
static int SendSignal(void* watcher_id);
static int IsAliveCheck(void* arg);

/******FUNCTIONS******/
int main ()
{
	pid_t watcher = 0;
	action_handler_t sig_handler = {0};
	pid_t watcher_id = 0;
	int count = 0;

	sig_handler.sa_handler = IsAliveReceived;

	if(0 > sigaction(SIGUSR1, &sig_handler, NULL));
	{
		perror("Sigaction error");
		return 1;
	}

	watcher_id = getppid();

	while(1)
	{
		sleep(1);
		SendSignal(&watcher_id)
		
		++count;
		if(5 == count)
		{
			IsAliveCheck(&watcher_is_alive);
			count = 0;
		}
	}
	return 1;
}


static void IsAliveReceived(int signum)
{
	printf("Dog recieved\n");
	watcher_is_alive = 1;
}

static int SendSignal(void* watcher_id)
{
	pid_t id = *(int*)watcher_id;
	printf("dog sent\n");
	/*send signal to other process*/
	if (0 > kill(id, SIGUSR1))
	{
		perror(“Signal Error”);
		return 0;
	}
	return 1;
}

static int IsAliveCheck(void* arg)
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






























