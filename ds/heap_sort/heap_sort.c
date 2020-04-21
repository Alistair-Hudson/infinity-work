/******************************************************************************
 *	Title:		Heap Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	20.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <string.h>		/* memcpy */

#include "heap_sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define INIT_CAP				(10)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef int(*cmp)(const void*, const void*, void* param);

typedef struct sort_param
{
	size_t nmemb;
	size_t size_elem;
	cmp compare;
	void* param;
	char* swap_buffer;
		
}sort_param_t;

static void HSSwap(char* item1, char* item2, char* swap_buffer, const size_t size_elem);

static void HSHeapify(char* root, int index, const sort_param_t* params);

/******FUNCTIONS******/
int HeapSort(void* begin, size_t nmemb, size_t size_elem, 
			int (*compr)(const void*, const void*, void*), void* param)
{
	int i = 0;
	sort_param_t* params = NULL;
	/*assert inputs are not NULL*/
	ASSERT_NOT_NULL(begin);

	params = malloc(sizeof(struct sort_param));
	if (NULL == params)
	{
		return 1;
	}
	/*store constant parameters into a struct*/
	params->nmemb = nmemb;
	params->size_elem = size_elem;
	params->compare = compr;
	params->param = param;
	params->swap_buffer = malloc(nmemb*size_elem);
	if (NULL == params->swap_buffer)
	{
		free(params);
		return 1;
	}

	/**rearrange array into a heap**/
	/*from last sub-root to begining of array*/
	for (i = (nmemb/2 -1); i >= 0; --i)
	{
		/*heapify*/
		HSHeapify((char*)begin, i, params);
	}

	/**extract each element and rearange**/
	/*from end to begining*/
	for (i = nmemb; i >= 0; --i)
	{
		/*swap the root with current element*/
		HSSwap((char*)begin, 
				(char*)begin+(i*size_elem), 
				params->swap_buffer, 
				size_elem);
		/*re-heapify*/
		params->nmemb = i;	
		HSHeapify((char*)begin, 0, params);
	}

	free(params->swap_buffer);
	free(params);
	return 0;
}

static void HSHeapify(char* root, int index, const sort_param_t* params)
{
	/*set index as largest*/
	int largest = index;
	/*set left and right children*/
	int left = 2*index + 1;
	int right = 2*index + 2;

	/*if left child is before root and is not pointing past the end*/
	if (left < params->nmemb && 
		0 >= params->compare(root+(largest*params->size_elem), 
								root+(left*params->size_elem), 
								params->param))
	{
		/*set the left to be largest*/
		largest = left;
	}	
	/*if right is the largest and is not pointing past the end*/
	if (right < params->nmemb && 
		0 >= params->compare(root+(largest*params->size_elem), 
								root+(right*params->size_elem), 
								params->param))
	{
		/*set right to the largest*/
		largest = right;
	}

	/*if largest is not the index*/
	if (largest != index)
	{
		/*swap largest with index*/
		HSSwap(root+(largest*params->size_elem), 
				root+(index*params->size_elem), 
				params->swap_buffer, 
				params->size_elem);
		/*heapify*/
		HSHeapify(root, largest, params);
	}
}

static void HSSwap(char* item1, char* item2, char* swap_buffer, const size_t size_elem)
{
	/*perform a swap*/
	memcpy(swap_buffer, item1, size_elem);
	memcpy(item1, item2, size_elem);
	memcpy(item2, swap_buffer, size_elem);
}







