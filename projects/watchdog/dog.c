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
action_handler_t dog = {0};

/*set signal handler*/	
dog.sa_handler = IsAliveReceived;
	if(0 > sigaction(SIGUSR1, &dog, NULL))
	{
		perror(“Sigaction failed”);
		return 1;
	}
	/*run watchdog scheduler*/
	SchedRun(watchdog_sched);

	return 0;
}

















