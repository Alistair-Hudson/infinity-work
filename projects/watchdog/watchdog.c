/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/

#include "watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define SEND_TIME				(1)
#define RECEIVE_TIME			(5)
#define NAME_LIMIT				(15)
#define ARG_LIMIT				(5)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sigaction action_handler_t;

struct watchdog
{
sem_t* dog_is_ready;
action_handler_t sig_hand;
sched_t *sched;
volatile int other_process_is_alive;
char program_name[NAME_LIMIT];
char *program_args[ARG_LIMIT];
};

sem_t ready_to_start_sem;

/******FUNCTIONS******/

watchdog_t *WatchdogStart(char *program_name, char *arguments[])
{
	pid_t pid = 0;
	action_handler_t watcher = {0};
	watchdog_t* dog;
	watchdog_t* watcher;
	pthread_t watcher_tread;
	
	assert(NULL != program_name);
	
	/*create watchdog*/
	dog = malloc(sizeof(watchdog_t));
	if (NULL == dog)
	{
		return NULL;
	}
	/*create dog watcher*/
	watcher = malloc(sizeof(watchdog_t));
	if(NULL == watcher)
	{
		free(dog);
		return NULL;

	}

	dog->other_process_is_alive = 0;
	watcher->other_process_is_alive = 0;
	/*set semaphore*/
	dog->dog_is_ready = ready_to_start_sem;
	watcher->dog_is_ready = ready_to_start_sem;
	/*set signal handler for dog watcher*/
	watcher->sig_hand.sa_handler = IsAliveReceived;
	

	if(0 > sigaction(SIGUSR1, watcher->sig_hand, NULL))
	{
		perror(“Sigaction failed”);
		return NULL;
	}

	/*fork the process to begin watchdog*/
	if (0 > (pid = fork()))
	{
		perror("Fork failed");
		return NULL;
	}	
	if (0 == pid)
	{
		/*create watchdog scheduler*/
		dog->sched = SchedCreate();
		/*add signal sending task*/
		SchedAdd(watchdog_sched, SendSignal, watcher_id, SEND_TIME, 0);
		/*add signal receiving task*/
		SchedAdd(watcher_sched, IsAliveReceived, SIGUSR2, RECEIVE_TIME, 0);
		/*semaphore to notify watchdog is read to run*/
		sem_post(&dog_is_ready);
		if (0 > execv(args[0], args))
		{
			perror("Exec failed");
			return NULL;
		}		
	}
	else
	{
		/*add signal sending task*/
		SchedAdd(dog_watcher_sched, SendSignal, watchdog_id, SEND_TIME, 0);
		/*add signal receiving task*/
		SchedAdd(dog_watcher_sched, IsAliveReceived, SIGUSR1, RECEIVE_TIME, 0);
		/* semaphore to wait for dog*/
		sem_wait(watcher->dog_is_ready);
		/*create thread to run process scheduler*/
		pthread_create(&watcher_thread, NULL, ProcessThreadScheduler, &dog_watch_sched);
		pthread_detach();
		return /*watchdog*/
	}
}

void WatchdogStop(watchdog_t *watchdog_instance)
{
	/*send stop to watchdog scheduler*/
	SchedStop(watchdog_sched);
	/*send stop to process scheduler*/
	SchedStop(watch_sched);

	/*destroy watchdog scheduler*/
	SchedDestroy(watchdog_sched);
	/*destroy process scheduler*/
	SchedDestroy(watch_sched);

	/*send process exit to watchdog*/

}

/*???????below  duplicate across to dog.c or can I use this just here??????*/
static void* ProcessThreadScheduler(void* arg)
{
	SchedRun(dog_watch_sched);
}

static void IsAliveReceived(int signum)
{
	oposite_process_is_alive = 1;
}

static int SendSignal(void* other_process_id)
{
	printf("watcher sends\n");
	/*send signal to other process*/
	if (0 > kill(other_process_id, signum))
	{
		perror(“Signal Error”);
		return 0;
	}
	return 1;
}

static int IsAliveReceived(void* arg)
{
	printf("watcher checks\n");
	if (!other_process_is_alive)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}















