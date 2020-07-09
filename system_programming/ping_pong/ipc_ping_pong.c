/******************************************************************************
 *	Title:		IPC Ping-Pong
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	16.06.2020.0
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
#define MSGSIZE                 (4)

/******TYPEDEFS, GLOBAL VARIABLES******/
static volatile int hit_back = 0;
static char* ping = "ping";
static char* pong = "pong";

/*****FUNCTIONS******/
void Hit(int);
int PingPong1(void);

/******FUNCTIONS******/
int main()
{
	int status = 0;

	status = PingPong1();

	return status;
}

int PingPong1(void)
{
	pid_t pid = 0;
	pid_t id = 0;
	size_t rally = 0;
	int p[2];
	char msg_buffer[MSGSIZE];
	
	if (pipe(p)<0)
	{
	    perror("Pipe error");
	    return 1;
	}

	pid = fork();
	
	if (0 > pid)
	{
		perror("Fork error");
		return 1;
	}

	while (1)
	{
		sleep(1);
		if (0 == pid)
    	{
    		//hit_back = 1;
    		write(p[1], ping, MSGSIZE);
    	}
    	else
    	{
    		write(p[1], pong, MSGSIZE);
    	}
    	
		read(p[0], msg_buffer, MSGSIZE);
		printf("%s\n", msg_buffer);
		++rally;
		if (10 <= rally)
		{
			return 0;				
		}
	}

	return 1;
}



