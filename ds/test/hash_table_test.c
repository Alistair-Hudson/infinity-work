#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

#define ALL_PASS (2)

size_t HashFunc(void *entry)
{
	size_t index = 0;
	index = *(int*)entry;
	return index;
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
	htable_t *htable = NULL;

	printf("\n\nStage 1 test\n");

	htable = HTableCreate(HashFunc, 26, Search);
	if (NULL == htable)
	{
		printf("Create faile\n");
		return 0;
	}

	if (!HTableIsEmpty(htable))
	{
		printf("Is Empty failed\n");
		return 0;
	}

	if (0 != HTableSize(htable))
	{
		printf("Size failed\n");
	}
		

	HTableDestroy(htable);
	
	printf("passed\n");
	return 1;
}

int InsertTest()
{
	htable_t *htable = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("\n\nInsert test\n");

	htable = HTableCreate(HashFunc, 26, Search);

	HTableInsert(htable, &array[5]);

	if (HTableIsEmpty(htable))
	{
		printf("Insert first failed\n");
		HTableDestroy(htable);
		return 0;
	}	
	if (1 != HTableSize(htable))
	{
		printf("Size of 1 failed\n");
		HTableDestroy(htable);
		return 0;
	}
	
	HTableInsert(htable, &array[2]);
	if (2 != HTableSize(htable))
	{
		printf("Insert left failed\n");
		HTableDestroy(htable);
		return 0;
	}
	
	HTableInsert(htable, &array[6]);
	HTableInsert(htable, &array[4]);
	if (4 != HTableSize(htable))
	{
		printf("Insert right failed\n");
		HTableDestroy(htable);
		return 0;
	}
	
	HTableInsert(htable, &array[9]);
	if (5 != HTableSize(htable))
	{
		printf("Insert to end failed\n");
		HTableDestroy(htable);
		return 0;
	}

	HTableDestroy(htable);

	printf("passed\n");
	return 1;
}

int RemoveTest()
{
	htable_t *htable = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	size_t size = 0;
	int i = 0;

	printf("\n\nRemove test\n");

	htable = HTableCreate(HashFunc, 26, Search);

	for (i = 0; i <= 14; ++i)
	{
		HTableInsert(htable, &array[i]);
	}
	size = HTableSize(htable);

	HTableRemove(htable, &array[2]);	
	--size;
	if (size != HTableSize(htable))
	{
		printf("Remove leaf failed\n");
		HTableDestroy(htable);
		return 0;
	}
	
	HTableRemove(htable, &array[5]);
	--size;	
	if (size != HTableSize(htable))
	{
		printf("Remove node with two leaves failed\n");
		HTableDestroy(htable);
		return 0;
	}

	HTableRemove(htable, &array[0]);
	--size;
	if (size != HTableSize(htable))
	{
		printf("Remove End failed\n");
		HTableDestroy(htable);
		return 0;
	}
	
	HTableRemove(htable, &array[6]);
	--size;
	if (size != HTableSize(htable))
	{
		printf("Remove subtree failed\n");
		HTableDestroy(htable);
		return 0;
	}

	HTableRemove(htable, &array[7]);
	--size;
	if (size != HTableSize(htable))
	{
		printf("Remove root failed\n");
		HTableDestroy(htable);
		return 0;
	}

	printf("passed\n");

	HTableDestroy(htable);

	return 1;
}

int FindTest()
{
	htable_t *htable = NULL;
	int find9 = 0;
	int num9 = 9;
	int num5 = 5;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int i = 0;

	printf("\n\nFind test\n");

	htable = HTableCreate(HashFunc, 26, Search);

	for (i = 0; i <= 14; ++i)
	{
		HTableInsert(htable, &array[i]);
	}
	find9 = *(int*)HTableFind(htable, &num9);
	
	if (find9 != num9)
	{
		printf("Find failed\n");
		printf("found %d, searched for %d", find9, num9);
		HTableDestroy(htable);
		return 0;		
	}

	HTableDestroy(htable);

	printf("passed\n");
	return 1;
}

int ForEachTest()
{
	htable_t *htable = NULL;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	int adding = 10;
	int index = 0;
	int i = 0;
	printf("\n\nFor Each test\n");

	htable = HTableCreate(HashFunc, 26, Search);

	for (i = 0; i <= 14; ++i)
	{
		HTableInsert(htable, &array[i]);
	}

	HTableForEach(htable, AddTo, &adding);

	for (index = 0; index <= 14; ++index)
	{
		if (array[index] != index + adding)
		{
			printf("PreOrder failed\n");
			printf("@index %d, value = %d", index, array[index]);
			HTableDestroy(htable);
			return 0;		
		}
	} 

	HTableDestroy(htable);

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

