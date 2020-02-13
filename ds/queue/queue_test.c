#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slist.c"
#include "queue.c"

#define MAX_PASS	(5)

static int Stage1Testing()
{
	queue_t *queue_ptr = 0;
	
	queue_ptr = QCreate();

	if(!QIsEmpty(queue_ptr))
	{
		printf("IsEmpty Failed\n");
		return 0;
	}
	if(0 != QCount(queue_ptr))
	{
			printf("Count Failed\n");
			return 0;
	}

	QDestroy(queue_ptr);	
	return 1;
}

static int EnqueueTest()
{
	queue_t *queue_ptr = 0;
	int num_of_inserts = 0;

	queue_ptr = QCreate();

	while(100 > num_of_inserts)
	{
		QEnqueue(queue_ptr, &num_of_inserts);
		++num_of_inserts;
	}
	if(QIsEmpty(queue_ptr))
	{
		printf("Enqueue Failed\n");
		return 0;
	}
	if(100 != QCount(queue_ptr))
	{
		printf("Enqueue Failed\n");
		return 0;
	}

	QDestroy(queue_ptr);	
	return 1;
}

static int DequeueTest()
{
	queue_t *queue_ptr = 0;
	int num_of_inserts = 100;

	queue_ptr = QCreate();

	while(0 <= num_of_inserts)
	{
		QEnqueue(queue_ptr, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		QDequeue(queue_ptr);
		++num_of_inserts;
	}

	if(QIsEmpty(queue_ptr))
	{
		printf("Dequeue Failed\n");
		return 0;
	}
	if(49 != QCount(queue_ptr))
	{
		printf("Dequeue Failed\n");
		return 0;
	}

	QDestroy(queue_ptr);	
	return 1;
}

static int PeekTest()
{
	queue_t *queue_ptr = 0;
	int array_of_ints[100];
	int index = 0;

	queue_ptr = QCreate();

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		QEnqueue(queue_ptr, &array_of_ints[index]);
		++index;
	}
	index = 0;
	while(100 > index)
	{
		if(array_of_ints[index] != *(int*)QPeek(queue_ptr))
		{
			printf("Peek Failed\n");
			return 0;
		}
		QDequeue(queue_ptr);
		++index;
	}

	QDestroy(queue_ptr);
	return 1;
}

int AppendTest()
{
	queue_t *queue_ptr1 = 0;
	queue_t *queue_ptr2 = 0;
	int num_of_inserts = 0;
	size_t combined_size = 0;

	queue_ptr1 = QCreate();
	queue_ptr2 = QCreate();

	while(100 > num_of_inserts)
	{
		QEnqueue(queue_ptr1, &num_of_inserts);
		++num_of_inserts;
	}
	num_of_inserts = 0;
	while(50 > num_of_inserts)
	{
		QEnqueue(queue_ptr2, &num_of_inserts);
		++num_of_inserts;
	}
	
	combined_size = QCount(queue_ptr1) + QCount(queue_ptr2) -1;
	
	QAppend(queue_ptr1, queue_ptr2);
	if((combined_size) != QCount(queue_ptr1))
	{
		printf("Append Failed\n");
		return 0;
	}

	QDestroy(queue_ptr1);	
	return 1;
}
int main()
{
	size_t pass = 0;
	
	pass += Stage1Testing();
	pass += EnqueueTest();
	pass += DequeueTest();
	pass += PeekTest();
	pass += AppendTest();

	if(MAX_PASS == pass)
	{
		printf("\n\n\nAll passed\n\n\n");
	}
	
	return 0;
}
