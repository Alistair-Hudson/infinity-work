/******************************************************************************
 *	Title:		Signal Ping-Pong
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	23.04.2020.0
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

static volatile int hit_back = 0;

void Hit(int);

int PingPong1(void);

/******FUNCTIONS******/
int main()
{
	int status = 0;

	status = PingPong1();

	return status;
}

void Hit(int signum)
{
	hit_back = 1;
}

int PingPong1(void)
{
	pid_t pid = 0;
	action_handler_t parent = {0};
	action_handler_t child = {0};
	int signum = 0;
	pid_t id = 0;
	char str[10] = {0};
	size_t rally = 0;

	parent.sa_handler = Hit;
	child.sa_handler = Hit;

	sigaction(SIGUSR1, &parent, NULL);
	sigaction(SIGUSR2, &child, NULL);

	pid = fork();
	
	if (0 > pid)
	{
		perror("Fork error");
		return 1;
	}

	if (0 == pid)
	{
		signum = SIGUSR1;
		hit_back = 1;
		id = getppid();
		strcpy(str, "|o    |");
	}
	else
	{
		signum = SIGUSR2;
		id = pid;
		strcpy(str, "|    o|");
	}

	while(1)
	{
		sleep(10);
		if(1 == hit_back)
		{
			printf("%s\n", str);
			kill(id, signum);
			hit_back = 0;
			if (0 < pid)
			{
				++rally;
			}
			if (10 <= rally)
			{
				kill(id, SIGQUIT);
				return 0;				
			}
		}
	}

	return 1;
}



