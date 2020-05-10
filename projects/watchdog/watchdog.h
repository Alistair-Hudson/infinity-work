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

#include "scheduler.h"  /* ilrd_uid_t */

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

typedef struct sched sched_t;

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  WatchdogStart
 *  Description:  Runs a watchdog to monitor a process
 *     Input(s):  
 *       Return:  
 * =============================================================================
 */
int WatchdogStart();

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  WatchdogStop
 *  Description:  Stops a watchdog to monitor a process
 *     Input(s):  
 *       Return:  
 * =============================================================================
 */
void WatchdogStop();

#endif   /* ----- #ifndef __SCHEDULER_H__  ----- */

