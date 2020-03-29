/******************************************************************************
 *	Title:		Heap
 *	Authour:	Alistair Hudson
 *	Reviewer:	Anya
 *	Version:	29.03.2020.1
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "heap.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define INIT_CAP				(10)
/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
struct heap 
{
	vector_t* vector;
	heap_cmp_t cmp;
};

static void Swap(vector_t* vector, size_t index1, size_t index2);

static int Parent(int index);

static void Heapify(heap_t* heap, size_t index);

static size_t Left(size_t index);

static size_t Right(size_t index);

static int FixHeap(heap_t* heap, size_t index);

/******FUNCTIONS******/
static void Swap(vector_t* vector, size_t index1, size_t index2)
{
	void* temp = NULL;
	temp = VectorGetElement(vector, index1);
	VectorSetElement(vector, index1, VectorGetElement(vector, index2));
	VectorSetElement(vector, index2, temp);
}

static int Parent(int index)
{
	return (index - 1)/2;
}

heap_t* HeapCreate(heap_cmp_t cmp)
{
	heap_t* new_heap = NULL;
	
	new_heap = malloc(sizeof(struct heap));
	if (NULL == new_heap)
	{
		return NULL;
	}

	new_heap->vector = 	VectorCreate(INIT_CAP);
	if (NULL == new_heap->vector)
	{
		free(new_heap);
		return NULL;
	}
	
	new_heap->cmp = cmp;

	return new_heap;
}

void HeapDestroy(heap_t* heap)
{
	ASSERT_NOT_NULL(heap);
	VectorDestroy(heap->vector);
	free(heap);
	heap = NULL;
}

int HeapPush(heap_t* heap, void* data)
{
	size_t index = 0;
	
	ASSERT_NOT_NULL(heap);
	
	index = HeapSize(heap);
	VectorPushBack(heap->vector, data);
	
	return FixHeap(heap, index);
}

void HeapPop(heap_t* heap)
{
	size_t index = 0;

	ASSERT_NOT_NULL(heap);
	
	if (HeapIsEmpty(heap))
	{
		return;
	}
	index = HeapSize(heap);
	Swap(heap->vector, 0, index-1);
	VectorPopBack(heap->vector);
	Heapify(heap, 0);
	
}

static void Heapify(heap_t* heap, size_t index)
{
	size_t left = Left(index);
	size_t right = Right(index);
	size_t smallest = index;

	if(left < HeapSize(heap) && heap->cmp(VectorGetElement(heap->vector, index), 											VectorGetElement(heap->vector, left)))
	{
		smallest = left;
	}
	if(right < HeapSize(heap) && heap->cmp(VectorGetElement(heap->vector, index), 											VectorGetElement(heap->vector, right)))
	{
		smallest = right;
	}
	if(smallest != index)
	{
		Swap(heap->vector, smallest, index);
		Heapify(heap, smallest);
	}
}

static size_t Left(size_t index)
{
	return 2*index + 1;
}

static size_t Right(size_t index)
{
	return 2*index + 2;
}

static int FixHeap(heap_t* heap, size_t index)
{
	while (0 != index && 
						heap->cmp(VectorGetElement(heap->vector, Parent(index)), 											VectorGetElement(heap->vector, index)))
	{
		Swap(heap->vector, Parent(index), index);
		index = Parent(index);
	}
	return 0;

}

void* HeapPeek(const heap_t* heap)
{	
	ASSERT_NOT_NULL(heap);

	if (HeapIsEmpty(heap))
	{
		return NULL;
	}	
	return VectorGetElement(heap->vector, 0);
}

size_t HeapSize(const heap_t* heap)
{
	ASSERT_NOT_NULL(heap);
	return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t* heap)
{
	ASSERT_NOT_NULL(heap);
	return VectorIsEmpty(heap->vector);
}

void* HeapRemove(heap_t* heap, 
			int(*is_match)(void* data, void* param), void* param)
{
	size_t index = 0;
	void* removed = NULL;
	
	ASSERT_NOT_NULL(heap);

	while (!is_match(VectorGetElement(heap->vector, index), param))
	{
		++index;
	}
	removed = VectorGetElement(heap->vector, index);
	Swap(heap->vector, index, HeapSize(heap)-1);
	VectorPopBack(heap->vector);
	Heapify(heap, HeapSize(heap));
	return removed;
}









