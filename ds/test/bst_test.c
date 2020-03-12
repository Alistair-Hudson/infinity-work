#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define ALL_PASS (1)

int CmpInts(void *int1, void* int2)
{
	return *(int*)int1 - *(int*)int2;
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
printf("b");
	if (!BSTIsEmpty(btree))
	{
		printf("Is Empty failed\n");
		return 0;
	}
printf("c");
	if (0 != BSTSize(btree))
	{
		printf("Size failed\n");
	}
printf("d");		

	BSTDestroy(btree);

	return 1;
}

int main()
{
	
	size_t pass = 0;

	pass += Stage1Test();
	
	if (ALL_PASS == pass)
	{
		printf("\n\n\nALL PASSED\n\n\n");
	}
	return 0;
}

