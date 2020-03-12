/******************************************************************************
 *	Title:		Binary Search Tree
 *	Authour:	Alistair Hudson
 *	Reviewer:	Dmitry
 *	Version:	10.03.2020.0
 ******************************************************************************/
#include <stdio.h>		/*TODO*/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "bst.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define END						(~0)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
enum {LEFT, RIGHT, NUM_CHILDREN};

typedef struct node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_CHILDREN];
};

struct btree
{
	bst_node_t *stub;
	int (*compare)(void*, void*);
};

static bst_node_t *CreateNewNode(bst_node_t *parent, void *data);

static int DirectionCheck(bst_t *btree, bst_iter_t parent, void *data);

static void ReorganiseNodes(bst_iter_t to_remove, bst_iter_t to_hold, 
																int direction);

static bst_iter_t ClimbUpTree(bst_iter_t start, int direction);

static bst_iter_t ClimbDownTree(bst_iter_t start, int direction);

/******FUNCTIONS******/
bst_t *BSTCreate(int(*cmp_funct)(void* data1, void* data2))
{
	bst_t *new_bst = NULL;

	ASSERT_NOT_NULL(cmp_funct);

	new_bst = (bst_t*)malloc(sizeof(struct btree));
	if (NULL == new_bst)
	{
		return NULL;
	}

	new_bst->stub = CreateNewNode(NULL, (void*)END);
	new_bst->compare = cmp_funct;

	return new_bst;
}

void BSTDestroy(bst_t *btree)
{
	bst_iter_t to_remove;
	bst_iter_t next_node;

	ASSERT_NOT_NULL(btree);

	to_remove = BSTBegin(btree);
	do
	{
		next_node = BSTNext(to_remove);
		BSTRemove(to_remove);
		to_remove = next_node;
	}while (END != *(int*)BSTGetData(to_remove));

	BSTRemove(to_remove);
	
	free(btree);
	btree = NULL;
}

size_t BSTSize(const bst_t *btree)
{
	size_t count = 0;
	bst_iter_t current_node;

	ASSERT_NOT_NULL(btree);

	current_node = BSTBegin(btree);

	while (!BSTIterIsEqual(current_node, BSTEnd(btree)))
	{
		++count;
		current_node = BSTNext(current_node);
	}

	return count;
}

int BSTIsEmpty(const bst_t *btree)
{
	bst_node_t *stub = NULL;

	ASSERT_NOT_NULL(btree);

	stub = btree->stub;

	return (NULL == stub->children[LEFT]);
}

bst_iter_t BSTInsert(bst_t *btree, void *data)
{
	bst_iter_t current_parent;
	bst_iter_t next_node;
	bst_node_t *append_end = NULL;
	int direction = 0;

	ASSERT_NOT_NULL(btree);

	current_parent.bst_node = (bst_node_t*)btree->stub;
	next_node.bst_node = current_parent.bst_node->children[direction];

	if (BSTIsEmpty(btree))
	{
		current_parent.bst_node->children[LEFT] = 
								CreateNewNode(current_parent.bst_node, data);
		if (NULL == current_parent.bst_node->children[direction])
		{
			return current_parent;
		}
		current_parent.bst_node->children[LEFT]->children[RIGHT] = 
													current_parent.bst_node;
		current_parent.bst_node = current_parent.bst_node->children[LEFT];
		return current_parent;
	}


	do
	{
		current_parent.bst_node = next_node.bst_node;
		if (0 == btree->compare(BSTGetData(current_parent), data))
		{
			return BSTEnd(btree);
		}
		direction = DirectionCheck(btree, current_parent, data);
		next_node.bst_node = current_parent.bst_node->children[direction];
	}while (NULL != current_parent.bst_node->children[direction] 
			|| END != *(int*)BSTGetData(next_node));
	
	append_end = current_parent.bst_node->children[direction];

	current_parent.bst_node->children[direction] = 	
								CreateNewNode(current_parent.bst_node, data);
	if (NULL == current_parent.bst_node->children[direction])
	{
		return BSTEnd(btree);
	}

	current_parent.bst_node->children[direction]->children[direction] = 
																	append_end;
	current_parent.bst_node = current_parent.bst_node->children[direction];
	return current_parent;
}

