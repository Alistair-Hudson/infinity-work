/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/

#include "watchdog.h"
#include <semaphore.h>  /* semaphore functions */
#include <signal.h>		/* signal functions */

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
	pid_t watching_id;
};

sem_t ready_to_start_sem;

static int dog_is_alive = 0;

static void* ProcessThreadScheduler(void* arg);
static void IsAliveHandler(int signum);
static int SendSignal(void* dog_id);
static int IsAliveReceived(void* arg);

/******FUNCTIONS******/

watchdog_t *WatchdogStart(char *program_name, char *arguments[])
{
	pid_t pid = 0;
	action_handler_t sig_handler = {0};
	watchdog_t* dog;
	pthread_t watcher_thread;

	assert(NULL != program_name);


	/*create watchdog*/
	dog = malloc(sizeof(watchdog_t));
	if (NULL == dog)
	{
		return NULL;
	}
	/*create dog watcher*/
	
	/*set semaphore*/

	/*set signal handler for dog watcher*/
	sig_handler.sa_handler = IsAliveReceived;
	if (0 > sigaction(SIGUSR1, &sig_handler, NULL))
	{
		perror("Sigaction error");
		return 1;
	}

	/*fork the process to begin watchdog*/
	if (0 > (pid = fork()))
	{
		perror("Fork failed");
		return NULL;
	}	
	if (0 == pid)
	{
		char* args[] = {"./dog", NULL};
		/*create watchdog scheduler*/
		/*add signal sending task*/
		/*add signal receiving task*/
		/*semaphore to notify watchdog is read to run*/
		if (0 > execv(ags[0], args))
		{
			perror("Exec failed");
			return NULL;
		}		
	}
	else
	{
		dog->watching_id = pid;
		/*add signal sending task*/
		/*add signal receiving task*/
		/*semaphore to wait for dog*/
		/*create thread to run process scheduler*/
		pthread_create(&watcher_thread, NULL, ProcessThreadScheduler, NULL);
		pthread_detach();
		return dog;
	}
}

void WatchdogStop(watchdog_t *dog)
{
	/*send stop to watchdog scheduler*/
	/*SchedStop(dog->sched);
	/*send stop to process scheduler*/
	/*SchedStop(watch->sched);

	/*destroy watchdog scheduler*/
	/*SchedDestroy(dog->sched);
	/*destroy process scheduler*/
	/*SchedDestroy(watch->sched);

	/*send process exit to watchdog*/
	if (0 > kill(dog->watching_id, SIGQUIT))
	{
		perror("Kill error");
	}

}


static void* ProcessThreadScheduler(void* arg)
{
	int count = 0;
	while(1)
	{
		sleep(1);
		SendSignal();

		++count;
		if(5 == count)
		{
			IsAliveCheck(&dog_is_alive);
			count = 0;
		}
	}
}

static void IsAliveReceived(int signum)
{
	printf("watcher recieved\n");
	dog_is_alive = 1;
}

static int SendSignal(void* dog_id)
{
	pid_t id = *(int*)dog_id;
	printf("watcher sent\n");
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
	int dog_is_alive = *(int*)arg;
	printf("watcher check\n");
	if (!dog_is_alive)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}

}















