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

/******FUNCTIONS******/
int HeapSort(void* begin, size_t nmemb, size_t size_elem, 
			int (*compr)(const char*, const char* char*), void* param)
{
	/*assert inputs are not NULL*/
	
	/*store constant parameters into a struct*/

	/**rearrange array into a heap**/
	/*from end to begining of array*/
		/*heapify*/

	/**extract each element and rearange**/
	/*from end to begining*/
		/*swap the root with current element*/
		/*re-heapify*/	
}

static void HSHeapify(char* root, char* end, sort_param_t* params)
{
	/*set left and right children*/

	/*if left child is before root*/
		/*set the left to be largest*/
	/*if right is the largest*/
		/*set right to the largest*/
	
	/*if largest is ot the root*/
		/*swap largest with root*/
		/*heapify*/
}

static HSSwap()
{
	/*perform a swap*/
}
