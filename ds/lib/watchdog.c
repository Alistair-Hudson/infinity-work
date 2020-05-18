/***********************************************************************BS"D****
*	Title:		WatchDog
*	Authour:	Shmuel Sinder
*	Reviewer:	-
*	Version:	10.05.2020.0
*******************************************************************************/

#define _USE_POSIX199309
#define _XOPEN_SOURCE

#include <stdio.h>
#include <sys/types.h> 		/* kill */
#include <signal.h> 		/* kill, sigaction */
#include <time.h> 			/* time */
#include <assert.h>			/* assert */
#include <errno.h>			/* perror */

#include <semaphore.h>		/* sem_t, sem_post, sem_wait */
#include <fcntl.h>  		/* sem_open */
#include <sys/stat.h> 

#include <pthread.h>		/* pthread_t, phtread_create */

#include "scheduler.h"
#include "watchdog.h"

#define FREC	(1)
#define SEM_NAME	("is_dog_on")

typedef struct check_arg
{
	sched_t **sched;
	int *to_stop;
	int *is_alive;
	int is_child;
	pid_t *pid;
    char *pathname;
	char **argv;
} check_arg_t;

int SchedularInit(check_arg_t *check_arg);
int CheckSignal(void *arg);
int SendSignal(void *arg);
int SemInit(sem_t **is_dog_on, sem_t *should_stop);

static int g_to_stop;
static pthread_t g_thread_id;
static int g_is_dog_alive;
static sem_t *g_is_dog_on;
static sem_t g_should_stop;
static pid_t g_pid;
static sched_t *g_sched = NULL;
static char *g_pathname;
static char **g_argv;
static int g_is_end;

void __attribute__((constructor)) ConstructorFunct(); 
void __attribute__((destructor)) DestructorFunct(); 

void ConstructorFunct(void);
void DestructorFunct(void);

static int SiganlsInit(void);
static void SginalHandler(int signal);

static void *ThreadFunct(void *arg);

void ConstructorFunct(void)
{
	/* init the semaphores */
	if (0 != SemInit(&g_is_dog_on, &g_should_stop))
	{
		return ;
	}
	
	/*call the signal handeling for SIGUSR1*/
	if (0 != SiganlsInit())
	{
		return ;
	}

	/* create Schedular */
	g_sched = SchedCreate();
	if (NULL == g_sched)
	{
		return ;
	}

	pthread_create(&g_thread_id, NULL, &ThreadFunct, NULL);

}

void DestructorFunct(void)
{
	if (0 > sem_destroy(&g_should_stop))
	{
		perror("sem_destroy fail: ");
	}

	if (0 > sem_close(g_is_dog_on))
	{
		perror("sem_close fail: ");
	}

	g_is_end = 1;
	sem_post(&g_should_stop);

	pthread_join(g_thread_id, NULL);

}


int WatchdogStart(char *pathname, char **argv)
{	
	g_pathname = pathname;
	g_argv = argv;

	if (0 > sem_post(&g_should_stop))
	{
		perror("sem_post fail: ");
		return 1;
	}

	return 0;
}	

static void *ThreadFunct(void* arg)
{	
	check_arg_t check_arg = {0};

	(void)arg;

	check_arg.sched = &g_sched;
	check_arg.to_stop = &g_to_stop;
	check_arg.is_alive = &g_is_dog_alive;
	check_arg.is_child = 0;
	check_arg.pid = &g_pid;
	check_arg.argv = g_argv;

	while (!g_is_end)
	{
		/* wait fot WatchdogStart call */
		if (0 > sem_wait(&g_should_stop))
		{
			return NULL;
		}

		if (!g_is_end)
		{
			/* create the dog process */
			CheckSignal(&check_arg);
		
			/*wait to dog start*/
			if (0 > sem_wait(g_is_dog_on))
			{
				perror("sem_wait fail: ");
				return NULL;
			}		

			/* schedular init */
			if (0 != SchedularInit(&check_arg))
			{
				return NULL;
			}
		}
	}

	SchedDestroy(g_sched);

	return NULL;

}

int SemInit(sem_t **is_dog_on, sem_t *should_stop)
{
	*is_dog_on = sem_open("is_dog_on", O_CREAT, 0644, 0);
	if (SEM_FAILED == *is_dog_on)
	{
		perror("sem_open fail: ");
		return 1;
	}

	if (0 > sem_init(should_stop, 0, 0))
	{
		perror("sem_init fail: ");
		return 1;
	}

	return 0;
}

void WatchdogStop(void)
{
	/* signal to kill the children */
	if (0 > kill(g_pid, SIGUSR2))
	{
		perror("kill fail: ");
	}

	g_to_stop = 1;
}

static int SiganlsInit(void)
{
	struct sigaction signal_action = {0};

	signal_action.sa_handler = SginalHandler;

	if (0 > sigaction(SIGUSR1, &signal_action, NULL))
	{
		perror("sigaction fail: ");
		return 1;
	}
	/* same other signals should be also included and ignored if received */

	return 0;
}

static void SginalHandler(int signal)
{
	if (SIGUSR1 == signal)
	{
		g_is_dog_alive = 1;
	}
}

int SchedularInit(check_arg_t *check_arg)
{
	ilrd_uid_t uid = {0};

	uid = SchedAdd(*(check_arg->sched), CheckSignal, (void*)check_arg,
					 FREC + 5, time(NULL) + 5);
	if (0 != UIDIsSame(bad_uid, uid))
	{
		return 1;
	}
	
	uid = SchedAdd(*(check_arg->sched), SendSignal, check_arg, FREC, time(NULL));
	if (0 != UIDIsSame(bad_uid, uid))
	{
		return 1;
	}
	
	if (0 != SchedRun(*(check_arg->sched)))
	{
		return 1;
	}

	*(check_arg->to_stop) = 0;

	return 0;
}

int CheckSignal(void *arg)
{
	check_arg_t *check_arg = (check_arg_t*)arg;

	#ifndef NDEBUG
		static int i;
		printf("checking signal ... %d\n", i++);
		printf("pid is: %d\n", *(check_arg->pid));
    #endif
	
	if (!*(check_arg->is_alive))
	{
		if (!(check_arg->is_child))
		{
			printf("fork and  execv\n");
			*(check_arg->pid) = fork();

			if (0 == *(check_arg->pid))
			{
				if (0 > execv("./dog", check_arg->argv))
				{
					perror("execv fail: ");
					return (-1);
				}
			}
		}
		else
		{
			printf("only execv\n");
			printf("check_arg->argv[0] %s\n", check_arg->argv[0]);
			if (0 > execv(check_arg->argv[0], check_arg->argv))
			{
				perror("execv fail: ");
				return (-1);
			}
		}
	}
	else
	{
		*(check_arg->is_alive) = 0;
	}

	if (*(check_arg->to_stop))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
	
int SendSignal(void *arg)
{
	check_arg_t *check_arg = (check_arg_t*)arg;

	#ifndef NDEBUG
		static int i;
        printf("sending signal ...%d\n", i++);
		printf("pid is: %d\n", *(check_arg->pid));
    #endif


	if (0 > kill(*(check_arg->pid), SIGUSR1))
	{
		perror("kill fail: ");
		return (-1);
	}
		
	if (*(check_arg->to_stop))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
