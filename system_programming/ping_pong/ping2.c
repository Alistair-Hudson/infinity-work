/******************************************************************************
 *	Title:		Signal Ping
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

static int hit_back = 0;

void hit(int);

int PingPong2(void);

/******FUNCTIONS******/
int main()
{
	int status = 0;

	status = PingPong2();

	return status;
}

int PingPong2(void)
{
	pid_t pid = 0;

	pid = fork();
	
	if (0 > pid)
	{
		perror("Fork error");
		return 1;
	}
	
	if (0 == pid)
	{
		char* args[] = {"./", NULL};

		execv(args[0], args);
	}
	else
	{
		
	}

	return 0;
}

void Hit(int signum)
{
	hit_back = 1;
}

