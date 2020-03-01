#include <stdio.h>
#include <stdlib.h>

#include "vsa.h"

int main()
{
	size_t alloc_size = 110;
	void *buff = NULL;
	vsa_t *alloc = NULL;
	void *ptr1 = NULL;
	void *ptr2 = NULL;
	void *ptr3 = NULL;
	void *ptr4 = NULL;

	buff = malloc(alloc_size);

	alloc = VSAInit(buff, alloc_size);

	ptr1 = VSAAlloc(alloc, 10);
	ptr2 = VSAAlloc(alloc, 20);
	ptr3 = VSAAlloc(alloc, 16);
	printf("alloc = %p, \nptr1 = %p,\n ptr2 = %p,\n ptr3 = %p\n ptr4 = %p\n",
			alloc, ptr1, ptr2, ptr3, ptr4);
	VSAFree(ptr2);
	VSAFree(ptr1);

	printf("largest chunk = %lu\n", VSABiggestChunk(alloc));

	ptr4 = VSAAlloc(alloc, 20);
	ptr2 = VSAAlloc(alloc, 10);
	ptr1 = VSAAlloc(alloc, 20);
	printf("alloc = %p, \nptr1 = %p,\n ptr2 = %p,\n ptr3 = %p\n ptr4 = %p\n",
			alloc, ptr1, ptr2, ptr3, ptr4);

	free(buff);

	return 0;
}
