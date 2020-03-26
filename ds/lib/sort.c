/******************************************************************************
 *	Title:		Sorting Algortims
 *	Authour:	Alistair Hudson
 *	Reviewer:	Ivana
 *	Version:	26.03.2020.2
 ******************************************************************************/

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

static int RadixSortLoop(int *array, size_t array_size, int *BitLUT, 
						int *buffer, int mask, size_t shift, size_t bit_range);

static int QuickSortImp(int* array, size_t low, size_t high);

static size_t Partion(int* array, size_t low, size_t high);

static int MergeSortImp(int* array, size_t left, size_t right);

static void Merge(int* array, size_t left, size_t middle, size_t right);

static int SearchRec(int* array, size_t index, size_t size, int key);

/******FUNCTIONS******/
int BinarySearchIt(int* array, size_t size, int key)
{
	size_t jump = size / 2;
	size_t index = jump;
	int SEARCHING = 1;

	while (SEARCHING)
	{
		if(0 == jump)
		{
			SEARCHING = 0;
		}
		if (array[index] > key)
		{
			jump /= 2;
			index -= jump;
		}
		else if (array[index] < key)
		{
			jump /= 2;
			index += jump;
		}
		else if (array[index] == key)
		{
			return index;
		}
	}
	return -1;
}

int BinarySearchRec(int* array, size_t size, int key)
{
	return SearchRec(array, size, size, key);
}

static int SearchRec(int* array, size_t index, size_t size, int key)
{
	index = index / 2;
	if (array[index] > key)
	{
		if (0 == index)
		{
			return -1;
		}	
		return SearchRec(array, index, size, key);
	}
	else if (array[index] < key)
	{
		if (array[index] == array[size-1])
		{
			return -1;
		}
		return SearchRec(array, (size + index), size, key);
	}
	else if (array[index] == key)
	{
		return index;
	}
}

int MergeSort(int* array, size_t size)
{

	return MergeSortImp(array, 0, size - 1);
}

static int MergeSortImp(int* array, size_t left, size_t right)
{
	if (left < right)
	{
		size_t middle = (left + right)/2;

		MergeSortImp(array, left, middle);
		MergeSortImp(array, middle + 1, right);

		Merge(array, left, middle, right);
	}
	return 0;
}

static void Merge(int* array, size_t left, size_t middle, size_t right)
{
	size_t i = 0, j = 0, k = left;
	size_t n1 = middle - left + 1;
	size_t n2 = right - middle;

	int* LEFT = malloc(n1 * sizeof(int));
	int* RIGHT = malloc(n2 * sizeof(int));

	for (i = 0; i < n1; ++i)
	{
		LEFT[i] = array[left + i];
	}
	for (j = 0; j < n2; ++j)
	{
		RIGHT[j] = array[middle+1+j];
	}

	i = 0;
	j = 0;

	while (i < n1 && j < n2)
	{
		if (LEFT[i] <= RIGHT[j])
		{
			array[k] = LEFT[i];
			++i;
		}
		else
		{
			array[k] = RIGHT[j];
			++j;
		}
		++k;
	}

	while(i < n1)
	{
		array[k] = LEFT[i];
		++i;
		++k;
	}
	while(j < n2)
	{
		array[k] = RIGHT[j];
		++j;
		++k;
	}
	free(LEFT);
	free(RIGHT);
}

int QuickSort(int* array, size_t size)
{
	return QuickSortImp(array, 0, size-1);
}

static int QuickSortImp(int* array, size_t low, size_t high)
{

	if (low < high)
	{
		int part_index = Partion(array, low, high);

		QuickSortImp(array, low, part_index - 1);
		QuickSortImp(array, part_index + 1, high);
	}
	return 0;
}

static size_t Partion(int* array, size_t low, size_t high)
{
	int pivot = array[high];
	int i = low - 1;
	size_t j = low;

	for (j = low; j <= high; ++j)
	{
		if(array[j] < pivot)
		{
			++i;
			Swap(&array[i], &array[j]);
		}
	}
	Swap(&array[i + 1], &array[high]);
	return i + 1;
}

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
		--array_size;
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
	int *BitLUT = NULL;
	
	bit_range = BitRange(num_of_bits);
	
	BitLUT = (int*)malloc(bit_range * sizeof(int));
	if(NULL == BitLUT)
	{
		return 1;
	}
	CreateLUT(BitLUT, bit_range);

	buffer = (int*)malloc(array_size * sizeof(int));
	if (NULL == buffer)
	{
		free(BitLUT);
		return 2;
	}

	mask = bit_range - 1;
	while(0 != mask)
	{
		RadixSortLoop(array, array_size, BitLUT, buffer, 
								mask, shift, bit_range);
		shift += num_of_bits;
		mask <<= num_of_bits;

	}

	free(BitLUT);
	free(buffer);

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
	return (1 << num_of_bits);
}

static int RadixSortLoop(int *array, size_t array_size, int *BitLUT, 
						int *buffer, int mask, size_t shift, size_t bit_range)
{
	size_t index = 0;
	int steps = 0;
		
		for (index = 0; index <= bit_range; ++index)
		{
			BitLUT[index] = 0;
		}
		for (index = 0; index < array_size; ++index)
		{
			int temp = array[index] & mask;
			temp >>= shift;
			BitLUT[temp] += 1;
		}
		steps = BitLUT[0];
		BitLUT[0] = 0;
		for (index = 1; index <= bit_range; ++index)
		{
			int next_steps = BitLUT[index] + steps;
			BitLUT[index] = steps;
			steps = next_steps;
		}
		for (index = 0; index < array_size; ++index)
		{
			int temp = array[index] & mask;
			temp >>= shift;
			buffer[BitLUT[temp]] = array[index];
			BitLUT[temp] += 1;
		}

		for (index = 0; index < array_size; ++index)
		{
			array[index] = buffer[index];
		}

	return 0;
}






