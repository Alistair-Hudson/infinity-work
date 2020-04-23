/******************************************************************************
 *	Title:		Signal Ping-Pong
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	22.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/* malloc, free */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */
#include <sys/types.h>	/* fork */
#include <unistd.h>		/* fork */
#include <sys/wait.h>	/* wait */
#include <errno.h>		/* perror */
#include <signal.h>		/* signal */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static void Ping(int);

static void Pong(int);

/******FUNCTIONS******/
static void Ping(int signum)
{
	signal(SIGUSR1, Ping);
	printf("|o     |\n\n");
}

static void Pong(int signum)
{
	signal(SIGUSR2, Pong);
	printf("|     o|\n\n");

}

int main ()
{
	pid_t pid = 0;

	pid = fork();
	
	if (0 > pid)
	{
		perror("fork");
		exit(1);
	}

	if (0 == pid)
	{
		signal(SIGUSR1, Ping);
		while(1)
		{

/*			sleep(5);
			kill(getppid, SIGUSR2);
*/		}
	}
	else
	{
		kill(pid, SIGUSR1);
/*		signal(SIGUSR2, Pong);
		while(1)
		{
			sleep(5);
			kill(pid, SIGUSR1);
		}*/
	}

	return 0;
}
