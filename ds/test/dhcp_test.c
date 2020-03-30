#include <stdio.h>
#include <stdlib.h>

#include "dhcp.h"

#define ALL_PASS (3)

int Stage1Test()
{
	dhcp_t *dhcp = NULL;
	ip_t network = {192, 168, 0, 0};
	size_t subnet_bits = 10;

	printf("\n\nStage 1 test\n");

	dhcp = DHCPCreate(network, subnet_bits);
	if (NULL == dhcp)
	{
		printf("Create faile\n");
		return 0;
	}

/*	if (0 != CountFree(dhcp))
	{
		printf("Count Free failed\n");
	}
		
*/
	DHCPDestroy(dhcp);
	
	printf("passed\n");
	return 1;
}

int AllocateTest()
{
/*	avl_t *btree = NULL;
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
*/	return 1;
}

int FreeTest()
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
	pass += AllocateTest();
	pass += FreeTest();
		
	if (ALL_PASS == pass)
	{
		printf("\n\n\nALL PASSED\n\n\n");
	}
	return 0;
}

