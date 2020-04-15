/******************************************************************************
 *	Title:		Generic Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	07.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "generic_sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static void QSortImp(void* base, size_t low, size_t high,
					int (*compar)(const void*, const void*, void*), void* param);

static size_t QSPartion(void* base, size_t low, size_t high,
						int (*compar)(const void *, const void *, void*), 
						void* param);

static void QSSwap(void* array, size_t index1, size_t index2);

static int MSortImp(void* base, size_t left, size_t right, size_t size,
					int (*compar)(const void *, const void *, void*), 
					void* param);

static int MSMerge(void* base, size_t left, size_t middle, size_t right, 
				size_t size, int (*compar)(const void *, const void *, void*), 
				void* param);

/******FUNCTIONS******/
void QSort(void* base, size_t nmemb, size_t size,  
			int (*compar)(const void*, const void*, void*), void* param)
{
	QSortImp(base, 0, nmemb-1, compar, param);
}

static void QSortImp(void* base, size_t low, size_t high,
						int (*compar)(const void *, const void *, void*),
						void* param)
{
	/*if low is before high*/
	if (0 >= compar(base[low], base[high], param))
	{
		/*create a partition index*/
		size_t part_index = QSPartion(base, low, high, compar, param);

		/*recursion on lower partition*/
		QSortImp(base, low, part_index-1, compar, param);
		/*recursion on upper partition*/
		QSortImp(base, part_index+1, high, compar, param);
	}
}

static size_t QSPartion(void* base, size_t low, size_t high,
						int (*compar)(const void *, const void *, void*),
						void* param)
{
	void* pivot = base[high];
	int i = low - 1;
	size_t j = low;
	/*for index from low to high*/
	for (j = low; j <= high; ++j)
	{
		/*if index is before pivot*/
		if (0 >= compar(base[j], pivot, param))
		{
			/*increase low*/
			++i;
			/*swap*/
			QSSwap(base, i, j);
		}
	}
	/*swap low and high*/
	QSSwap(base, i+1, high);
	/*return low +1*/
	return i + 1;
}

static void QSSwap(void* array, size_t index1, size_t index2)
{
	/*put index1 into a temporary variable*/
	void* temp = NULL;
	*temp = *array[index1];
	/*put index2 into index1*/
	*array[index1] = *array[index2];
	/*put the temporary varible into index2*/
	*array[index2] = *temp;
}

int MSort(void* base, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *, void*), void* param)
{
	return MSortImp(base, 0, nmemb - 1, size, compar, param);
}

static int MSortImp(void* base, size_t left, size_t right, size_t size,  
					int (*compar)(const void *, const void *, void*), 
					void* param)
{
	/*if left is before right*/
	if (0 >= compar(base[left], base[right], param))
	{
		/*find middle*/
		size_t middle = (left + right)/2;

		/*recursion on left*/
		if (0 != MSortImp(base, left, middle, size, compar, param))
		{
			return 1;
		}
		/*recursion on right*/
		if (0 != MSortImp(base, middle+1, right, size, compar, param))
		{
			return 1;
		}

		/*merge the two halves*/
		if (0 != MSMerge(base, left, middle, right, size, compar, param))
		{
			return 1;
		}
	}
	return 0;
}

static int MSMerge(void* base, size_t left, size_t middle, size_t right, 
				size_t size, int (*compar)(const void *, const void*, void*),
				void* param)
{
	/*set
		*n1
		*n2
		*/
	size_t i = 0, j= 0, k = left;
	size_t n1 = middle - left + 1;
	size_t n2 = right - middle;

	/*Allocate for array LEFT and RIGHTH*/
	/*if either fails return 1*/
	void* LEFT = malloc(n1 * size);
	if (NULL == LEFT)
	{
		return 1;
	}
	void* RIGHT = malloc(n2 * size);
	if (NULL == RIGHT)
	{
		free(LEFT);
		return 1;
	}
	
	/*for i from 0 until n1*/
		/*LEFT[i] = base[left + i]*/
	for (i = 0; i < n1; ++i)
	{
		LEFT[i] = base[left + i];
	}
	/*for j from 0 until n1*/
		/*RIGHT[i] = base[middle + i]*/
	for (j = 0; j < n2; ++j)
	{
		RIGHT[j] = base[middle+1+j];
	}
	
	/*reset i and j*/
	i = 0;
	j = 0;
	/*while i is before n1 && j is before n2*/
	while (i < n1 && j < n2)
	{	
		/*if LEFT is before RIGHT*/
		if (0 >= compar(LEFT[i], RIGHT[j], param))
		{
			/*base[k] = LEFT*/
			base[k] = LEFT[i];
			/*increase i*/
			++i;
		}
		/*else*/
		else
		{
			/*base[k] = RIGHT*/
			base[k] = RIGHT[j];
			/*increase j*/
			++j;
		}
		/*increase k*/
		++k
	}

	/*fill reamining LEFT*/
	while (i < n1)
	{
		base[k] = LEFT[i];
		++i;
		++k;
	}
	/*fill reamaining RIGHT*/
	while (j < n2)
	{
		base[k] = RIGHT[j];
		++j;
		++k;
	}
	/*free LEFT and RIGHT*/
	free(LEFT);
	free(RIGHT);

	return 0;
}








