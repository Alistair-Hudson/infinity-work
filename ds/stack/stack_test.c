#include <stdio.h>
#include "stack.c"

int main()
{	
	size_t pass = 0;

	void *ptr = StackCreate(80);

	if(80 == StackCapacity(ptr))
	{
		++pass;
	}
	else
	{
		printf("Capacity failed\n");
	}
	if(StackIsEmpty(ptr))
	{
		++pass;
	}
	else
	{
		printf("IsEmpty failed\n");
	}
	if(0 == StackSize(ptr))
	{
		++pass;
	}
	else
	{
		printf("Size failed\n");
	}
	StackPush(ptr, (void*)88);
	StackPush(ptr, (void*)666);
	StackPush(ptr, (void*)13);
	if(3 == StackSize(ptr))
	{
		++pass;
	}
	else
	{
		printf("Push failed\n");
	}
	if(13 == *(size_t*)StackPeek(ptr))
	{
		++pass;
	}
	else
	{
		printf("Peek failed\n");
	}
	StackPop(ptr);
	if(2 == StackSize(ptr))
	{
		++pass;
	}
	else
	{
		printf("Pop failed\n");
	}

	if(6 == pass)
	{
		printf("Interal tests passed please check valgrind to confirm destroy\n");
	}
	StackDestroy(ptr);
	
	return 0;
}
