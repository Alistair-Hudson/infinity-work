#include <stdlib.h>
#include <assert.h> 		/* assert */

#include "pqueue.h"
#include "sorted_list.h"	/* sorted list functions and types */
#include "heap.h"			/* heap functions and types */

/*****MACROS*****/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/*****TYPEDEFS, INTERNAL GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

struct pqueue
{
	heap_t *heap;
	heap_cmp_t cmp;
};

/*****FUNcTIONS******/
pqueue_t *PQCreate(pqcompare_t compare)
{
	pqueue_t *new_queue = (pqueue_t*)HeapCreate(compare);

	return new_queue;
}

void PQDestroy(pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	HeapDestroy((heap_t*) pqueue);
}

int PQIsEmpty(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	
	return HeapIsEmpty((heap_t*) pqueue);
}

size_t PQSize(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	
	return HeapSize((heap_t*) pqueue);
}

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	ASSERT_NOT_NULL(pqueue);
	HeapPush((heap_t *) pqueue, data);
	
	return 0;
}

void PQDequeue(pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	HeapPop((heap_t *) pqueue);
}

void *PQPeek(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	return HeapPeek((heap_t *) pqueue);
}

void *PQErase(pqueue_t *pqueue, ismatch_t ismatch, void *key)
{
	void *data = NULL;

	ASSERT_NOT_NULL(pqueue);
	
	data = HeapRemove((heap_t *) pqueue, ismatch, key);
	
	return data;
}

void PQClear(pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);

	while(!HeapIsEmpty((heap_t *) pqueue))
	{
		HeapPop((heap_t *) pqueue);
	}
}



