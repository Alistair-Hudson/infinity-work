/******************************************************************************
 *	Title:		Signal Ping-Pong
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel
 *	Version:	27.04.2020.2
 ******************************************************************************/
#define _USE_POSIX199309
#define _XOPEN_SOURCE

#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* strcpy */
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
	assert(NULL != signum);
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
		if(0 > sigaction(SIGUSR1, &parent, NULL))
		{
			perror("Parent Sigaction error");
			return 1;
		}
	}
	else
	{
		signum = SIGUSR2;
		id = pid;
		strcpy(str, "|    o|");
		if(0 > sigaction(SIGUSR2, &child, NULL))
		{
			perror("Child Sigaction error");
			return 1;
		}
	}

	while(1)
	{
		sleep(10);
		if(1 == hit_back)
		{
			printf("%s\n", str);
			hit_back = 0;
			if(0 > kill(id, signum))
			{
				perror("Signal error");
				return 1;
			}

			if (0 < pid)
			{
				++rally;
			}
			if (10 <= rally)
			{
				if(0 > kill(id, SIGQUIT))
				{
					perror("Kill error");
					return 1;
				}
				return 0;				
			}
		}
	}

	return 1;
}



