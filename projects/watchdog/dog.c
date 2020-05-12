/******************************************************************************
 *	Title:		Dog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	11/05/2020.0
 ******************************************************************************/
#define _USE_POSIX1993309
#define _XOPEN_SOURCE

#include <stdio.h> /*TODO*/

#include "watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sigaction action_handler_t;

static int watcher_is_alive = 0;

static void DogIsAliveReceived(int signum);
static void DogStop(int signum);
static int DogSendSignal(void* watcher_id);
static int DogIsAliveCheck(void* arg);

/******FUNCTIONS******/
int main (int argc, char* argv[])
{
	sched_t* dog_schedule;
	action_handler_t alive_handler = {0};
	action_handler_t stop_handler = {0};
	pid_t watcher_id = 0;
	int status = 0;

	/*assert(0 < argc);
	
	dog = argv[1];
	*/
	watcher_id = getppid();

	dog_schedule = SchedCreate();
	if (NULL == dog_schedule)
	{
		printf("Failed to create Scheduler for dog\n");
		return 1;
	}

	SchedAdd(dog_schedule, DogSendSignal, &watcher_id, 1, time(NULL));
	SchedAdd(dog_schedule, DogIsAliveCheck, &watcher_is_alive, 5, time(NULL));

	alive_handler.sa_handler = DogIsAliveReceived;
	stop_handler.sa_handler = DogStop;
	/*sem_post(dog->ready_to_start);
*/
	if(0 > sigaction(SIGUSR1, &alive_handler, NULL))
	{
		perror("Alive error");
		return 1;
	}
	if (0 > sigaction(SIGUSR2, &stop_handler, NULL))
	{
		perror("Stop error");
		return 1;
	}
	
	status = SchedRun(dog_schedule);

	return status;
}

static void DogStop(int signum)
{

}

static void DogIsAliveReceived(int signum)
{
	printf("Dog recieved\n");
	watcher_is_alive = 1;
}

int DogSendSignal(void* watcher_id)
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

int DogIsAliveCheck(void* arg)
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





























