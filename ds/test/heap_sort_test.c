#include <stdio.h>
#include <stdlib.h>

#include "heap_sort.h"

#define ALL_PASS (5)

int IntCmpr(const void* data1, const void* data2, void* param)
{
	(void)param;
	printf("comparing %d, %d\n", *(int*) data1, *(int*)data2);
	return *(int*)data1 - *(int*)data2;
}

int IsSameArray(int* array1, size_t size1, int* array2, size_t size2)
{
	size_t i = 0;
	if (size1 != size2)
	{
		return 0;
	}
	for (i = 0; i <= size1; ++i)
	{
		if (array1[i] != array2[i])
		{
			return 0;
		}
	}
	return 1;
}

void PrintArray(int* array, size_t size)
{
	int i = 0;
	for (i = 0; i < size; ++i)
	{	
		printf("%d ", array[i]);
		printf("\0");
	}
}

void Test()
{
	int array[] = 	 {5, 6, 8, 1, 9, 7, 2, 3, 4, 0};
	int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	HeapSort(&array, 10, sizeof(int), IntCmpr, 0);
	
	if (!IsSameArray(array, 10, expected, 10))
	{
		printf("failed\n");
		PrintArray(array, 10);
		return;
	}
	printf("passed\n");
		
}

int main()
{
	Test();

	return 0;
}
