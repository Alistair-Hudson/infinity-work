/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/

#include "watchdog.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))\

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
struct watchdog
{

};

/******FUNCTIONS******/
/*This is to be placed in a separate .c file TODO*/
int main (int argc, char* argv[])
{
/*set signal handler*/	
	/*set and run watchdog*/
	/*watchdog scheduler*/

	return 0;
}

watchdog_t *WatchdogStart(char *program_name, char *arguments[])
{
	pid_t pid = 0;
	/*create watchdog*/
	/*create dog watcher*/

	/*fork the process to begin watchdog*/
	if (0 > (pid = fork()))
	{
		perror("Fork failed");
		return NULL;
	}	
	if (0 == pid)
	{
		/*create watchdog scheduler*/
		/*add signal sending task*/
		/*add signal receiver task*/
		/*semaphore to notify watchdog is read to run*/
		if (0 > execv(args[0], args))
		{
			perror("Exec failed");
			return NULL;
		}		
	}
	else
	{
		/*set signal handler*/
		/*add signal sending task*/
		/*add signal receiving task*/
		/* semaphore to wait for dog*/
		/*create thread to run process scheduler*/
		return /*watchdog*/
	}
}

void WatchdogStop(watchdog_t *watchdog_instance)
{
	/*send stop to watchdog scheduler*/
	/*send stop to process scheduler*/

	/*destroy watchdog scheduler*/
	/*destroy process scheduler*/

	/*send process exit to watchdog*/

}

/*???????below  duplicate across to dog.c or can I use this just here??????*/
static void* ProcessThreadScheduler(void* arg)
{
	/*run scheduler*/
}

static void SignalReceived(int signum)
{
	oposite_process_is_alive = 1;
}

static int SendSignal(void* other_process_id)
{
	/*send signal to other process*/
	return 1;
}

static int IsAlive(void* arg)
{
	if (/*not other_process_is_alive*/)
	{
		/*reboot process*/
	}
	/*process is alive set to 0*/
	return 1;
}
















