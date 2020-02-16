#include <stdio.h>
#include "cbuffer.c"

int Stage1Tests()
{
	cbuff_t *cbuff_ptr = CBuffCreate(20);
	
	if(!CBuffIsEmpty(cbuff_ptr))
	{
		printf("Is empty failed");
		return 0;
	}
	
	if(0 != CBuffCapacity(cbuff_ptr))
	{
		printf("Capacity failed");
		return 0;
	}

	CBuffDestroy(cbuff_ptr);
	return 1;
}

int main()
{
	int pass = 0;	
	
	pass += Stage1Tests();

	if(ALL_PASSED == pass)
	{
		printf("\n");
		printf("\n");
		printf("ALL PASSED\n");
		printf("\n");
		printf("\n");
	}

	return 0;
}
