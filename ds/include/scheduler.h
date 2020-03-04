/*
 * =============================================================================
 *
 *       Filename:  scheduler.h
 *
 *    Description:  Scheduler Library Header File
 *
 *        Version:  1.0
 *        Created:  02/24/20 12:09:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =============================================================================
 */


#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__


/* #####   HEADER FILE INCLUDES   ########################################### */

#include <stddef.h>  /* size_t */
#include <time.h>  /* time_t */

#include "uid.h"  /* ilrd_uid_t */

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

typedef struct sched sched_t;

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedCreate
 *  Description:  Allocates a new schedule.
 *     Input(s):  None.
 *       Return:  Pointer to new schedule on success.  In case of insufficient
 *       		  memory returns NULL.
 *    Important:  The returned schedule should only be accessed using the
 *    			  functions provided by this library.  When the schedule is no
 *    			  longer needed, it should be destroyed.
 * =============================================================================
 */
sched_t *SchedCreate(void);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedDestroy
 *  Description:  Releases memory of the given schedule.
 *     Input(s):  Schedule to destroy.  This must be a schedule which was 
 *     			  received from SchedCreate (this applies to all functions part
 *     			  of this library that receive a sched_t pointer as an input).
 *       Return:  None, this function does not fail.
 * 	  Important:  After calling this function the input schedule cannot be used
 * 	  			  again and its address is invalid.
 * =============================================================================
 */
void SchedDestroy(sched_t *schedule);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedIsEmpty
 *  Description:  Checks if the schedule is empty.
 *     Input(s):  Schedule to check.
 *       Return:  Returns 1 if empty, otherwise returns 0.
 * =============================================================================
 */
int SchedIsEmpty(const sched_t *schedule);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedSize
 *  Description:  Counts the number of tasks in the schedule.
 *     Input(s):  Schedule to get size of.
 *       Return:  The number of tasks in the schedule.
 * =============================================================================
 */
size_t SchedSize(const sched_t *schedule);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedAdd
 *  Description:  Adds a new task to the schedule.
 *     Input(s):  1. Schedule to add to.
 *     			  2. The function it should execute.
 *     			  3. The input that should be passed to the function.
 *     			  4. The frequency, in seconds, at which the function should be
 *     			  	 executed.
 *     			  5. The time, in seconds since the epoch, when the function
 *     			  	 should be executed.
 *       Return:  Returns the UID for the new task on success, otherwise
 *       		  bad_uid (declared in uid.h) is returned.
 *         Note:  The return of the input function should be 1 if it should be
 *         		  rescheduled, 0 if not.
 * =============================================================================
 */
ilrd_uid_t SchedAdd(sched_t *schedule, int (*action)(void*), void *param, 
											size_t freq, time_t exec_time);
                                            
                                          
/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedClear
 *  Description:  Removes all tasks from the schedule.
 *     Input(s):  Schedule to clear.
 *       Return:  None, this does not fail.
 * =============================================================================
 */
void SchedClear(sched_t *schedule);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedRemove
 *  Description:  Remove task from schedule.
 *     Input(s):  1. Schedule to remove from.
 *     			  2. UID of task to remove.
 *       Return:  None, this does not fail.
 * =============================================================================
 */
void SchedRemove(sched_t *schedule, ilrd_uid_t uid);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedStop
 *  Description:  Stops a running schedule.  If the given schedule is not
 *  			  currently running then it does nothing.
 *     Input(s):  Schedule to stop.
 *       Return:  Always returns 0. 
 * =============================================================================
 */
int SchedStop(void *schedule);


/* 
 * ===  FUNCTION  ==============================================================
 *         Name:  SchedRun
 *  Description:  Runs the given schedule until SchedStop is called or until
 *  			  the schedule is empty.
 *     Input(s):  Schedule to run.
 *       Return:  Returns 0 on success.  If an error is encountered while
 *       		  running the schedule, a non-zero value is returned.
 * =============================================================================
 */
int SchedRun(sched_t *schedule);

#endif   /* ----- #ifndef __SCHEDULER_H__  ----- */

