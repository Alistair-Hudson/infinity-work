/******************************************************************************
 *	Title:		Heap Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	20.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define INIT_CAP				(10)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef int(*cmp)(const void*, const void*, void* param);

typedef struct sort_param
{
	size_t size_elem;
	cmp cmpare;
	void* param;
	char* swap_buffer;
		
}sort_param_t;
/******FUNCTIONS******/
int HeapSort(void* begin, size_t nmemb, size_t size_elem, 
			int (*compr)(const char*, const char* char*), void* param)
{
	int i = 0;
	sort_param_t* params = {size_elem, compr, param, NULL};
	/*assert inputs are not NULL*/
	ASSERT_NOT_NULL(begin);

	/*store constant parameters into a struct*/
	params->swap_buffer = malloc(nmemb*size_elem);
	if (NULL == params->swap_buffer)
	{
		return 1;
	}

	/**rearrange array into a heap**/
	/*from last sub-root to begining of array*/
	for (i = (nmemb/2 -1); i >= 0; --i)
	{
		/*heapify*/
		HSHeapify((char*)(begin+(i*size_elem)), 
					(char*)(begin+(nmemb*size_elem)), 
					params);
	}

	/**extract each element and rearange**/
	/*from end to begining*/
	for (i = nmemb; i >= 0; --i)
	{
		/*swap the root with current element*/
		HSSwap((char*)begin, (char*)(begin+(i*size_elem)), 
				params->swap_buffer, size_elem);
		/*re-heapify*/	
		HSHeapify((char*)begin, (char*)begin+(i*size_elem), params);
	}

	free(params->swap_buffer);
	return 0;
}

static void HSHeapify(char* root, char* end, const sort_param_t* params)
{
	/*set root as largest*/
	/*set left and right children*/

	/*if left child is before root*/
		/*set the left to be largest*/
	/*if right is the largest*/
		/*set right to the largest*/
	
	/*if largest is ot the root*/
		/*swap largest with root*/
		/*heapify*/
}

static HSSwap(char* item1, char* item2, char* swap_buffer, const size_t size_elem)
{
	/*perform a swap*/
}
