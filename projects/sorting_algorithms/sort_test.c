#include <stdio.h>
#include <stdlib.h>

#include "sort.h"

#define ALL_PASS		(9)

int AreArraysTheSame(int *arr1, size_t size1, int *arr2, size_t size2)
{
	int index = 0;

	if (size1 != size2)
	{
		return 0;
	}

	for (index = 0; index < size1; ++index)
	{
		if (arr1[index] != arr2[index])
		{
			printf("index = %d, arr1 = %d, arr2 = %d", index, arr1[index], arr2[index]);
			return 0;
		}
	}
	return 1;
}

int BubbleTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 7, 8, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 7, 6, 8};
	size_t size = 9;

	printf("\n\n\nBubble Test\n");

	BubbleSort(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	BubbleSort(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	BubbleSort(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	BubbleSort(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Bubble passed\n");
	
	return 1;

}

int OptBubTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 7, 8, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 7, 6, 8};
	size_t size = 9;

	printf("\n\n\nBubble Opt Test\n");

	BubbleSortOpt(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	BubbleSortOpt(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	BubbleSortOpt(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	BubbleSortOpt(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	
	return 1;

}

int SelectionTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 7, 8, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 7, 6, 8};
	size_t size = 9;

	printf("\n\n\nSelection Test\n");

	SelectionSort(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	SelectionSort(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	SelectionSort(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	SelectionSort(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Selection passed\n");
	
	return 1;

}

int InsertionTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 7, 8, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 7, 6, 8};
	size_t size = 9;

	printf("\n\n\nInsertion Test\n");

	InsertionSort(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	InsertionSort(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	InsertionSort(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	InsertionSort(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Insertion passed\n");

	return 1;

}

int CountTest()
{
	int exp[] = {1, 2, 3, 5, 5, 6, 8, 8, 9};
	int rand[] = {5, 3, 9, 5, 1, 2, 8, 8, 6};
	int rev[] = {9, 8, 8, 6, 5, 5, 3, 2, 1};
	int sort[] = {1, 2, 3, 5, 5, 6, 8, 8, 9};
	int almost[] = {1, 2, 3, 9, 5, 5, 8, 6, 8};
	size_t size = 9;

	printf("\n\n\nCount Test\n");

	CountingSort(rand, size, 1, 9);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	CountingSort(rev, size, 1, 9);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	CountingSort(sort, size, 1, 9);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	CountingSort(almost, size, 1, 9);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Count passed\n");

	return 1;

}

int RadixTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 8, 7, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6,7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 8, 6, 7};
	size_t size = 9;

	printf("\n\n\nRadix Test\n");

	RadixSort(rand, size, 2);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	RadixSort(rev, size, 2);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	RadixSort(sort, size, 2);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	RadixSort(almost, size, 2);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Radix passed\n");

	return 1;

}

int MergeTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 8, 7, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6,7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 8, 6, 7};
	size_t size = 9;

	printf("\n\n\nMerge Test\n");

	MergeSort(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

	MergeSort(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}

	MergeSort(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	MergeSort(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Merge passed\n");

	return 1;

}

int QuickTest()
{
	int exp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int rand[] = {5, 3, 9, 4, 1, 2, 8, 7, 6};
	int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int sort[] = {1, 2, 3, 4, 5, 6,7, 8, 9};
	int almost[] = {1, 2, 3, 9, 4, 5, 8, 6, 7};
	size_t size = 9;

	printf("\n\n\nQuick Test\n");

	QuickSort(rand, size);
	if (!AreArraysTheSame(exp, size, rand, size))
	{
		printf("rand failed\n");
		return 0;
	}

/*	QuickSort(rev, size);
	if (!AreArraysTheSame(exp, size, rev, size))
	{
		printf("rev failed\n");
		return 0;
	}
*/
	QuickSort(sort, size);
	if (!AreArraysTheSame(exp, size, sort, size))
	{
		printf("sort failed\n");
		return 0;
	}

	QuickSort(almost, size);
	if (!AreArraysTheSame(exp, size, almost, size))
	{
		printf("almost failed\n");
		return 0;
	}

	printf("Quick passed\n");

	return 1;

}

int BSearchTest()
{
	int array[] = {1, 2, 3, 4, 5, 6,7, 8, 9};
	int find = 0;
	int key = 2;
	int alt_key = 12;
	size_t size = 9;

	printf("\n\n\nBSearch Test\n");

	find = BinarySearchIt(array, size, key);
	if (array[find] != key)
	{
		printf("Iterative search failed\n");
		return 0;
	}

	find = BinarySearchIt(array, size, alt_key);
	if ((-1) != find)
	{
		printf("failed iterative search failed %d\n", find);
		return 0;
	}

	find = BinarySearchRec(array, size, key);
	if (array[find] != key)
	{
		printf("Rec search failed\n");
		return 0;
	}

	find = BinarySearchRec(array, size, alt_key);
	if ((-1) != find)
	{
		printf("failed rec search failed\n");
		return 0;
	}

	printf("BSearch Passed\n");
	return 1;
}
int main()
{
	size_t pass = 0;

	pass += BubbleTest();
	pass += OptBubTest();
	pass += SelectionTest();
	pass += InsertionTest();
	pass += CountTest();
	pass += RadixTest();
	pass += MergeTest();
	pass += QuickTest();
	pass += BSearchTest();

	if (pass == ALL_PASS)
	{
		printf("\n\n\n\nALL PASSED!!!!!\n\n\n\n");
	}

	return 0;
}
