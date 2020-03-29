#include <stdlib.h>
#include <assert.h> 		/* assert */

#include "pqueue.h"
#include "sorted_list.h"	/* sorted list functions and types */

/*****MACROS*****/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/*****TYPEDEFS, INTERNAL GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

struct pqueue
{
	sorted_list_t *list;
	sorted_compare_t cmp;
};

/*****FUNcTIONS******/
pqueue_t *PQCreate(pqcompare_t compare)
{
	pqueue_t *new_queue = (pqueue_t*)SortedListCreate(compare);

	return new_queue;
}

void PQDestroy(pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	SortedListDestroy((sorted_list_t*) pqueue);
}

int PQIsEmpty(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	
	return SortedListIsEmpty((sorted_list_t*) pqueue);
}

size_t PQSize(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	
	return SortedListSize((sorted_list_t*) pqueue);
}

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	ASSERT_NOT_NULL(pqueue);
	SortedListInsert((sorted_list_t *) pqueue, data);
	
	return 0;
}

void PQDequeue(pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	SortedListPopFront((sorted_list_t *) pqueue);
}

void *PQPeek(const pqueue_t *pqueue)
{
	ASSERT_NOT_NULL(pqueue);
	return SortedListGetData(SortedListBegin((sorted_list_t *) pqueue));
}

void *PQErase(pqueue_t *pqueue, ismatch_t ismatch, void *key)
{
	sorted_list_iter_t iterator;
	void *data = NULL;

	ASSERT_NOT_NULL(pqueue);
	
	iterator =  SortedListFindIf(SortedListBegin((sorted_list_t *) pqueue),
									SortedListEnd((sorted_list_t *) pqueue),
									ismatch,
									key);
	data = SortedListGetData(iterator);

	SortedListRemove(iterator);
	
	return data;
}

void PQClear(pqueue_t *pqueue)
{
	sorted_list_iter_t iterator;

	ASSERT_NOT_NULL(pqueue);

	iterator = SortedListBegin((sorted_list_t *) pqueue);
	while(!SortedListIsSame(iterator, SortedListEnd((sorted_list_t *) pqueue)))
	{
		iterator = SortedListRemove(iterator);
	}
}



