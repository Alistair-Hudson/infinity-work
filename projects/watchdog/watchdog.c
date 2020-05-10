/******************************************************************************
 *	Title:		Watchdog
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	10/05/2020.0
 ******************************************************************************/

#include <stdlib.h>
#include <assert.h>		/* assert */
#include <unistd.h>		/* sleep */

#include "scheduler.h"
#include "pqueue.h"
#include "task.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))\

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/

