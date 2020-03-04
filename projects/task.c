#include <stdio.h>
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "uid.c"		/* UID functions */
#include "task.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)		(assert(NULL != ptr))
/******TYPEDEFS, INTERNAL GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
struct task
{
	ilrd_uid_t uid;
	task_act_t act;
	size_t frequency;
	time_t exec_time;
	void* parameter;
};

/******FUNCTIONS******/
task_t *TaskCreate(task_act_t action, void *param, size_t freq,
															 time_t start_time)
{
	task_t *new_task = malloc(sizeof(struct task));
	
	if(NULL == new_task)
	{
		return 0;
	}
	
	new_task->uid = UIDCreate();
	new_task->act = action;
	new_task->frequency = freq;
	new_task->exec_time = start_time;
	new_task->parameter = param;

	return new_task;
}

void TaskDestroy(task_t *task)
{
	ASSERT_NOT_NULL(task);
	free(task);
	task = NULL;
}

time_t TaskGetSchdTime(task_t *task)
{
	ASSERT_NOT_NULL(task);
	return task->exec_time;
}

ilrd_uid_t TaskGetUID(task_t *task)
{
	ASSERT_NOT_NULL(task);
	return task->uid;
}

int TaskExecute(task_t *task)
{
	ASSERT_NOT_NULL(task);

	return task->act(task->parameter);
}

int TaskReschd(task_t *task)
{
	ASSERT_NOT_NULL(task);
	
	task->exec_time += task->frequency;
	
	return 0;
}




