/*
 * =============================================================================
 *
 *       Filename:  watchdog.h
 *
 *    Description:  Watchdog Library Header File
 *
 *        Version:  1.0
 *        Created:  10/05/2020
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =============================================================================
 */


#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__


/* #####   HEADER FILE INCLUDES   ########################################### */
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <unistd.h>		/* sleep */

#include "scheduler.h"
#include "pqueue.h"
#include "task.h"

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

typedef struct watchdog watchdog_t;

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  WatchdogStart
 *  Description:  Runs a watchdog to monitor a process
 *     Input(s):  program's namme and any arguments required for the main 
				  function
 *       Return:  NULL if failed, pointer to watchdog if success
 * =============================================================================
 */
watchdog_t *WatchdogStart(char *program_name, char *arguments[]);

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  WatchdogStop
 *  Description:  Stops a watchdog to monitor a process
 *     Input(s):  watchdog to stop.
 *       Return:  
 * =============================================================================
 */
void WatchdogStop(watchdog_t *watchdog_instance);

#endif   /* ----- #ifndef __SCHEDULER_H__  ----- */

