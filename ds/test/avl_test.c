#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define ALL_PASS (5)

int CmpInts(const void *int1, const void* int2)
{
	return *(int*)int1 < *(int*)int2;
}

int Search(void *data, void *key)
{
	return !(*(int*)data == *(int*)key);
}

int AddTo(void *data, void *added)
{
	*(int*)data += *(int*)added;
	return 0;
}

int Stage1Test()
{
	avl_t *btree = NULL;

	printf("\n\nStage 1 test\n");

	btree = AVLCreate(CmpInts);
	if (NULL == btree)
	{
		printf("Create faile\n");
		return 0;
	}

	if (!AVLIsEmpty(btree))
	{
		printf("Is Empty failed\n");
		return 0;
	}

	if (0 != AVLSize(btree))
	{
		printf("Size failed\n");
	}
		

	AVLDestroy(btree);
	
	printf("passed\n");
	return 1;
}

int InsertTest()
{
	avl_t *btree = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("\n\nInsert test\n");

	btree = AVLCreate(CmpInts);

	AVLInsert(btree, &array[5]);

	if (AVLIsEmpty(btree))
	{
		printf("Insert first failed\n");
		AVLDestroy(btree);
		return 0;
	}	
	if (1 != AVLSize(btree))
	{
		printf("Size of 1 failed\n");
		AVLDestroy(btree);
		return 0;
	}
	if (0 != AVLHeight(btree))
	{
		printf("Height of 1 node failed\n");
		AVLDestroy(btree);
		return 0;		
	}
	
	AVLInsert(btree, &array[2]);
	if (2 != AVLSize(btree))
	{
		printf("Insert left failed\n");
		AVLDestroy(btree);
		return 0;
	}
	if (1 != AVLHeight(btree))
	{
		printf("Height of 2 nodes failed\n");
		AVLDestroy(btree);
		return 0;		
	}
	
	AVLInsert(btree, &array[6]);
	AVLInsert(btree, &array[4]);
	if (4 != AVLSize(btree))
	{
		printf("Insert right failed\n");
		printf("size = %u\n", AVLSize(btree));
		AVLDestroy(btree);
		return 0;
	}
	
	AVLInsert(btree, &array[9]);
	if (5 != AVLSize(btree))
	{
		printf("Insert to end failed\n");
		printf("size = %u\n", AVLSize(btree));
		AVLDestroy(btree);
		return 0;
	}
	AVLDestroy(btree);

	printf("passed\n");
	return 1;
}

int RemoveTest()
{
	avl_t *btree = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	size_t size = 0;

	printf("\n\nRemove test\n");

	btree = AVLCreate(CmpInts);

	AVLInsert(btree, &array[7]);
	AVLInsert(btree, &array[11]);
	AVLInsert(btree, &array[3]);
	AVLInsert(btree, &array[1]);
	AVLInsert(btree, &array[0]);
	AVLInsert(btree, &array[2]);
	AVLInsert(btree, &array[5]);
	AVLInsert(btree, &array[4]);
	AVLInsert(btree, &array[6]);
	AVLInsert(btree, &array[14]);
	AVLInsert(btree, &array[12]);
	AVLInsert(btree, &array[13]);
	AVLInsert(btree, &array[9]);
	AVLInsert(btree, &array[8]);
	AVLInsert(btree, &array[10]);
	
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

	return 1;
}

int FindTest()
{
	avl_t *btree = NULL;
	int find9 = 0;
	int num9 = 9;
	int num5 = 5;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	printf("\n\nFind test\n");

	btree = AVLCreate(CmpInts);

	AVLInsert(btree, &array[7]);
	AVLInsert(btree, &array[11]);
	AVLInsert(btree, &array[3]);
	AVLInsert(btree, &array[1]);
	AVLInsert(btree, &array[0]);
	AVLInsert(btree, &array[2]);
	AVLInsert(btree, &array[5]);
	AVLInsert(btree, &array[4]);
	AVLInsert(btree, &array[6]);
	AVLInsert(btree, &array[14]);
	AVLInsert(btree, &array[12]);
	AVLInsert(btree, &array[13]);
	AVLInsert(btree, &array[9]);
	AVLInsert(btree, &array[8]);
	AVLInsert(btree, &array[10]);

	find9 = *(int*)AVLFind(btree, &num9);
	
	if (find9 != num9)
	{
		printf("Find failed\n");
		printf("found %d, searched for %d", find9, num9);
		AVLDestroy(btree);
		return 0;		
	}

	AVLDestroy(btree);

	printf("passed\n");
	return 1;
}

int ForEachTest()
{
	avl_t *btree = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int adding = 10;
	int index = 0;

	printf("\n\nFor Each test\n");

	btree = AVLCreate(CmpInts);

	AVLInsert(btree, &array[7]);
	AVLInsert(btree, &array[11]);
	AVLInsert(btree, &array[3]);
	AVLInsert(btree, &array[1]);
	AVLInsert(btree, &array[0]);
	AVLInsert(btree, &array[2]);
	AVLInsert(btree, &array[5]);
	AVLInsert(btree, &array[4]);
	AVLInsert(btree, &array[6]);
	AVLInsert(btree, &array[14]);
	AVLInsert(btree, &array[12]);
	AVLInsert(btree, &array[13]);
	AVLInsert(btree, &array[9]);
	AVLInsert(btree, &array[8]);
	AVLInsert(btree, &array[10]);

	AVLForEach(btree, AddTo, &adding, PRE_ORDER);
	for (index = 0; index <= 14; ++index)
	{
		if (array[index] != index + adding)
		{
			printf("PreOrder failed\n");
			printf("@index %d, value = %d", index, array[index]);
			AVLDestroy(btree);
			return 0;		
		}
	} 

	AVLForEach(btree, AddTo, &adding, IN_ORDER);
	for (index = 0; index <= 14; ++index)
	{
		if (array[index] != index + (adding * 2))
		{
			printf("InOrder failed\n");
			printf("@index %d, value = %d", index, array[index]);
			AVLDestroy(btree);
			return 0;		
		}
	} 

	AVLForEach(btree, AddTo, &adding, POST_ORDER);
	for (index = 0; index <= 14; ++index)
	{
		if (array[index] != index + (adding * 3))
		{
			printf("PostOrder failed\n");
			printf("@index %d, value = %d\n", index, array[index]);
			AVLDestroy(btree);
			return 0;		
		}
	} 

	AVLDestroy(btree);

	printf("passed\n");
	return 1;
}

int main()
{
	
	size_t pass = 0;

	pass += Stage1Test();
	pass += InsertTest();
	pass += RemoveTest();
	pass += FindTest();
	pass += ForEachTest();
		
	if (ALL_PASS == pass)
	{
		printf("\n\n\nALL PASSED\n\n\n");
	}
	return 0;
}