void BSTRemove(bst_iter_t iter)
{
	bst_iter_t to_remove;
	bst_iter_t node;
	bst_iter_t to_hold;
	bst_iter_t parent;
	int direction = 0;
	
	node = iter;
	to_hold.bst_node = node.bst_node->children[RIGHT];
	to_remove.bst_node = node.bst_node->children[LEFT];
	parent.bst_node = node.bst_node->parent;

	if (BSTGetData(to_remove) < BSTGetData(parent))
	{
		direction = 1;
		to_hold.bst_node = node.bst_node->children[LEFT];
		to_remove.bst_node = node.bst_node->children[RIGHT];
	}

	ReorganiseNodes(to_remove, to_hold, direction);

	node.bst_node->data = to_remove.bst_node->data;
	node.bst_node->children[LEFT] = to_remove.bst_node->children[LEFT];
	node.bst_node->children[RIGHT] = to_remove.bst_node->children[RIGHT];

	free(to_remove.bst_node);
	to_remove.bst_node = NULL;
}

bst_iter_t BSTBegin(const bst_t *btree)
{
	bst_iter_t checked_node;

	ASSERT_NOT_NULL(btree);

	if (BSTIsEmpty(btree))
	{
		checked_node.bst_node = btree->stub;
		return checked_node;
	}

	checked_node.bst_node = btree->stub->children[LEFT];
	while (NULL != checked_node.bst_node->children[LEFT])
	{
		checked_node.bst_node = checked_node.bst_node->children[LEFT];
	}

	return checked_node;
}

bst_iter_t BSTEnd(const bst_t *btree)
{
	bst_iter_t checked_node;

	ASSERT_NOT_NULL(btree);

	checked_node.bst_node = btree->stub;

	return checked_node;
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	if (NULL == iter.bst_node->children[LEFT])
	{
		return ClimbUpTree(iter, RIGHT);
	}
	
	return ClimbDownTree(iter, RIGHT);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	if (NULL == iter.bst_node->children[RIGHT])
	{
		return ClimbUpTree(iter, LEFT);
	}
	
	return ClimbDownTree(iter, LEFT);
	
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return (iter1.bst_node == iter2.bst_node);
}

void *BSTGetData(bst_iter_t iter)
{
	return iter.bst_node->data;
}

bst_iter_t BSTFind(bst_t *btree, int(*search)(void* data, void* to_find),
                    											void *to_find)
{
	bst_iter_t current_node;

	ASSERT_NOT_NULL(btree);

	current_node = BSTBegin(btree);

	while (!BSTIterIsEqual(current_node, BSTEnd(btree)) 
								&& search(BSTGetData(current_node), to_find))
	{
		current_node = BSTNext(current_node);
	}

	return current_node;
}

int BSTForEach(bst_iter_t from, bst_iter_t to, int (*action)(void*, void*), 
																	void* param)
{
	bst_iter_t current_node;
	int status = 0;

	current_node = from;

	while (!BSTIterIsEqual(current_node, to) && !status)
	{
		status = action(BSTGetData(current_node), param);
		current_node = BSTNext(current_node);
	}

	return status;
}

static bst_node_t *CreateNewNode(bst_node_t *parent, void *data)
{
	bst_node_t *new_node = NULL;

	new_node = (bst_node_t*)malloc(sizeof(struct node));
	if (NULL == new_node)
	{
		return NULL;
	}

	new_node->data = data;
	new_node->parent = parent;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;

	return new_node;
}

static int DirectionCheck(bst_t *btree, bst_iter_t parent, void *data)
{
	if (0 > btree->compare(BSTGetData(parent), data))
	{
		return LEFT;
	}
	
	return RIGHT;
}

static void ReorganiseNodes(bst_iter_t to_remove, bst_iter_t to_hold, 
																int direction)
{
	while (NULL != to_remove.bst_node->children[direction])
	{
		to_remove.bst_node = to_remove.bst_node->children[direction];
	}

	to_remove.bst_node->children[direction] = to_hold.bst_node;
}

static bst_iter_t ClimbUpTree(bst_iter_t start, int direction)
{
	bst_iter_t parent;
	bst_iter_t parent_direct;

	parent.bst_node = start.bst_node->parent;
	parent_direct.bst_node = parent.bst_node->children[direction];

	while (!BSTIterIsEqual(start, parent_direct))
	{
		start.bst_node = parent.bst_node;
		parent.bst_node = parent.bst_node->parent;
		parent_direct.bst_node = parent.bst_node->children[direction];
	}
	return parent;
}

static bst_iter_t ClimbDownTree(bst_iter_t start, int direction)
{
	start.bst_node = start.bst_node->children[-(direction - 1)];

	while (NULL != start.bst_node->children[direction])
	{
		start.bst_node = start.bst_node->children[direction];
	}
	return start;
}








