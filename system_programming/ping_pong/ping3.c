/******************************************************************************
 *	Title:		Signal Ping ex3
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

static void Hit(int);

/******FUNCTIONS******/
static void Hit(int signum)
{
	hit_back = 1;
}

int main ()
{
	pid_t pid = 0;
	action_handler_t ping = {0};
	int signum = 0;
	pid_t id = 0;
	char str[10] = {0};
	size_t rally = 0;

	child.sa_handler = Hit;

	sigaction(SIGUSR1, &ping, NULL);

	signum = SIGUSR2;
	strcpy(str, "|o    |");

	while(1)
	{
		if(1 == hit_back)
		{
			printf("%s\n", str);
			sleep(1);
			kill(id, signum);
			hit_back = 0;

			if (10 <= rally)
			{
				kill(id, SIGQUIT);
				return 0;				
			}
		}
	}
	return 1;
}
