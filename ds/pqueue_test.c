#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pqueue.h"

#define MAX_PASS	(5)

int IntComp(void *x, void *y)
{
	return (*(int*)x - *(int*)y);
}

int Match(void *x, void *y)
{
	return !(*(int*)x == *(int*)y);
}

static int Stage1Testing()
{
	pqueue_t *que_ptr = 0;
	
	que_ptr = PQCreate(IntComp);

	if(!PQIsEmpty(que_ptr))
	{
		printf("IsEmpty Failed\n");
		return 0;
	}
	if(0 != PQSize(que_ptr))
	{
			printf("Size Failed\n");
			return 0;
	}

	PQDestroy(que_ptr);	
	return 1;
}

static int InsertTest()
{
	pqueue_t *que_ptr = 0;
	int num_of_inserts = 0;

	que_ptr = PQCreate(IntComp);

	while(100 > num_of_inserts)
	{

		PQEnqueue(que_ptr, &num_of_inserts);
		++num_of_inserts;
	}

	if(PQIsEmpty(que_ptr))
	{
		printf("Insert Failed\n");
		return 0;
	}

	if(100 != PQSize(que_ptr))
	{
			printf("Insert Failed\n");
			return 0;
	}
	
	PQDestroy(que_ptr);	
	return 1;
}

static int RemoveTest()
{
	pqueue_t *que_ptr = 0;
	int num_of_inserts = 100;

	que_ptr = PQCreate(IntComp);

	while(0 <= num_of_inserts)
	{
		PQEnqueue(que_ptr, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		PQDequeue(que_ptr);
		++num_of_inserts;
	}

	if(PQIsEmpty(que_ptr))
	{
		printf("Remove Failed\n");
		return 0;
	}
	if(49 != PQSize(que_ptr))
	{
			printf("Remove Failed\n");
			return 0;
	}

	PQClear(que_ptr);
	if(!PQIsEmpty(que_ptr))
	{
		printf("Clear Failed\n");
		return 0;
	}

	PQDestroy(que_ptr);	
	return 1;
}

static int PeekTest()
{
	pqueue_t *que_ptr = 0;
	int int_array[50];
	int index = 0;

	que_ptr = PQCreate(IntComp);

	while(50 > index)
	{
		int_array[index] = index;
		++index;
	}

	index = 0;
	while(50 >index)
	{
		PQEnqueue(que_ptr, &int_array[index]);
		++index;
	}
	index = 0;
	while(50 >index)
	{
		PQEnqueue(que_ptr, &int_array[index]);
		++index;
	}
	index = 0;
	while(100 > index)
	{
		if(int_array[index/2] != *(int*)PQPeek(que_ptr))
		{
			printf("Peek Failed at index: %d, value in list %d\n",
									index, *(int*)PQPeek(que_ptr));
			return 0;
		}
		PQDequeue(que_ptr);
		++index;
	}

	PQDestroy(que_ptr);
	return 1;
}

int EraseTest()
{
	pqueue_t *que_ptr = 0;
	int int_array[50];
	int index = 0;
	int erase = 26;

	que_ptr = PQCreate(IntComp);

	while(50 > index)
	{
		int_array[index] = index;
		++index;
	}

	index = 0;
	while(50 >index)
	{
		PQEnqueue(que_ptr, &int_array[index]);
		++index;
	}
	PQErase(que_ptr, Match, &erase);
	
	index = 0;
	

	while(erase > index)
	{
		if(int_array[index] != *(int*)PQPeek(que_ptr))
		{
			printf("Peek Failed at index: %d, value in list %d\n",
									index, *(int*)PQPeek(que_ptr));
			return 0;
		}

		PQDequeue(que_ptr);
		++index;
	}

	if(int_array[index] == *(int*)PQPeek(que_ptr))
	{
		printf("Peek Failed at index: %d, value in list %d\n",
								index, *(int*)PQPeek(que_ptr));
		return 0;
	}

	PQDestroy(que_ptr);
	return 1;
}
int main()
{
	size_t pass = 0;
	
	pass += Stage1Testing();
	pass += InsertTest();
	pass += RemoveTest();
	pass += PeekTest();
	pass += EraseTest();
	
	if(MAX_PASS == pass)
	{
		printf("\n\n\nAll passed\n\n\n");
	}
	
	return 0;
}
