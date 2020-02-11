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

iter_t SListInsertBefore(iter_t iterator , void *data)
{
	node_t *old_node = 0;
	node_t *new_node = malloc(NODE_SIZE);
	if(NULL == new_node)
	{
		return 0;
	}
	old_node = iterator;

	new_node->data = old_node->data;
	new_node->next_node = old_node->next_node;
	
	old_node->data = data;
	old_node->next_node = new_node;
	
	if(NULL == new_node->next_node)
	{
		UpdateTail(new_node->data, new_node);
	}
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
