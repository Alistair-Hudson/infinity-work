/******************************************************************************
 *	Title:		Signal Pong
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
#include <errno.h>		/* perror */
#include <signal.h>		/* signal */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sigaction action_handler_t;

static volatile int hit_back = 0;

static void Hit(int);

/******FUNCTIONS******/
static void Hit(int signum)
{
	assert(NULL != signum);
	hit_back = 1;
}

int main ()
{
	pid_t pid = 0;
	action_handler_t child = {0};
	int signum = 0;
	pid_t oponent_id = 0;
	char str[10] = {0};
	size_t rally = 0;

	child.sa_handler = Hit;

	if(0 > sigaction(SIGUSR2, &child, NULL));
	{
		perror("Sigaction error");
		return 1;
	}

	signum = SIGUSR1;
	hit_back = 1;
	oponent_id = getppid();
	strcpy(str, "|o    |");

	while(1)
	{
		sleep(10);
		if(1 == hit_back)
		{
			printf("%s\n", str);
			hit_back = 0;
			if(0 > kill(oponent_id, signum))
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
				if(0 > kill(oponent_id, SIGQUIT))
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
