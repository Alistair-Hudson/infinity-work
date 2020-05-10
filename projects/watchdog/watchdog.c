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

/******FUNCTIONS******/
watchdog_t *WatchdogStart(char *program_name, char *arguments[])
{
	/*create watchdog*/
	/*create watchdog scheduler*/
	/*create process scheduler*/

	/*fork the process to begin watchdog*/
	/*if fork returns an error*/
		/*perror*/
		/*return null*/	
	/*if child process*/
		/*add sending task*/
		/*add reeceeiving task*/
		/*run watchdog*/

	/*else*/
		/*add signal sending task*/
		/*add signal receiving task*/
		/*create thread to run process scheduler*/
		/*return watchdog*/
}

void WatchdogStop(watchdog_t *watchdog_instance)
{
	/*send stop to watchdog scheduler*/
	/*send stop to process scheduler*/

	/*destroy watchdog scheduler*/
	/*destropy process scheduler*/

}

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
	/*if not other process iis alive*/
		/*reboot process*/
	return 1;
}













