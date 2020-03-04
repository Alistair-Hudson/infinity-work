#include <stdlib.h>
#include <assert.h>		/* assert */

#include "queue.h"
#include "slist.h"

/******MARCOS******/
#define MEMBER_SIZE		(sizeof(struct member))

/******TYPEDEFS, INTERNAL GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/

struct queue
{
	void *front;
	void *end;
};

/******FUNCTIONS******/
queue_t *QCreate()
{
	queue_t *new_queue = (queue_t*)SListCreate();
	
	return new_queue;
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	SListDestroy((list_t*)queue);
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return SListIsEmpty((list_t*)queue);
}

size_t QCount(const queue_t *queue)
{
	assert(NULL != queue);

	return SListCount((list_t*)queue);
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	SListInsertBefore((list_t*)queue, SListEnd((list_t*)queue) , data);

	return 0;
}

void QDequeue(queue_t *queue)
{
	SListRemove(SListBegin((list_t*)queue));
}

void *QPeek(queue_t *queue)
{
	assert(NULL != queue);

	return SListGetData(SListBegin((list_t*)queue));
}

queue_t *QAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	return (queue_t*)SListAppend((list_t*)dest, (list_t*)src);

}
