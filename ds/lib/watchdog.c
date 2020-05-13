/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/
#define _USE_POSIX1993309
#define _XOPEN_SOURCE

#include <string.h> 	/* strncpy */

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
	char program_name[NAME_LIMIT];
	pid_t watching_id;
	sem_t* ready_to_start;
	sched_t* schedule;
};

sem_t ready_to_start_sem;

static int dog_is_alive = 0;

static void* ProcessThreadScheduler(void* arg);
static void IsAliveReceived(int signum);
static int SendSignal(void* dog_id);
static int IsAliveCheck(void* arg);

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
	dog->schedule = SchedCreate();
	if (NULL == dog->schedule)
	{
		return NULL;
	}
	strncpy(dog->program_name, program_name, NAME_LIMIT);
	/*create dog watcher*/
	
	/*set semaphore*/
	dog->ready_to_start = &ready_to_start_sem;

	/*set signal handler for dog watcher*/
	sig_handler.sa_handler = IsAliveReceived;
	if (0 > sigaction(SIGUSR1, &sig_handler, NULL))
	{
		perror("Sigaction error");
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
		char* args[] = {"./dog", &dog->program_name, NULL};
		/*create watchdog scheduler*/
		/*add signal sending task*/
		/*add signal receiving task*/
		/*semaphore to notify watchdog is read to run*/
		if (0 > execv(args[0], args))
		{
			perror("Exec failed");
			return NULL;
		}		
	}
	else
	{
		dog->watching_id = pid;
		/*add signal sending task*/
		SchedAdd(dog->schedule, SendSignal, &dog->watching_id, SEND_TIME, time(NULL));
		/*add signal receiving task*/
		SchedAdd(dog->schedule, IsAliveCheck, &dog_is_alive, RECEIVE_TIME, time(NULL));
		/*semaphore to wait for dog*/
		/*sem_wait(&ready_to_start_sem);
		/*create thread to run process scheduler*/
		sleep(5);
		pthread_create(&watcher_thread, NULL, ProcessThreadScheduler, dog);
		pthread_detach(pthread_self());
		return dog;
	}
	return NULL;
}

void WatchdogStop(watchdog_t *dog)
{
	/*send process exit to watchdog*/
	if (0 > kill(dog->watching_id, SIGQUIT))
	{
		perror("Kill error");
	}
	/*send stop to watchdog scheduler*/
	/*SchedStop(dog->sched);
	/*send stop to process scheduler*/
	SchedStop(dog->schedule);

	/*destroy watchdog scheduler*/
	/*SchedDestroy(dog->sched);
	/*destroy process scheduler*/
	SchedDestroy(dog->schedule);
}


static void* ProcessThreadScheduler(void* arg)
{
	watchdog_t* dog = arg;
	SchedRun(dog->schedule);
	return NULL;
}

static void IsAliveReceived(int signum)
{
	printf("watcher recieved\n");
	dog_is_alive = 1;
}

int SendSignal(void* dog_id)
{
	pid_t id = *(int*)dog_id;
	printf("watcher sent\n");
	/*send signal to other process*/
	if (0 > kill(id, SIGUSR1))
	{
		perror("Signal Error");
		return 0;
	}
	return 1;
}

int IsAliveCheck(void* arg)
{
	pid_t pid = 0;
	watchdog_t* dog = arg;

	printf("watcher check\n");
	if (!dog_is_alive)
	{
		/*reboot process*/
		if(0 > (pid = fork()))
		{
			perror("Fork error");
		}
		if(0 == pid)
		{
			char* args[] = {"./dog", &dog->program_name, NULL};
			if (0 > execv(args[0], args))
			{
				perror("Exec failed");
				return NULL;
			}		
		}
		else
		{
			dog->watching_id = pid;
		}
		
	}
	dog_is_alive = 0;
	return 1;
}















