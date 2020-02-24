#include <stdio.h>
#include <stdlib.h>

#include "scheduler.c"

#define ALL_PASS		(5)

int Counter(void *count)
{
	--*(int*)count;
	return (count > 0);
}

int RunTestTask1(void *count)
{
	printf("         0<         \n");
	printf("          0<        \n");
	printf("        >0          \n");
	printf("____________________\n");
	++*(int*)count;
	return (*(int*)count != 10);
}

int RunTestTask2(void *count)
{
	printf("            0<      \n");
	printf("   >0               \n");
	printf("                >0  \n");
	printf("____________________\n");
	++*(int*)count;
	return (*(int*)count != 10);
}

int RunTestTask3(void *count)
{
	printf("   >0              \n");
	printf("          0<       \n");
	printf("     >0            \n");
	printf("___________________\n");;
	++*(int*)count;
	return (*(int*)count != 10);
}

int Stage1Test()
{
	sched_t *sched_ptr = 0;
	
	sched_ptr = SchedCreate();

	if (!SchedIsEmpty(sched_ptr))
	{
		printf("IsEmpty failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	if(0 != SchedSize(sched_ptr))
	{
		printf("Size failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	SchedDestroy(sched_ptr);
	return 1;
}

int AddTest()
{
	sched_t *sched_ptr = 0;
	size_t count = 10;
	size_t to_add = 10;
	
	sched_ptr = SchedCreate();

	while(0 < to_add)
	{
		SchedAdd(sched_ptr, Counter, &count, 2, time(NULL));
		--to_add;
	}

	if (SchedIsEmpty(sched_ptr))
	{
		printf("Add failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	if(10 != SchedSize(sched_ptr))
	{
		printf("Add failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	SchedDestroy(sched_ptr);

	return 1;
}

int Stage3Test()
{
	sched_t *sched_ptr = 0;
	ilrd_uid_t uid = {0,0,0};
	size_t count = 10;
	size_t to_add = 10;
	
	
	sched_ptr = SchedCreate();

	while(0 < to_add)
	{
		uid = SchedAdd(sched_ptr, Counter, &count, 2, time(NULL));
		--to_add;
	}

	SchedRemove(sched_ptr, uid);

	if(9 != SchedSize(sched_ptr))
	{
		printf("Remove failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	SchedClear(sched_ptr);
	if (!SchedIsEmpty(sched_ptr))
	{
		printf("Clear failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}
	
	SchedDestroy(sched_ptr);
	return 1;
}

int RunTest()
{
	sched_t *sched_ptr = 0;
	size_t count1 = 0;
	size_t count2 = 0;
	size_t count3 = 0;

	sched_ptr = SchedCreate();
	
	SchedAdd(sched_ptr, RunTestTask1, &count1, 2, time(NULL));
	SchedAdd(sched_ptr, RunTestTask2, &count2, 3, time(NULL));
	SchedAdd(sched_ptr, RunTestTask3, &count3, 4, time(NULL));

	SchedRun(sched_ptr);

	if (!SchedIsEmpty(sched_ptr))
	{
		printf("Run failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	SchedDestroy(sched_ptr);
	return 1;
}

int StopTest()
{
	sched_t *sched_ptr = 0;
	size_t count1 = 0;
	size_t count2 = 0;
	size_t count3 = 0;

	sched_ptr = SchedCreate();
	
	SchedAdd(sched_ptr, RunTestTask1, &count1, 2, time(NULL));
	SchedAdd(sched_ptr, RunTestTask2, &count2, 3, time(NULL));
	SchedAdd(sched_ptr, RunTestTask3, &count3, 4, time(NULL));
	SchedAdd(sched_ptr, SchedStop, sched_ptr, 0, time(NULL)+10);

	SchedRun(sched_ptr);

	if (SchedIsEmpty(sched_ptr))
	{
		printf("Stop failed\n");
		SchedDestroy(sched_ptr);
		return 0;
	}

	SchedDestroy(sched_ptr);
	return 1;

	
}

int main ()
{
	size_t pass = 0;

	pass += Stage1Test();
	pass += AddTest();
	pass += Stage3Test();
	pass += RunTest();
	pass += StopTest();

	if(ALL_PASS == pass)
	{
		printf("\n\n\nALL PASS\n\n\n");
	}

	return 0;
}
