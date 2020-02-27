#include <stdio.h>
#include <stdlib.h>

#include "fsa.h"

int main()
{
	size_t alloc_size = 0;
	void *buff = NULL;
	size_t num_blocks = 2;
	size_t size_blocks = 8;
	fsa_t *alloc = NULL;
	void *ptr1 = NULL;
	void *ptr2 = NULL;
	void *ptr3 = NULL;
	void *ptr4 = NULL;

	alloc_size = FSASuggestSize(num_blocks, size_blocks);
	if (alloc_size != 40)
	{
		printf("SuggestedSize failed\n");
	}

	buff = malloc(alloc_size);

	alloc = FSAInit(buff, alloc_size, size_blocks);

	if (num_blocks != FSANumOfAvailableBlocks(alloc))
	{
		printf("NumOfAvailbleBlocks failed\n");
	}

	ptr1 = FSAAlloc(alloc);
	ptr2 = FSAAlloc(alloc);
	ptr3 = FSAAlloc(alloc);
	printf("alloc = %u, \nptr1 = %u,\n ptr2 = %u,\n ptr3 = %u\n ptr4 = %u\n",
			alloc, ptr1, ptr2, ptr3, ptr4);
	FSAFree(ptr2);
	
	ptr4 = FSAAlloc(alloc);
	ptr2 = FSAAlloc(alloc);
	
	printf("alloc = %u, \nptr1 = %u,\n ptr2 = %u,\n ptr3 = %u\n ptr4 = %u\n",
			alloc, ptr1, ptr2, ptr3, ptr4);

	if (0 != FSANumOfAvailableBlocks(alloc))
	{
		printf("NumOfAvailbleBlocks failed\n");
	}

	free(buff);	

	return 0;
}
