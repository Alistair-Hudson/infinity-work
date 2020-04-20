/******************************************************************************
 *	Title:		Heap Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	20.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "heap.h"



/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define INIT_CAP				(10)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

/******FUNCTIONS******/
int HeapSort(heap_t* heap)
{
	/*assert heap is not NULL*/

	/*perform a quick sort (merge sort) on the heap with a parameter*/
}

static void HeapQSort(heap_t* heap)
{
	/*if start of vector location equals the end*/
		/*return*/

	/*if the the start elementis is less than the end element*/
		/*create a partition index*/
		
		/*perform recursion on lower half*/
		/*perform recursion on upper half*/
}

static char* HeapQSPartion*()
{
	
	/*from the begining to the last element*/
		/*if element is before pivot point*/
			/*swap*/
			/*move to next element*/
}

static HeapQSSwap()
{
	/*perform a swap*/
}
