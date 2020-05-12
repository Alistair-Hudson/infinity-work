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

/******FUNCTIONS******/
int main (int argc, char* argv[])
{
	/*set watchdog*/
	watchdog_t* dog;

	assert(0 < argc);

	while(NULL == (dog.sched = SchedCreate()))
	{
	}

	dog = argv[1];
	dog->sig_hand = {0};

	/*set signal handler*/	
	dog->sig_hand.sa_handler = IsAliveReceived;
	if(0 > sigaction(SIGUSR1, dog->sig_hand, NULL))
	{
		perror(“Sigaction failed”);
		return 1;
	}

	SchedAdd(dog.sched, SendSignal, dog.other_id, 1, 0);
	SchedAdd(dog.sched, IsAliveReceived, dog.other_id, 5, 0);

	sem_post(dog->dog_is_ready);

	/*run watchdog scheduler*/
	SchedRun(watchdog_sched);

	return 0;
}


static void IsAliveReceived(int signum)
{
	oposite_process_is_alive = 1;
}

static int SendSignal(void* other_process_id)
{
	printf("dog sent\n");
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
	printf("dog chjeck\n");
	if (!other_process_is_alive)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}






























