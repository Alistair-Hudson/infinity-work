#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define ALL_PASS (3)

int CmpInts(const void *lhs, const void* rhs)
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
/*	avl_t *btree = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	size_t size = 0;
	int i = 0;

	printf("\n\nRemove test\n");

	btree = AVLCreate(CmpInts);

	for (i = 0; i <= 14; ++i)
	{
		AVLInsert(btree, &array[i]);
	}
	size = AVLSize(btree);

	AVLRemove(btree, &array[2]);	
	--size;
	if (size != AVLSize(btree))
	{
		printf("Remove leaf failed\n");
		printf("size = %lu\n", AVLSize(btree));
		AVLDestroy(btree);
		return 0;
	}
	
	AVLRemove(btree, &array[5]);
	--size;	
	if (size != AVLSize(btree))
	{
		printf("Remove node with two leaves failed\n");
		AVLDestroy(btree);
		return 0;
	}

	AVLRemove(btree, &array[0]);
	--size;
	if (size != AVLSize(btree))
	{
		printf("Remove End failed\n");
		AVLDestroy(btree);
		return 0;
	}
	
	AVLRemove(btree, &array[6]);
	--size;
	if (size != AVLSize(btree))
	{
		printf("Remove subtree failed\n");
		AVLDestroy(btree);
		return 0;
	}

	AVLRemove(btree, &array[7]);
	--size;
	if (size != AVLSize(btree))
	{
		printf("Remove root failed\n");
		AVLDestroy(btree);
		return 0;
	}

	printf("passed\n");

	AVLDestroy(btree);

*/	return 1;
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

