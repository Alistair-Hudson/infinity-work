#include <stdio.h>
#include "vector.c"

#define NEED_TO_PASS (7)
int main()
{	
	size_t pass = 0;

	void *ptr = VectorCreate(80);
	
	if(80 == VectorCapacity(ptr))
	{
		++pass;
	}
	if(VectorIsEmpty(ptr))
	{
		++pass;
	}
	if(0 == VectorSize(ptr))
	{
		++pass;
	}
	VectorPushBack(ptr, (void*)88);
	VectorPushBack(ptr, (void*)666);
	VectorPushBack(ptr, (void*)13);
	if(3 == VectorSize(ptr))
	{
		++pass;
	}
	VectorPopBack(ptr);
	if(2 == VectorSize(ptr))
	{
		++pass;
	}
	if(666 == *(size_t*)VectorGetValue(ptr, 1))
	{
		++pass;
	}
	VectorSetElement(ptr, 1, (void*)101);
	if(101 == *(size_t*)VectorGetValue(ptr, 1))
	{
		++pass;
	}

	if(NEED_TO_PASS == pass)
	{
		printf("all passed\n");
	}
	VectorDestroy(ptr);
	
	return 0;
}
