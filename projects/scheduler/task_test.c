#include <stdio.h>
#include <stdlib.h>

#include "task.c"

#define ALL_PASS		(3)


int Counter(void *count)
{
	return --*(int*)count;
}

int Stage1Test()
{
	int count = 0;
	size_t freq = 3;
	time_t start = 0;

	task_t *task_ptr = TaskCreate(*Counter, &count, freq, start);

	TaskDestroy(task_ptr);

	return 1;
}

int Stage2Test()
{
	int count = 0;
	size_t freq = 3;
	time_t start = 0;

	task_t *task_ptr = TaskCreate(*Counter, &count, freq, start);
	
	if (0 != TaskGetSchdTime(task_ptr))
	{
		printf("GetSchdTime failed\n");
		TaskDestroy(task_ptr);
		return 0;
	}

	if (UIDIsSame(bad_uid, TaskGetUID(task_ptr)))
	{
		printf("GetUID failed\n");
		TaskDestroy(task_ptr);
		return 0;
	}
	TaskDestroy(task_ptr);

	return 1;
}

int Stage3Test()
{
	int count = 100;
	size_t freq = 3;
	time_t start = 0;

	task_t *task_ptr = TaskCreate(*Counter, &count, freq, start);
	while (0 < count)
	{
		count = TaskExecute(task_ptr);

		if (0 != TaskGetSchdTime(task_ptr) % freq)
		{
			printf("Reschd or Execution failed\n");
			TaskDestroy(task_ptr);
			return 0;
		}
		TaskReschd(task_ptr);
	}
	TaskDestroy(task_ptr);

	return 1;
}

int main()
{
	size_t pass = 0;
	
	pass += Stage1Test();
	pass += Stage2Test();
	pass += Stage3Test();

	if(ALL_PASS == pass)
	{
		printf("\n\n\nALL PASS\n\n\n");
	}

	return 0;
}
