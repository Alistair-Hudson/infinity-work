/******************************************************************************
 *	Title:		Sorting Algortims
 *	Authour:	Alistair Hudson
 *	Reviewer:	Ivana
 *	Version:	08.03.2020.0
 ******************************************************************************/
#include <stdio.h>		/*TODO*/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))\

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static void Swap(int *x, int *y);

static void CreateLUT(int *lookup_array, size_t range);

static size_t ABSRange(int max, int min);

static size_t BitRange(size_t num_of_bits);

/******FUNCTIONS******/
static void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(int *array, size_t array_size)
{
	size_t j = 0;

	for (j = 0; j < array_size; ++j)
	{
		size_t index = 1;
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
	size_t index = 1;

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
	size_t index = 0;
	size_t j = 0;

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
	size_t index = 1;

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

int CountingSort(int *array, size_t array_size, int min, int max)
{
	int insert = 0;
	size_t index = 0;
	int *NumLUT = (int*)malloc(sizeof(int) *ABSRange(max, min));
	if (NULL == NumLUT)
	{
		return 1;
	}

	CreateLUT(NumLUT, ABSRange(max, min));

	for (index = 0; index < array_size; ++index)
	{
		NumLUT[array[index] - min] += 1;
	}
	
	index = 0;
	for (insert = min; insert <= max; ++insert)
	{
		while (0 < NumLUT[insert - min])
		{
			array[index] = insert;
			++index;
			NumLUT[insert - min] -= 1;
		}
	}

	free(NumLUT);
	
	return 0;
}

int RadixSort(int *array, size_t array_size, size_t num_of_bits)
{
	int mask = 0;
	size_t bit_range = 0;
	int *buffer = NULL;
	size_t shift = 0;
	size_t index = 0;
	int insert = 0;
	int *BitLUT = NULL;
	
	bit_range = BitRange(num_of_bits);
	buffer = (int*)malloc(array_size * sizeof(int));
	if (NULL == buffer)
	{
		return 1;
	}

	mask = bit_range - 1;

	while (0 != mask)
	{
		for(index = 0; index < array_size; ++index)
		{
			buffer[index] = array[index] & (mask << shift);
			buffer[index] >>= shift;
		}
		if (CountingSort(buffer, array_size, 0, mask))
		{
			free(buffer);
			return 2;
		}
		
		for (index = 0; index < array_size; ++index)
		{
			buffer[index] <<= shift;
		}
		
		index = 0;
		for (insert = 0; insert <= bit_range; ++insert)
		{
			while(0 < BitLUT[insert])
			{
				buffer[index] |= insert << shift;
				++index;
				BitLUT[insert] -= 1;
			}
		}
		shift += num_of_bits;
	}
	
	for (index = 0; index < array_size; ++index)
	{
		array[index] = buffer[index];
	}

	return 0;
}

static void CreateLUT(int *lookup_array, size_t range)
{
	size_t lut_index = 0;
	
	for (lut_index = 0; lut_index <= range; ++lut_index)
	{
		lookup_array[lut_index] = 0;
	}
}

static size_t ABSRange(int max, int min)
{
	if (max < min)
	{
		int temp = 0;
		temp = max;
		max = min;
		min = temp;
	}

	return max - min;
}

static size_t BitRange(size_t num_of_bits)
{
	size_t range = 1;

	while (0 < num_of_bits)
	{
		range *= 2;
	}

	return range;
}

