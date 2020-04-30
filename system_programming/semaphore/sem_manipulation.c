/******************************************************************************
 *	Title:		Semaphore Manipulation
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	30.04.2020.0
 ******************************************************************************/
#include <stdlib.h>		/*  */
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */
#include <stdio.h>		/* printf */
#include <errno.h>		/* perror */
#include <pthread.h>	/* pthread functions */
#include <time.h>		/* time */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != (ptr)))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/


/******FUNCTIONS******/
