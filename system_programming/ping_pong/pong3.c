/******************************************************************************
 *	Title:		Signal Pong ex3
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

static volatile int hit_back = 0;

static void Hit(int);

/******FUNCTIONS******/
static void Hit(int signum)
{
	(void)signum;
	hit_back = 1;
}

int main (int argc, char *argv[])
{

	action_handler_t pong = {0};
	int signum = 0;
	pid_t oponent_id = 0;
	char str[10];
	size_t rally = 0;

/*	assert(argc == 1);
*/	assert(isdigit(argv[1][0]));

	oponent_id = atoi(argv[1]);
	pong.sa_handler = Hit;

	sigaction(SIGUSR2, &pong, NULL);

	signum = SIGUSR1;
	hit_back = 1;
	strcpy(str, "|    o|");

	while(1)
	{
		sleep(10);
		if(1 == hit_back)
		{
			
			printf("%s\n", str);
			kill(oponent_id, signum);
			hit_back = 0;

			++rally;

			if (10 <= rally)
			{
				kill(oponent_id, SIGQUIT);
				return 0;				
			}
		}
	}
	return 1;
}
