#include <stdlib.h>
#include <assert.h>		/* assert */
#include <unistd.h>		/* sleep */

#include "scheduler.h"
#include "pqueue.c"
#include "task.c"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))\

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
struct sched
{
	pqueue_t *pqueue;
	task_t *current_task;
	int run;
};

static int TimeExecCmp(void *task, void *task_key);
static int UIDFinder(void *task_ptr, void *uid_key);

/******FUNCTIONS******/
sched_t *SchedCreate()
{
	sched_t *new_sched = malloc(sizeof(struct sched));

	if (NULL == new_sched)
	{
		return 0;
	}

	new_sched->current_task = NULL;
	new_sched->pqueue = PQCreate(TimeExecCmp);
	new_sched->run = 1;
	
	if(NULL == new_sched->pqueue)
	{
		free(new_sched);
		return 0;
	}

	return new_sched;
}

static int TimeExecCmp(void *task, void *task_key)
{
	task_t *task1 = 0;
	task_t *task2 = 0;

	ASSERT_NOT_NULL(task);
	ASSERT_NOT_NULL(task_key);

	task1 = task;
	task2 = task_key;

	return task1->exec_time - task2->exec_time;
}

void SchedDestroy(sched_t *schedule)
{
	size_t nodes_to_destroy = 0;
	task_t *task = 0;

	ASSERT_NOT_NULL(schedule);
	
	nodes_to_destroy = SchedSize(schedule);
	
	while (0 != nodes_to_destroy)
	{
		task = PQPeek(schedule->pqueue);
		PQDequeue(schedule->pqueue);
		TaskDestroy(task);
		--nodes_to_destroy;
	}
	
	PQDestroy(schedule->pqueue);
	free(schedule);
	task = NULL;
	schedule = NULL;
}

size_t SchedSize(const sched_t *schedule)
{
	return PQSize(schedule->pqueue);
}

int SchedIsEmpty(const sched_t *schedule)
{
	return PQIsEmpty(schedule->pqueue);
}

ilrd_uid_t SchedAdd(sched_t *schedule, int (*action)(void*), void *param, 
												size_t freq, time_t exec_time)
{
	task_t *new_task = 0;
	
	ASSERT_NOT_NULL(schedule);
	ASSERT_NOT_NULL(action);
	
	new_task = TaskCreate(action, param, freq, exec_time);

	if(UIDIsSame(TaskGetUID(new_task), bad_uid))
	{
		free(new_task);
		new_task = NULL;
		return bad_uid;
	}

	if(PQEnqueue(schedule->pqueue, new_task))
	{
		free(new_task);
		new_task = NULL;
		return bad_uid;
	}

	return TaskGetUID(new_task);
}

void SchedClear(sched_t *schedule)
{
	size_t nodes_to_destroy = 0;
	task_t *task = 0;

	ASSERT_NOT_NULL(schedule);
	
	nodes_to_destroy = SchedSize(schedule);
	
	while (0 != nodes_to_destroy)
	{
		task = PQPeek(schedule->pqueue);
		PQDequeue(schedule->pqueue);
		TaskDestroy(task);
		--nodes_to_destroy;
	}
}

void SchedRemove(sched_t *schedule, ilrd_uid_t uid)
{
	task_t *task = 0;

	ASSERT_NOT_NULL(schedule);

	task = (task_t*)PQErase(schedule->pqueue, UIDFinder, &uid);
	free(task);
	task = NULL;
}

static int UIDFinder(void *task_ptr, void *uid_key)
{
	task_t *task = task_ptr;
	return (UIDIsSame(task->uid, *(ilrd_uid_t*)uid_key));
}

int SchedRun(sched_t *schedule)
{
	int resched = 0;
	unsigned int sleep_time = 0;

	ASSERT_NOT_NULL(schedule);

	while(!SchedIsEmpty(schedule) && schedule->run)
	{
		schedule->current_task = PQPeek(schedule->pqueue);
		sleep_time = TaskGetSchdTime(schedule->current_task) - time(NULL);
		sleep(sleep_time);
		PQDequeue(schedule->pqueue);
		resched = TaskExecute(schedule->current_task);
		if(resched)
		{
			TaskReschd(schedule->current_task);
			PQEnqueue(schedule->pqueue, schedule->current_task);
		}
		else
		{
			free(schedule->current_task);
		}
	}
	return 0;
}

int SchedStop(void *schedule)
{
	sched_t *sched = schedule;
	sched->run = 0;
	return 0;
}











