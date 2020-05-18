<<<<<<< HEAD
/***********************************************************************BS"D****
*	Title:		WatchDog Dog
*	Authour:	Shmuel Sinder
*	Reviewer:	-
*	Version:	10.05.2020.0
*******************************************************************************/

#define _USE_POSIX199309
=======
/******************************************************************************
 *	Title:		Dog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	14/05/2020.0
 ******************************************************************************/
#define _USE_POSIX1993309
>>>>>>> ec4a06547a5f6ee06a82791ded2fd15a94c8314f
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

#include "scheduler.h"

typedef struct check_arg
{
<<<<<<< HEAD
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
int SendSignal(void *pid);
int StopScheduler(void *sched);
int SemInit(sem_t **is_dog_on, sem_t *should_stop);

static int g_to_stop;
static int g_is_user_alive = 1;
static sem_t g_should_stop;
static sem_t *g_is_dog_on;
static sched_t *g_sched;
static pid_t g_pid = 0;

static int SiganlsInit(void);
static void SginalHandler(int signal);

int main(int argc, char **argv)
=======
	char program_name[NAME_LIMIT];
	char* arguments[ARG_LIMIT];
}data_t;

static int watcher_is_alive = 1;
static int stop_dog = 0;
static sem_t* ready_to_start_sem;

static void DogIsAliveReceived(int signum);
static void DogStop(int signum);
static int DogSendSignal(void* watcher_id);
static int DogIsAliveCheck(void* arg);
static int StopDog(void* arg);

/******FUNCTIONS******/
int main (int argc, char** argv)
>>>>>>> ec4a06547a5f6ee06a82791ded2fd15a94c8314f
{
	check_arg_t check_arg = {0};

	g_pid = getppid();

	(void)argc;

	check_arg.sched = &g_sched;
	check_arg.to_stop = &g_to_stop;
	check_arg.is_alive = &g_is_user_alive;
	check_arg.is_child = 1;
	check_arg.pid = &g_pid;
	check_arg.argv = argv;

	/* inti the semaphores */
	

	if (0 != SemInit(&g_is_dog_on, &g_should_stop))
	{
		return 1;
	}

	/*call the signal handeling for SIGUSR1 and SIGUSR2 any other signal*/
	if (0 != SiganlsInit())
	{
		return 1;
	}

	g_sched = SchedCreate();
	if (NULL == g_sched)
	{
		return 1;
	}
	
	/*send a post the watchdog semaphore*/
	if (0 > sem_post(g_is_dog_on))
	{
		perror("kill fail: ");
		return 1;
	}

	/* schedular init */
	if (0 != SchedularInit(&check_arg))
	{
		return 1;
	}

	SchedDestroy(g_sched);

	if (0 > sem_destroy(&g_should_stop))
	{
		perror("sem_destroy fail: ");
	}

	if (0 > sem_close(g_is_dog_on))
	{
		perror("sem_close fail: ");
	}
	
	return 0;
}

static int SiganlsInit(void)
{
	struct sigaction signal_action = {0};

	signal_action.sa_handler = SginalHandler;

<<<<<<< HEAD
	if (0 > sigaction(SIGUSR1, &signal_action, NULL) || 						
		0 > sigaction(SIGUSR2, &signal_action, NULL))
=======
static int DogSendSignal(void* watcher_id)
{
	pid_t id = *(int*)watcher_id;
	printf("dog sent\n");
	/*send signal to other process*/
	if (0 > kill(id, SIGUSR1))
>>>>>>> ec4a06547a5f6ee06a82791ded2fd15a94c8314f
	{
		perror("sigaction fail: ");
		return 1;
	}
	/* same other signals should be also included and ignored if received */

	return 0;
}

<<<<<<< HEAD
static void SginalHandler(int signal)
=======
static int DogIsAliveCheck(void* arg)
>>>>>>> ec4a06547a5f6ee06a82791ded2fd15a94c8314f
{
	if (SIGUSR1 == signal)
	{
		g_is_user_alive = 1;
	}

<<<<<<< HEAD
	/* SIGUSR2 is for stoping the process */
	else if (SIGUSR2 == signal)
=======
static int StopDog(void* arg)
{
	sched_t* dog = arg;
	if(stop_dog)
>>>>>>> ec4a06547a5f6ee06a82791ded2fd15a94c8314f
	{
		g_to_stop = 1;
	}
}

