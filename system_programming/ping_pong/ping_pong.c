/******************************************************************************
 *	Title:		Signal Ping-Pong
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	22.04.2020.0
 ******************************************************************************/
#define _USE_POSIX199309
#define _XOPEN_SOURCE

#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/*  */
#include <stdio.h>		/* printf */
#include <sys/types.h>	/* fork */
#include <unistd.h>		/* fork */
#include <sys/wait.h>	/* wait */
#include <errno.h>		/* perror */
#include <signal.h>		/* signal */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sigaction action_handler_t;

int flag = 0;

void Ping(int);

void Pong(int);

/******FUNCTIONS******/
void Ping(int signum)
{
	flag = 1;	
}

void Pong(int signum)
{
	flag = 0;
}

int main ()
{
	pid_t pid = 0;
	action_handler_t parent;
	action_handler_t child;

	pid = fork();
	
	if (0 > pid)
	{
		perror("fork");
		exit(1);
	}

	if (0 == pid)
	{
		child.sa_handler = Pong;
		sigemptyset(&child.sa_mask);
		child.sa_flags = 0;
		
		sigaction(SIGUSR1, NULL, &parent);
		while(1)
		{
			sleep(1);
			if (0 == flag)
			{
				write(1, "|o     |\n\n", 10);
				kill(getppid(), SIGUSR2);
			}
		}
	}
	else
	{
		size_t rally = 0;
		parent.sa_handler = Ping;
		sigemptyset(&parent.sa_mask);
		parent.sa_flags = 0;

		sigaction(SIGUSR2, &child, NULL);
		while(1)
		{
			sleep(1);
			if (10 == rally)
			{
				kill(pid, SIGQUIT);
				break;
			}
			if (1 == flag)
			{
				write(1, "|     o|\n\n", 10);
				kill(pid, SIGUSR1);
				++rally;
			}
		}
	}

	return 0;
}
