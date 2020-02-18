#include <stdlib.h> 	/*malloc*/
#include <assert.h>		/*assert*/
#include "dlist.h"

/******MACROS******/
#define NODE_SIZE				(sizeof(struct node))
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS AND STRUCTS******/
struct dlist
{
	iter_t head;
	iter_t tail;
};

typedef struct node
{
	void *data;
	iter_t next_node;
	iter_t prev_node;
}node_t;

/******INTERNAL FUNCTIONS AND GLOBAL VARIABLES******/
static void UpdateTail(dlist_t *list, node_t *node);
static node_t *CreateNode();

/******FUNCTIONS******/
static node_t *CreateNode()
{
	node_t *new_node = malloc(NODE_SIZE);

	return new_node;
}

dlist_t *DListCreate()
{
	dlist_t *new_list = NULL;
	node_t *head_node = CreateNode();
	node_t *tail_node = CreateNode();

	if(NULL == head_node)
	{
		free(tail_node);	
		return 0;
	}

	if(NULL == tail_node)
	{
		free(head_node);		
		return 0;
	}

	head_node->prev_node = NULL;
	head_node->next_node = tail_node;
	tail_node->next_node = NULL;
	tail_node->prev_node = head_node;

	new_list = malloc(sizeof(struct dlist));
	
	if(NULL == new_list)
	{
		free(head_node);
		free(tail_node);
		head_node = NULL;
		tail_node = NULL;
		return 0;
	}
	new_list->head = head_node;
	new_list->tail = tail_node;
	head_node->data = new_list;
	tail_node->data = new_list;

	return new_list;
}

void DListDestroy(dlist_t *list)
{
	node_t *free_node = NULL;
	node_t *next_2_free = NULL;
	
	ASSERT_NOT_NULL(list);

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

int DListIsEmpty(const dlist_t *list)
{
	node_t *head = NULL;
	node_t *tail = NULL;
	
	ASSERT_NOT_NULL(list);

	head = list->head;
	tail = list->tail;
	
	return (head->next_node == tail);
}

size_t DListSize(const dlist_t *list)
{
	size_t count = NULL;
	node_t *node_next = NULL;

	ASSERT_NOT_NULL(list);

	node_next = DListBegin(list);
	do
	{
		node_next = node_next->next_node;
		++count;
	}while(node_next);
	
	return count-1;
}

iter_t DListInsert(dlist_t *list, iter_t iterator , void *data)
{
	node_t *after_node = NULL;
	node_t *new_node = CreateNode();
	node_t *b4_old = NULL;

	ASSERT_NOT_NULL(list);
	ASSERT_NOT_NULL(iterator);

	if(NULL == new_node)
	{
		return list->tail;
	}

	after_node = iterator;
	b4_old = after_node->prev_node;
	
	new_node->data = data;
	new_node->next_node = after_node;
	new_node->prev_node = b4_old;
	
	after_node->prev_node = new_node;
	b4_old->next_node = new_node;

	if(NULL == new_node->next_node)
	{
		UpdateTail(list, new_node);
	}

	return b4_old->next_node;
}

iter_t DListBegin(const dlist_t *list)
{
	node_t *head_node = NULL;

	ASSERT_NOT_NULL(list);
	head_node = list->head;
	return head_node->next_node;
}

iter_t DListEnd(const dlist_t *list)
{
	ASSERT_NOT_NULL(list);
	return list->tail;
}

static void UpdateTail(dlist_t *list, node_t *node)
{

	ASSERT_NOT_NULL(list);
	ASSERT_NOT_NULL(node);

	list->tail = node;
}

iter_t DListRemove(iter_t iterator)
{
	node_t *b4_node = NULL;
	node_t *remove_node = NULL;
	node_t *after_node = NULL;

	ASSERT_NOT_NULL(iterator);
	
	remove_node = iterator;
	b4_node = remove_node->prev_node;
	after_node = remove_node->next_node;	

	b4_node->next_node = after_node;
	after_node->prev_node = b4_node;

	free(remove_node);
	remove_node = NULL;
	
	return b4_node->next_node;

}

void *DListGetData(iter_t iterator)
{
	node_t *node = NULL;
	ASSERT_NOT_NULL(iterator);
	node = iterator;
	return node->data;
}

int DListIsSame(iter_t iterator1, iter_t iterator2)
{
	ASSERT_NOT_NULL(iterator1);
	ASSERT_NOT_NULL(iterator2);
	return(iterator1 == iterator2);
}

iter_t DListNext(iter_t iterator)
{
	node_t *node = NULL;
	ASSERT_NOT_NULL(iterator);
	node = iterator;
	return node->next_node;
	
}

iter_t DListFind(iter_t from, iter_t to, compare_t compare , void* data)
{
	node_t *check_node = NULL;
	ASSERT_NOT_NULL(from);
	ASSERT_NOT_NULL(to);
	ASSERT_NOT_NULL(compare);
	check_node = from;
	
	do
	{
		if(!(*compare)(data, check_node->data))
		{
			return check_node;
		}
		check_node = DListNext(check_node);
	}while(!DListIsSame(check_node, to));

	return to;
}

int DListForEach(iter_t from, iter_t to, action_t action, void *param)
{
	node_t *node_from = NULL;
	node_t *node_to = NULL;
	
	ASSERT_NOT_NULL(from);
	ASSERT_NOT_NULL(to);
	ASSERT_NOT_NULL(action);

	node_from = from;
	node_to = to;
	
	do
	{
		if((*action)(node_from->data, param))
		{
			return 1;
		}
		node_from = node_from->next_node;
	}while(!DListIsSame(node_from, node_to));

	return 0;
}

iter_t DListPushFront(dlist_t *list, void *data)
{
	ASSERT_NOT_NULL(list);
	return DListInsert(list, DListBegin(list), data);
}

iter_t DListPushBack(dlist_t *list, void *data)
{
	ASSERT_NOT_NULL(list);
	return DListInsert(list, DListEnd(list), data);
}

void *DListPopFront(dlist_t *list)
{
	ASSERT_NOT_NULL(list);
	DListRemove(DListBegin(list));
	
	return 0;
}

void *DListPopBack(dlist_t *list)
{
	node_t *tail_node = NULL;
	node_t *remove_node = NULL;

	ASSERT_NOT_NULL(list);
	
	tail_node = DListEnd(list);
	remove_node = tail_node->prev_node;
	DListRemove(DListBegin(list));
	UpdateTail(list, remove_node);
	
	return 0;
}

iter_t DListSplice(iter_t from, iter_t to, iter_t where)
{
	node_t *from_node = NULL;
	node_t *to_node = NULL;
	node_t *where_node = NULL;
	node_t *b4_from = NULL;
	node_t *last_node = NULL;
	node_t *after_where = NULL;

	ASSERT_NOT_NULL(from);
	ASSERT_NOT_NULL(to);
	ASSERT_NOT_NULL(where);

	from_node = from;
	to_node  =to;
	where_node = where;
	
	last_node = to_node->prev_node;
	b4_from = from_node->prev_node;
	after_where = where_node->next_node;

	b4_from->next_node = to_node;
	to_node->prev_node = b4_from;

	where_node->next_node = from_node;
	from_node->prev_node = where_node;
	last_node->next_node = after_where;
	after_where->prev_node = last_node;

	return last_node;
}
