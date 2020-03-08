/******************************************************************************
 *	Title:		Sorting Algortims
 *	Authour:	Alistair Hudson
 *	Reviewer:	Ivana
 *	Version:	08.03.2020.0
 ******************************************************************************/

#include <stdlib.h>
#include <assert.h>		/* assert */

#include "sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))\

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static void Swap(int *x, int *y);

/******FUNCTIONS******/
static void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(int *array, size_t array_size)
{
	int temp = 0;
	int j = 0;

	for (j = 0; j < array_size; ++j)
	{
		int index = 1;
		for (index = 1; index < array_size; ++index)
		{
			if (array[index] < array[index - 1])
			{
				Swap(&array[index], &array[index - 1]);
			}
		}
	}
}

void BubbleSortOpt(int *array, size_t array_size)
{
	int sorted = 0;
	int temp = 0;
	int index = 1;

	while (!sorted)
	{
		sorted = 1;
		for (index = 1; index < array_size; ++index)
		{
			if (array[index] < array[index - 1])
			{
				Swap(&array[index], &array[index - 1]);
				sorted = 0;
			}
		}
	}
}

void SelectionSort(int *array, size_t array_size)
{
	int index = 0;
	int j = 0;

	for (index = 0; index < array_size; ++index)
	{
		for(j = index + 1; j < array_size; ++j)
		{
			if (array[j] < array [index])
			{
				Swap(&array[j], &array[index]);
			}
		}
	}
}

void InsertionSort(int *array, size_t array_size)
{
	int index = 1;

	for (index = 1 ; index < array_size; ++index)
	{
		int key = array[index];
		int j = index - 1;
		
		while (j >= 0 && array[j] > key)
		{
			array[j+1] = array[j];
			--j;
		}
		array[j + 1] = key;
	}
}
