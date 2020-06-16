/******************************************************************************
 *	Title:		IPC Ping
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

/******FUNCTIONS******/
int main()
{
    int fd;
    size_t rally = 0;
    char* fifo = "./fifo";
    char msg_buffer[MSGSIZE];
    
    mkfifo(fifo, 0666);
    while (10 >= rally)
    {
        sleep(1);
        fd = open(fifo, O_WRONLY);
        write(fd, ping, MSGSIZE);
        close(fd);
        
        fd = open(fifo, O_RDONLY);
        read(fd, msg_buffer, MSGSIZE);
        prinf("%s\n", msg_buffer);
        close(fd);
        
        ++rally;
    }
	return 0;
}



