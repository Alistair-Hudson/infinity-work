/******************************************************************************
 *	Title:		IPC Message Reader
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	16.06.2020.0
 ******************************************************************************/
#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* strcpy */
#include <stdio.h>		/* printf */
#include <sys/ipc.h>    /*ftok, shmget, shmat, shmdt */
#include <sys/msg.h>

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MSGSIZE                 (100)

/******TYPEDEFS, GLOBAL VARIABLES******/

/******STRUCTS******/
struct msgbuf
{
    long msg_type;
    char msg[MSGSIZE];
};

/*****FUNCTIONS DECLARATIONS******/

/******FUNCTIONS******/
int main()
{
    key_t key;
    int msgid = 0;
    struct msgbuf message;
    
    key = ftok("msgfile",65); 
    msgid = msgget(key,1024,0666|IPC_CREAT); 
    
    msgrcv(msgid, &message, MSGSIZE, 1, 0);  

    msgctl(msgid, IPC_RMID, NULL); 
  
    return 0; 
}



