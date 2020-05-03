/******************************************************************************
 *	Title:		Semaphore Manipulation
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	30.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/* atoi */
#include <assert.h>		/* assert */
#include <stdio.h>		/* printf, fgets*/
#include <errno.h>		/* perror */
#include <pthread.h>	/* pthread functions */
#include <time.h>		/* time */
#include <sys/types.h>	/* Sys V functions */
#include <sys/sem.h>	/* Sys V functions */
#include <string.h>		/* strstr */
#include <ctype.h>		/* isdigit */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != (ptr)))
#define MAX_CHAR_LIM			(100)
/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/
int main(int argc, char** argv)
{
	int semid;
	int status = 0;
	int semaphore_val = 0;
	const char undo_command [10] = "[undo]";
	key_t key;
	struct sembuf operations[1];
	struct sembuf sem_value[1];

	if (0 ==  argc)
	{
		printf("No name for semaphore");
		return 0;
	}

	key = atoi(argv[1]);

	if (0 > (semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600)))
	{
		perror("Failed semget");
		return 1;
	}

	while(!status)
	{
		int user_number = 0;
		char user_command[MAX_CHAR_LIM] = {0};
		char* user_action = NULL;
		int operation_mod = 1;

		fgets(user_command, MAX_CHAR_LIM, stdin);
		user_action = user_command;

		if ('X' == *user_command)
		{
			return 0;
		}
		else if ('D' == *user_command || 'U' == *user_command)
		{
			operation_mod = ('D' == *user_command ? -1 : 1 );	
			user_action +=2;
			if (isdigit(*user_action))
			{
				user_number = strtod(user_action, &user_action) * operation_mod;
				
				semaphore_val = semctl(semid, 0, GETVAL, sem_value);
				
				if (0 > semaphore_val - user_number)
				{
					user_number = 0;
				}

				operations[0].sem_op = user_number;

				if (strstr(user_action, undo_command))
				{
					operations[0].sem_flg = SEM_UNDO;
				}
				
				if (0 > semop(semid, operations, 1))
				{
					perror("Semop failed");
				}
			}
		}
		else
		{
			printf("Incorrect key\n");			
		}
	}
	return status;
}
