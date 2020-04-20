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
typedef int(*cmp)(const void *, const void *, void * param);

typedef struct sort_param
{
	size_t size_elem;
	cmp compare;
	void* param;
}sort_param_t;

static void QSortImp(char* begin, char* end, const sort_param_t* params);

static char* QSPartion(char* begin, char* end, const sort_param_t* params);

static void QSSwap(char* item1, char* item2);

static int MSortImp(char* begin, char* end, const sort_param_t* params);

static int MSMege(char* begin, char* middle, char* end, const sort_param_t* params);

/******FUNCTIONS******/
void QSort(void* begin, size_t nmemb, size_t size,  
			int (*compar)(const char*, const char*, char*), void* param)
{
	sort_params_t* params = {size, compar, param};
	QSortImp(begin, begin+(nmemb*size), params);
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
	QSSwap(swap, end);
	/*return low +1*/
	return swap;
}

static void QSSwap(char* item1, char* item2)
{
	/*put index1 into a temporary variable*/
	char* temp = NULL;
	*temp = *item1;
	/*put index2 into index1*/
	*item1 = *item2;
	/*put the temporary varible into index2*/
	*item1 = *temp;
}

int MSort(void* begin, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *, char*), void* param)
{
	sort_param_t* params = {size, compar, param};
	return MSortImp(begin, begin+(nmemb*size), params);
}

static int MSortImp(char* begin, char* end, const sort_param_t* params)
{
	if (begin == end-params->size_elem)
	{
		return 0;
	}
	/*if left is before right*/
	if (0 >= params->compare(begin, end, params->param))
	{
		/*find middle*/
		char* middle = (begin + end)/2;

		/*recursion on left*/
		if (0 != MSortImp(begin, middle, params))
		{
			return 1;
		}
		/*recursion on right*/
		if (0 != MSortImp(middle+1, end, params))
		{
			return 1;
		}

		/*merge the two halves*/
		if (0 != MSMerge(begin, middle, end, params))
		{
			return 1;
		}
	}
	return 0;
}

static int MSMege(char* begin, char* middle, char* end, sort_param_t* params)
{
	/*set
		*n1
		*n2
		*/
	char* left = begin;
	char* right = middle;

	/*Allocate for array LEFT and RIG1HTH*/
	/*if either fails return 1*/
	char* LEFT = malloc(n1 * params->size);
	if (NULL == LEFT)
	{
		return 1;
	}
	char* RIGHT = malloc(n2 * params->size);
	if (NULL == RIGHT)
	{
		free(LEFT);
		return 1;
	}
	
	/*for i from 0 until n1*/
		/*LEFT[i] = begin[left + i]*/
	while (left < middle)
	{
		*LEFT = *left;
		LEFT += params->size_elem;
		left += params->size_elem;
	}
	/*for j from 0 until n1*/
		/*RIGHT[i] = begin[middle + i]*/
	while (right < end)
	{
		*RIGHT = *right;
		RIGHT += params->size_elem;
		right += params->size_elem;
	}
	
	/*reset i and j*/
	i = 0;
	j = 0;
	/*while i is before n1 && j is before n2*/
	while (left < middle && right < end)
	{	
		/*if LEFT is before RIGHT*/
		char** smaller = (0 > params->compare(LEFT, RIGHT, param)) ? LEFT : RIGHT
			
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
	/*free LEFT and RIGHT*/
	free(LEFT);
	free(RIGHT);

	return 0;
}








