#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define ALL_PASS (5)

int CmpInts(const void *int1, const void* int2)
{
	return *(int*)int1 - *(int*)int2;
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
	bst_t *btree = NULL;

	printf("\n\nStage 1 test\n");

	btree = BSTCreate(CmpInts);
	if (NULL == btree)
	{
		printf("Create faile\n");
		return 0;
	}

	if (!BSTIsEmpty(btree))
	{
		printf("Is Empty failed\n");
		return 0;
	}

	if (0 != BSTSize(btree))
	{
		printf("Size failed\n");
	}
		

	BSTDestroy(btree);
	
	printf("passed\n");
	return 1;
}

int InsertTest()
{
	bst_t *btree = NULL;
	int array[] = {5, 9, 4, 8, 3, 1, 2, 7, 6};

	printf("\n\nInsert test\n");

	btree = BSTCreate(CmpInts);

	BSTInsert(btree, &array[0]);

	if (BSTIsEmpty(btree))
	{
		printf("Insert first failed\n");
		BSTDestroy(btree);
		return 0;
	}	
	if (1 != BSTSize(btree))
	{
		printf("Size of 1 failed\n");
		BSTDestroy(btree);
		return 0;
	}
	
	BSTInsert(btree, &array[2]);
	if (2 != BSTSize(btree))
	{
		printf("Insert left failed\n");
		BSTDestroy(btree);
		return 0;
	}

	BSTInsert(btree, &array[6]);
	BSTInsert(btree, &array[4]);
	if (4 != BSTSize(btree))
	{
		printf("Insert right failed\n");
		BSTDestroy(btree);
		return 0;
	}
	
	BSTInsert(btree, &array[1]);
	if (5 != BSTSize(btree))
	{
		printf("Insert to end failed\n");
		BSTDestroy(btree);
		return 0;
	}
	BSTDestroy(btree);

	printf("passed\n");
	return 1;
}

int RemoveTest()
{
	bst_t *btree = NULL;
	bst_iter_t remove2;
	bst_iter_t remove5;
	bst_iter_t remove11;
	bst_iter_t remove14;
	bst_iter_t remove7;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	size_t size = 0;

	printf("\n\nRemove test\n");

	btree = BSTCreate(CmpInts);

	remove7 = BSTInsert(btree, &array[7]);
	remove11 = BSTInsert(btree, &array[11]);
	BSTInsert(btree, &array[3]);
	BSTInsert(btree, &array[1]);
	BSTInsert(btree, &array[0]);
	remove2 = BSTInsert(btree, &array[2]);
	remove5 = BSTInsert(btree, &array[5]);
	BSTInsert(btree, &array[4]);
	BSTInsert(btree, &array[6]);
	remove14 = BSTInsert(btree, &array[14]);
	BSTInsert(btree, &array[12]);
	BSTInsert(btree, &array[13]);
	BSTInsert(btree, &array[9]);
	BSTInsert(btree, &array[8]);
	BSTInsert(btree, &array[10]);
	
	size = BSTSize(btree);

	BSTRemove(remove2);	
	--size;
	if (size != BSTSize(btree))
	{
		printf("Remove leaf failed\n");
		BSTDestroy(btree);
		return 0;
	}
	
	BSTRemove(remove5);
	--size;	
	if (size != BSTSize(btree))
	{
		printf("Remove node with two leaves failed\n");
		BSTDestroy(btree);
		return 0;
	}
	
	BSTRemove(remove11);
	--size;
	if (size != BSTSize(btree))
	{
		printf("Remove subtree failed\n");
		BSTDestroy(btree);
		return 0;
	}

	BSTRemove(remove14);
	--size;
	if (size != BSTSize(btree))
	{
		printf("Remove End failed\n");
		BSTDestroy(btree);
		return 0;
	}
	
	BSTRemove(remove7);
	--size;
	if (size != BSTSize(btree))
	{
		printf("Remove root failed\n");
		BSTDestroy(btree);
		return 0;
	}
	BSTDestroy(btree);

	printf("passed\n");
	return 1;
}

int FindTest()
{
	bst_t *btree = NULL;
	bst_iter_t find9;
	bst_iter_t found9;
	bst_iter_t find5;
	bst_iter_t found5;
	int num9 = 9;
	int num5 = 5;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	printf("\n\nFind test\n");

	btree = BSTCreate(CmpInts);

	BSTInsert(btree, &array[7]);
	BSTInsert(btree, &array[11]);
	BSTInsert(btree, &array[3]);
	BSTInsert(btree, &array[1]);
	BSTInsert(btree, &array[0]);
	BSTInsert(btree, &array[2]);
	find5 = BSTInsert(btree, &array[5]);
	BSTInsert(btree, &array[4]);
	BSTInsert(btree, &array[6]);
	BSTInsert(btree, &array[14]);
	BSTInsert(btree, &array[12]);
	BSTInsert(btree, &array[13]);
	find9 = BSTInsert(btree, &array[9]);
	BSTInsert(btree, &array[8]);
	BSTInsert(btree, &array[10]);

	found9 = BSTFind(btree, Search, &num9);
	
	if (!BSTIterIsEqual(found9, find9))
	{
		printf("Find failed\n");
		BSTDestroy(btree);
		return 0;		
	}

	found5 = BSTGet(btree, &num5);

	if (!BSTIterIsEqual(found5, find5))
	{
		printf("Get failed\n");
		BSTDestroy(btree);
		return 0;		
	}

	BSTDestroy(btree);

	printf("passed\n");
	return 1;
}

int ForEachTest()
{
	bst_t *btree = NULL;
	bst_iter_t from;
	bst_iter_t to;
	bst_iter_t check;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int adding = 10;
	int index = 0;

	printf("\n\nFor Each test\n");

	btree = BSTCreate(CmpInts);

	BSTInsert(btree, &array[7]);
	BSTInsert(btree, &array[11]);
	from = BSTInsert(btree, &array[3]);
	BSTInsert(btree, &array[1]);
	BSTInsert(btree, &array[0]);
	BSTInsert(btree, &array[2]);
	BSTInsert(btree, &array[5]);
	BSTInsert(btree, &array[4]);
	BSTInsert(btree, &array[6]);
	BSTInsert(btree, &array[14]);
	to = BSTInsert(btree, &array[12]);
	BSTInsert(btree, &array[13]);
	BSTInsert(btree, &array[9]);
	BSTInsert(btree, &array[8]);
	BSTInsert(btree, &array[10]);


	check = from;

	BSTForEach(from, to, AddTo, &adding);

	for (index = 3; index < 12; ++index)
	{
		if ((index + adding) != *(int*)BSTGetData(check))
		{
			printf("For each failed\n");
			printf("@ index = %d, expected = %d, actual = %d\n", index, 
									(index + adding), *(int*)BSTGetData(check));
			BSTDestroy(btree);
			return 0;		
		}
		check = BSTNext(check);
	}	
	BSTDestroy(btree);

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

