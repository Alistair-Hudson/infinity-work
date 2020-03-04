#include <stdio.h>
#include <stdlib.h> 	/*malloc*/
#include <assert.h>		/*assert*/
#include "slist.h"

/******MACROS******/
#define NODE_SIZE	(sizeof(struct node))

/******TYPEDEFS AND STRUCTS******/
struct list
{
	iter_t head;
	iter_t tail;
};

typedef struct node
{
	void *data;
	iter_t next_node;
}node_t;

/******INTERNAL FUNCTIONS AND GLOBAL VARIABLES******/
static void UpdateTail(list_t *list, node_t *node);

/******FUNCTIONS******/
list_t *SListCreate()
{
	list_t *_list = NULL;
	node_t *_node = malloc(NODE_SIZE);
	if(NULL == _node)
	{
		return 0;
	}
	_node->data = NULL;
	_node->next_node = NULL;

	_list = malloc(sizeof(struct list));
	if(NULL == _list)
	{
		free(_node);
		_node = NULL;
		return 0;
	}
	_list->head = _node;
	_list->tail = _node;
	_node->data = _list;

	return _list;
}

void SListDestroy(list_t *list)
{
	node_t *free_node = 0;
	node_t *next_2_free = 0;
	
	assert(NULL != list);

	free_node = list->head;
	do
	{
		next_2_free = free_node->next_node;
		free(free_node);
		free_node = next_2_free;
	}while(free_node);
	free_node = NULL;
	next_2_free = NULL;
	free(list);
	list = NULL;
}

int SListIsEmpty(const list_t *list)
{
	return (list->head == list->tail);
}

size_t SListCount(const list_t *list)
{
	size_t count = 0;
	node_t *node_next = 0;

	assert(NULL != list);

	node_next = list->head;
	do
	{
		node_next = node_next->next_node;
		++count;
	}while(node_next);
	
	return count-1;
}

iter_t SListInsertBefore(list_t *list, iter_t iterator , void *data)
{
	node_t *old_node = 0;
	node_t *new_node = malloc(NODE_SIZE);
	if(NULL == new_node)
	{
		return list->tail;
	}
	old_node = iterator;

	new_node->data = old_node->data;
	new_node->next_node = old_node->next_node;
	
	old_node->data = data;
	old_node->next_node = new_node;
	
	if(NULL == new_node->next_node)
	{
		UpdateTail(list, new_node);
	}
	return old_node->next_node;
}

iter_t SListBegin(const list_t *list)
{
	return list->head;
}

iter_t SListEnd(const list_t *list)
{
	return list->tail;
}

static void UpdateTail(list_t *list, node_t *node)
{

	assert(NULL != list);
	assert(NULL != node);

	list->tail = node;
}

iter_t SListRemove(iter_t iterator)
{
	node_t *held_node = 0;
	node_t *remove_node = 0;

	assert(NULL != iterator);
	
	held_node = iterator;
	remove_node = held_node->next_node;
	
	held_node->data = remove_node->data;
	held_node->next_node = remove_node->next_node;

	free(remove_node);
	remove_node = NULL;
	
	return held_node->next_node;

}

void *SListGetData(iter_t iterator)
{
	node_t *node = 0;
	assert(NULL != iterator);
	node = iterator;
	return node->data;
}

void SListSetData(iter_t iterator, void *data)
{
	node_t *node = 0;
	assert(NULL != iterator);
	node = iterator;
	node->data = data;
}

int SListIsEqual(iter_t iterator1, iter_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return(iterator1 == iterator2);
}

iter_t SListNext(iter_t iterator)
{
	node_t *node = 0;
	assert(NULL != iterator);
	node = iterator;
	return node->next_node;
	
}

iter_t SListFind(iter_t from, iter_t to, compare_t compare , void* data)
{
	node_t *check_node = 0;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != compare);

	check_node = from;
	
	do
	{
		if(!(*compare)(data, check_node->data))
		{
			return check_node;
		}
		check_node = SListNext(check_node);
	}while(!SListIsEqual(check_node, to));

	return to;
}

int SListForEach(iter_t from, iter_t to, action_t action, void *param)
{
	node_t *node_from = 0;
	node_t *node_to = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);

	node_from = from;
	node_to = to;
	
	do
	{
		if((*action)(node_from->data, param))
		{
			return 1;
		}
		node_from = node_from->next_node;
	}while(!SListIsEqual(node_from, node_to));

	return 0;
}

list_t *SListAppend(list_t *dest, list_t *src)
{
	node_t dest_tail = 0;
	node_t src_head = 0;

	assert(NULL != dest);
	assert(NULL != src);

	dest_tail = SListEnd(dest);
	src_head = SlistBegin(src);

	dest_tail->data = src_head->data;
	dest_tail->next_node = SListRemove(src_head);
	
	dest->tail = src->tail;
	
	free(src);
	src = NULL;

	return dest;
}
