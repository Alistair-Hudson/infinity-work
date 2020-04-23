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
	int signum = 0;
	pid_t id = 0;
	char str[10] = {0};

	parent.sa_handler = Ping;
	child.sa_handler = Pong;

	sigaction(SIGUSR1, NULL, &parent);
	sigaction(SIGUSR2, &child, NULL);

	pid = fork();
	
	if (0 > pid)
	{
		perror("fork");
		exit(1);
	}

	if (0 == pid)
	{
		signum = SIGUSR2;
		id = getppid();
		str = "|o    |";
	}
	else
	{
		signum = SIGUSR1;
		id = pid;
		str = "|    o|";
	}

	while(1)
	{
		if(signal)
		{
			printf("%s", str);
			sleep(1);
			kill(id, signum);
			signal = 0;
		}
	}

	return 0;
}
