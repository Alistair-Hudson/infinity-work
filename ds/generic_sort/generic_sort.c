/******************************************************************************
 *	Title:		Generic Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	07.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */

#include "generic_sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef int(*cmp)(const void *, const void *, void * param);

typedef struct sort_param
{
	size_t size_elem;
	cmp compare;
	void* param;
	char* swap_buffer;

}sort_param_t;

static void QSortImp(char* begin, char* end, const sort_param_t* params);

static char* QSPartion(char* begin, char* end, const sort_param_t* params);

static void QSSwap(char* item1, char* item2);

static void MSortImp(char* begin, char* end, const sort_param_t* params);

static void MSMege(char* begin, char* middle, char* end, const sort_param_t* params);

/******FUNCTIONS******/
int QSort(void* begin, size_t nmemb, size_t size,  
			int (*compar)(const char*, const char*, char*), void* param)
{
	sort_params_t* params = {size, compar, param, NULL};
	params->swap_buffer = malloc(nmemb*size);
	if (NULL == params->swap_buffer)
	{
		return 1;
	}
	QSortImp(begin, begin+(nmemb*size), params);
	return 0;
}

static void QSortImp(char* begin, char* end, const sort_param_t* params)
{	
	if (begin == end-params->size_elem)
	{
		return;
	}
	/*if low is before high*/
	if (0 >= params->compare(begin, end, params->param))
	{
		/*create a partition index*/
		char* part_index = QSPartion(begin, end, params);

		/*recursion on lower partition*/
		QSortImp(begin, part_index, params);
		/*recursion on upper partition*/
		QSortImp(part_index, end, params);
	}
}

static char* QSPartion(char* begin, char* end, const sort_param_t* params)
{
	char* pivot = end - params->size_elem;
	char* swap = begin;

	/*for index from low to high*/
	for (begin; begin != end; begin += params->size_elem)
	{
		/*if index is before pivot*/
		if (0 >= params->compare(begin, pivot, params->param))
		{
			/*increase low*/
			swap += params->size_elem;
			/*swap*/
			QSSwap(swap, begin);
		}
	}
	/*swap low and high*/
	QSSwap(swap, end, params);
	/*return low +1*/
	return swap;
}

static void QSSwap(char* item1, char* item2, sort_parma_t* params)
{
	/*put index1 into a temporary variable*/
	memcpy(params->swap_buffer, item1, params->size_elem);
	/*put index2 into index1*/
	memcpy(item1, item2, params->size_elem);
	/*put the temporary varible into index2*/
	memcpy(item2, swap_buffer, params->size_elem);
}

int MSort(void* begin, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *, char*), void* param)
{
	sort_param_t* params = {size, compar, param, NULL};
	params->swap_buffer = malloc(nmemb*size);
	if (NULL == params->swap_buffer)
	{
		return 1;
	}
	MSortImp(begin, begin+(nmemb*size), params);
	return 0;
}

static void MSortImp(char* begin, char* end, const sort_param_t* params)
{
	if (begin == end-params->size_elem)
	{
		return;
	}
	/*if left is before right*/
	if (0 >= params->compare(begin, end, params->param))
	{
		/*find middle*/
		char* middle = (begin + end)/2;

		/*recursion on left*/
		MSortImp(begin, middle, params))
		
		/*recursion on right*/
		MSortImp(middle+1, end, params))
		
		/*merge the two halves*/
		MSMerge(begin, middle, end, params))
	}
}

static void MSMege(char* begin, char* middle, char* end, sort_param_t* params)
{
	/*set
		*n1
		*n2
		*/
	char* left = params->swap_buffer;
	char* right = params->swap_buffer + (middle - begin);
	
	/*for i from 0 until n1*/
		/*LEFT[i] = begin[left + i]*/
	memcpy(parmas->swap_buffer, begin, (begin - middle));
	/*for j from 0 until n1*/
		/*RIGHT[i] = begin[middle + i]*/
	memcpy(pamas->swap_buffer+(middle-begin), middle, end - middle);	
	/*while i is before n1 && j is before n2*/
	while (left < middle && right < end)
	{	
		/*if LEFT is before RIGHT*/
		char** smaller = (0 > params->compare(left, right, params->param)) ? left : right;
			
		memcpy(begin, *smaller, params->size_elem);
		*smaller += params->size_elem;
		begin += params->size_elem;
	}

	/*fill reamining LEFT*/
	while (i < n1)
	{
		*begin = *LEFT;
		LEFT += params->size_elem;
		begin += params->size_elem;
		++i;
	}
	/*fill reamaining RIGHT*/
	while (j < n2)
	{
		*begin = *RIGHT;
		RIGHT += params->size_elem;
		begin += params->size_elem;
		++j;
	}
}








