/******************************************************************************
 *	Title:		Signal Ping ex3
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel
 *	Version:	27.04.2020.2
 ******************************************************************************/
#define _USE_POSIX199309
#define _POSIX_C_SOURCE	199309L
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

static pid_t oponent_id = 0;

static volatile int hit_back = 0;

static void Hit(int, siginfo_t*, void*);

/******FUNCTIONS******/
static void Hit(int signum, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	assert(NULL != signum);
	assert (NULL != info);
	oponent_id = info->si_pid;
	hit_back = 1;
}

int main ()
{
	action_handler_t ping = {0};
	int signum = 0;
	char str[10] = {0};
	size_t rally = 0;

	ping.sa_sigaction = Hit;
	ping.sa_flags = SA_SIGINFO;

	if(0 > sigaction(SIGUSR1, &ping, NULL))
	{
		perror("Sigaction error");
		return 1;
	}

	signum = SIGUSR2;
	strcpy(str, "|o    |");

	while(1)
	{
		sleep(10);
		if(1 == hit_back)
		{
			printf("%s\n", str);
			hit_back = 0;
			if (0 > kill(oponent_id, signum))
			{
				perror("Signal errror");
				return 1;
			}
	
			++rally;
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
