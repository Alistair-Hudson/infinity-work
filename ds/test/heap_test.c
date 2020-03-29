#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define ALL_PASS (3)

int CmpInts(void *lhs, void* rhs)
{
	return *(int*)lhs > *(int*)rhs;
}

int Search(void *data, void *key)
{
	return !(*(int*)data == *(int*)key);
}

int Stage1Test()
{
	heap_t *heap = NULL;

	printf("\n\nStage 1 test\n");

	heap = HeapCreate(CmpInts);
	if (NULL == heap)
	{
		printf("Create faile\n");
		return 0;
	}

	if (!HeapIsEmpty(heap))
	{
		printf("Is Empty failed\n");
		return 0;
	}

	if (0 != HeapSize(heap))
	{
		printf("Size failed\n");
	}
		

	HeapDestroy(heap);
	
	printf("passed\n");
	return 1;
}

int InsertTest()
{
	heap_t *heap = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("\n\nInsert test\n");

	heap = HeapCreate(CmpInts);

	HeapPush(heap, &array[5]);

	if (HeapIsEmpty(heap))
	{
		printf("Insert first failed\n");
		HeapDestroy(heap);
		return 0;
	}	
	if (1 != HeapSize(heap))
	{
		printf("Size of 1 failed\n");
		HeapDestroy(heap);
		return 0;
	}

	HeapPush(heap, &array[4]);
	HeapPush(heap, &array[7]);
	HeapPush(heap, &array[5]);
	HeapPush(heap, &array[2]);
	HeapPush(heap, &array[6]);
	HeapPush(heap, &array[3]);
	HeapPush(heap, &array[5]);
	HeapPush(heap, &array[9]);	
	HeapPush(heap, &array[2]);
	if (10 != HeapSize(heap))
	{
		printf("Insert second failed\n");
		HeapDestroy(heap);
		return 0;
	}
	if (2 != *(int*)HeapPeek(heap))
	{
		printf("Peek failed\n");
		printf("%d", *(int*)HeapPeek(heap));
		HeapDestroy(heap);
		return 0;		
	}
	
	HeapDestroy(heap);

	printf("passed\n");
	return 1;
}

int RemoveTest()
{
	heap_t *heap = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t size = 0;
	printf("\n\nRemove test\n");

	heap = HeapCreate(CmpInts);

	HeapPush(heap, &array[5]);
	HeapPush(heap, &array[4]);
	HeapPush(heap, &array[7]);
	HeapPush(heap, &array[5]);
	HeapPush(heap, &array[2]);
	HeapPush(heap, &array[6]);
	HeapPush(heap, &array[3]);
	HeapPush(heap, &array[5]);
	HeapPush(heap, &array[9]);	
	HeapPush(heap, &array[2]);

	size = HeapSize(heap);

	while (!HeapIsEmpty(heap))
	{
		printf("next = %d\n", *(int*)HeapPeek(heap));
		HeapPop(heap);
		--size;
		if (size != HeapSize(heap))
		{
			printf("Pop failed\n");
			HeapDestroy(heap);
			return 0;
		}
	}

/*	HeapRemove(heap, Search, &array[6]);
	if (7 != HeapSize(heap))
	{
		printf("Remove failed\n");
		HeapDestroy(heap);
		return 0;
	}
*/	
	HeapDestroy(heap);

	printf("passed\n");
	return 1;

}

int main()
{
	
	size_t pass = 0;

	pass += Stage1Test();
	pass += InsertTest();
	pass += RemoveTest();
		
	if (ALL_PASS == pass)
	{
		printf("\n\n\nALL PASSED\n\n\n");
	}
	return 0;
}

