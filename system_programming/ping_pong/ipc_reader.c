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
#include <sys/shm.h>

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES******/

/*****FUNCTIONS******/

/******FUNCTIONS******/
int main()
{
    key_t key;
    int shmid = 0;
    char* str;
    
    key = ftok("shmfile",65); 
    shmid = shmget(key,1024,0666|IPC_CREAT); 
    str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Message: %s", str); 
     
    shmdt(str); 
  
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0; 
}
