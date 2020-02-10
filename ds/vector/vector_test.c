#include <stdio.h>
#include "vector.c"

#define NEED_TO_PASS (10)
int main()
{	
	size_t pass = 0;

	void *ptr = VectorCreate(80);
	
	if(80 == VectorCapacity(ptr))
	{
		++pass;
		printf("Cap\n");
	}
	if(VectorIsEmpty(ptr))
	{
		++pass;
		printf("Emp\n");
	}
	if(0 == VectorSize(ptr))
	{
		++pass;
		printf("Size\n");
	}

	VectorPushBack(ptr, (void*)88);
	VectorPushBack(ptr, (void*)666);
	VectorPushBack(ptr, (void*)13);
	if(3 == VectorSize(ptr))
	{
		++pass;
		printf("Push\n");
	}
	VectorPopBack(ptr);
	if(2 == VectorSize(ptr))
	{
		++pass;
		printf("Pop\n");
	}
	if(666 == *(size_t*)VectorGetValue(ptr, 1))
	{
		++pass;
		printf("Get\n");
	}
	VectorSetElement(ptr, 1, (void*)101);
	if(101 == *(size_t*)VectorGetValue(ptr, 1))
	{
		++pass;
		printf("Set\n");
	}
	VectorShrinkToFit(ptr);
	if(2 == VectorCapacity(ptr))
	{
		++pass;
		printf("Shrink\n");
	}
	if(101 == *(size_t*)VectorGetValue(ptr, 1))
	{
		++pass;
	}
	VectorPushBack(ptr, (void*)666);
	VectorPushBack(ptr, (void*)13);
	if(6 == VectorCapacity(ptr))
	{
		++pass;
		printf("Reserve\n");
	}


	if(NEED_TO_PASS == pass)
	{
		printf("All Passed\n");
	}
	VectorDestroy(ptr);
	
	return 0;
}
