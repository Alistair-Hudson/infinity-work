
#ifndef __TASK_H__
#define __TASK_H__

/*******************************************************************************
                                 *  ALI TASK API
                                 * version 24.02.2020.0
 ******************************************************************************/

#include <stddef.h>	/* size_t */    
#include <time.h>	/*time_t*/
#include "uid.h"

typedef struct task task_t;

/*
*Action function
*Input : void pointer
*Retun : remianing number of exectuions upon success, "-1" upon failure.
*/
typedef int (* task_act_t)(void *param);

/*
* Input:  pointer to action function parameter of siad function the frequency at
*which the task should run and the intial start time of the task.
* Process: allocate memory for task
* Return: pointer to task if successful, NULL if failed
*/
task_t *TaskCreate(task_act_t action, void *param, size_t freq, 
															time_t start_time);

/*
* Input:  pointer to task
* Process: destroy the whole task (free memory)
* Return: none
*/
void TaskDestroy(task_t *task);

/*
* Input:  task
* Return: time that task is to be executed.
*/
time_t TaskGetSchdTime(task_t *task);

/*
* Input:  task
* Return: the UID of the task.
*/
ilrd_uid_t TaskGetUID(task_t *task);

/*
* Input:  task
* Process: adds the the frequency time to the current time to reschdule the
* task
* Return: "0" upon success, all other values denote failure.
*/
int TaskReschd(task_t *task);

/*
 * Input: pointer to a task
 * Process: The function executes the task
 * Return: remianing number of exectuions upon success, "-1" upon failure.
 */
int  TaskExecute(task_t *task);


/*
 * Input: pointer to task
 * Return: the task execution time
 */
time_t TaskGetExecTime(task_t *task);

#endif /* __TASK_H__ */


