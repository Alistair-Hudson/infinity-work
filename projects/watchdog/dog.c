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
watchdog_t dog = {0};

assert(0 < argc);

dog = argv[1];
dog.sig_hand = {0};

/*set signal handler*/	
dog.sig_hand.sa_handler = IsAliveReceived;
	if(0 > sigaction(SIGUSR1, &dog.sig_hand, NULL))
	{
		perror(“Sigaction failed”);
		return 1;
	}
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
	if (!other_process_is_alive)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}






























