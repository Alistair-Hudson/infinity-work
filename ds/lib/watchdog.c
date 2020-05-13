/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/
#define _USE_POSIX1993309
#define _XOPEN_SOURCE

#include <string.h> 	/* strncpy */
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

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
	char* arguments[ARG_LIMIT];
	pid_t watching_id;
	sched_t* schedule;
};

static sem_t* ready_to_start_sem;

static int dog_is_alive = 1;

static void* ProcessThreadScheduler(void* arg);
static void IsAliveReceived(int signum);
static void ReleaseSem(int signum);
static int SendSignal(void* dog_id);
static int IsAliveCheck(void* arg);

/******FUNCTIONS******/

watchdog_t *WatchdogStart(char *program_name, char* arguments[])
{
	pid_t pid = 0;
	action_handler_t sig_handler = {0};
	action_handler_t sem_handler = {0};
	watchdog_t* dog;
	pthread_t watcher_thread;
	int i = 0;

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
	dog->arguments[0] = "./dog";
	for (i = 1; i < ARG_LIMIT; ++i)
	{
		dog->arguments[i] = arguments[i-1];
	}

	/*create dog watcher*/
	ready_to_start_sem = sem_open("shared semaphore", O_CREAT, 0666, 0);
	/*fork the process to begin watchdog*/
	if (0 > (pid = fork()))
	{
		perror("Fork failed");
		return NULL;
	}	
	if (0 == pid)
	{
		if (0 > execv("./dog", dog->arguments))
		{
			perror("Exec failed");
			return NULL;
		}		
	}
	else
	{
		/*set signal handler for dog watcher*/
		sig_handler.sa_handler = IsAliveReceived;
		if (0 > sigaction(SIGUSR1, &sig_handler, NULL))
		{
			perror("Sigaction error");
			return NULL;
		}
		dog->watching_id = pid;
		/*add signal sending task*/
		SchedAdd(dog->schedule, SendSignal, &dog->watching_id, SEND_TIME, time(NULL));
		/*add signal receiving task*/
		SchedAdd(dog->schedule, IsAliveCheck, &dog_is_alive, RECEIVE_TIME, time(NULL));
		/*semaphore to wait for dog*/
		sem_wait(ready_to_start_sem);
		/*create thread to run process scheduler*/
		pthread_create(&watcher_thread, NULL, ProcessThreadScheduler, dog);
		pthread_detach(pthread_self());
		return dog;
	}
	return NULL;
}

void WatchdogStop(watchdog_t *dog)
{
	/*send stop to watchdog scheduler*/
	if (0 > kill(dog->watching_id, SIGUSR2))
	{
		perror("send stop error");
	}
	sem_wait(ready_to_start_sem);
	/*send process exit to watchdog*/
	if (0 > kill(dog->watching_id, SIGQUIT))
	{
		perror("Kill error");
	}
	
	/*send stop to process scheduler*/
	SchedStop(dog->schedule);

	/*destroy process scheduler*/
	SchedDestroy(dog->schedule);

	if (0 > sem_close(ready_to_start_sem))
	{
		perror("failed to close sem");
	}
	if (0 > sem_destroy(ready_to_start_sem))
	{
		perror("failed to close sem");
	}
}


static void* ProcessThreadScheduler(void* arg)
{
	watchdog_t* dog = arg;
	SchedRun(dog->schedule);
	return NULL;
}

static void IsAliveReceived(int signum)
{
	(void)signum;
	printf("watcher recieved\n");
	dog_is_alive = 1;
}

static void ReleaseSem(int signum)
{
	(void)signum;

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
			printf("rebooting\n\n\n");
		/*reboot process*/
		if(0 > (pid = fork()))
		{
			perror("Fork error");
		}
		if(0 == pid)
		{
			
			if (0 > execv("./dog", dog->arguments))
			{
				perror("Exec failed");
				return 0;
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















