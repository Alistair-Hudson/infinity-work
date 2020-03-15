/******************************************************************************
 *	Title:		Binary Search Tree
 *	Authour:	Alistair Hudson
 *	Reviewer:	Dmitry
 *	Version:	15.03.2020.0
 ******************************************************************************/
#include <stdio.h>		/*TODO*/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "bst.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define END						(~0)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
enum DIRECTION{LEFT, RIGHT, NUM_CHILDREN};

struct node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_CHILDREN];
};

struct btree
{
	bst_node_t *stub;
	int (*compare)(const void*, const void*);
};

static bst_node_t *CreateNewNode(bst_node_t *parent, void *data);

static int DirectionCheck(bst_t *btree, bst_iter_t parent, const void *data);

static bst_iter_t ClimbUpTree(bst_iter_t start, enum DIRECTION direction);

static bst_iter_t ClimbDownTree(bst_iter_t start, enum DIRECTION direction);

static int IsEndNext(bst_iter_t iter, enum DIRECTION direction);

static void RemoveLeaf(bst_iter_t iter);

static void RemoveEnd(bst_iter_t iter);

static void RemoveSubtree(bst_iter_t iter);

/******FUNCTIONS******/
bst_t *BSTCreate(int(*cmp_funct)(const void* data1, const void* data2))
{
	bst_t *new_bst = NULL;

	ASSERT_NOT_NULL(cmp_funct);

	new_bst = (bst_t*)malloc(sizeof(struct btree));
	if (NULL == new_bst)
	{
		return NULL;
	}

	new_bst->stub = CreateNewNode(NULL, NULL);
	new_bst->compare = cmp_funct;

	return new_bst;
}

void BSTDestroy(bst_t *btree)
{
	bst_iter_t to_remove;
	bst_iter_t next_node;
	
	ASSERT_NOT_NULL(btree);

	to_remove = BSTBegin(btree);
	while (NULL != to_remove.bst_node->parent)
	{
		if (NULL != to_remove.bst_node->children[LEFT])
		{
			to_remove.bst_node = to_remove.bst_node->children[LEFT];
		}
		else if (NULL != to_remove.bst_node->children[RIGHT]
												&& !IsEndNext(to_remove, RIGHT))
		{
			to_remove.bst_node = to_remove.bst_node->children[RIGHT];
		}
		else
		{
			next_node.bst_node = to_remove.bst_node->parent;
			BSTRemove(to_remove);
			to_remove.bst_node = next_node.bst_node;
		}
	}
	free(btree->stub);
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
	bst_node_t *new_node = NULL;
	bst_node_t *append_end = NULL;
	enum DIRECTION direction = LEFT;

	ASSERT_NOT_NULL(btree);

	current_parent.bst_node = btree->stub;

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
		current_parent.bst_node = current_parent.bst_node->children[direction];
		if (0 == btree->compare(BSTGetData(current_parent), data))
		{
			return BSTEnd(btree);
		}
		direction = DirectionCheck(btree, current_parent, data);
		
	}while (NULL != current_parent.bst_node->children[direction] 
									&& !IsEndNext(current_parent, direction));
	
	append_end = current_parent.bst_node->children[direction];

	new_node = CreateNewNode(current_parent.bst_node, data);
	if (NULL == new_node)
	{
		return BSTEnd(btree);
	}
	
	current_parent.bst_node->children[direction] = new_node;
	new_node->children[direction] = append_end;

	current_parent.bst_node = new_node;
	return current_parent;
}

void BSTRemove(bst_iter_t iter)
{

	if (NULL == iter.bst_node->children[LEFT] 
									&&	NULL == iter.bst_node->children[RIGHT])
	{
		RemoveLeaf(iter);
		return;
	}
	
	if (IsEndNext(iter, RIGHT))
	{
		RemoveEnd(iter);
		return;
	}

	if (NULL != iter.bst_node->children[LEFT] 
									||	NULL != iter.bst_node->children[RIGHT])
	{
		RemoveSubtree(iter);
		return;
	}
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
	if (NULL == iter.bst_node->parent->parent)
	{
		iter.bst_node = iter.bst_node->parent;
		return iter;
	}
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
	else if (NULL == iter.bst_node->children[RIGHT]->parent)
	{
		iter.bst_node = iter.bst_node->children[RIGHT];
		return iter;
	}	
	return ClimbDownTree(iter, LEFT);
	
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	if (NULL == iter1.bst_node || NULL == iter2.bst_node)
	{
		return 0;
	}
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
								&& (*search)(BSTGetData(current_node), to_find))
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
		status = (*action)(BSTGetData(current_node), param);
		current_node = BSTNext(current_node);
	}

	return status;
}

bst_iter_t BSTGet(bst_t *btree, const void *data)
{
	bst_iter_t current_parent;
	enum DIRECTION direction = LEFT;

	ASSERT_NOT_NULL(btree);

	current_parent.bst_node = btree->stub;

	if (BSTIsEmpty(btree))
	{
		return current_parent;
	}

	do
	{	
		current_parent.bst_node = current_parent.bst_node->children[direction];
		if (0 == btree->compare(BSTGetData(current_parent), data))
		{
			return current_parent;
		}
		direction = DirectionCheck(btree, current_parent, data);
		
	}while (NULL != current_parent.bst_node->children[direction] 
									&& !IsEndNext(current_parent, direction));
	
	return BSTEnd(btree);
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

static int DirectionCheck(bst_t *btree, bst_iter_t parent, const void *data)
{
	if (0 < btree->compare(BSTGetData(parent), data))
	{
		return LEFT;
	}
	
	return RIGHT;
}

static bst_iter_t ClimbUpTree(bst_iter_t start, enum DIRECTION direction)
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

static bst_iter_t ClimbDownTree(bst_iter_t start, enum DIRECTION direction)
{
	start.bst_node = start.bst_node->children[-(direction - 1)];
	
	while (NULL != start.bst_node->children[direction])
	{
		start.bst_node = start.bst_node->children[direction];
	}
	return start;
}

static int IsEndNext(bst_iter_t iter, enum DIRECTION direction)
{
	if (NULL == iter.bst_node->children[direction])
	{
		return 0;
	}
	
	if (NULL != iter.bst_node->children[direction]->parent)
	{
		return 0;
	}
	
	return 1;
}

static void RemoveLeaf(bst_iter_t iter)
{
	bst_iter_t parent;
	enum DIRECTION direction = LEFT;
	bst_iter_t check_child;

	parent.bst_node = iter.bst_node->parent;
	check_child.bst_node = parent.bst_node->children[direction];

	if (!BSTIterIsEqual(check_child, iter))
	{
		direction = RIGHT;
	}
	
	parent.bst_node->children[direction] = NULL;

	free(iter.bst_node);
}

static void RemoveEnd(bst_iter_t iter)
{
	bst_node_t *parent = iter.bst_node->parent;
	if (NULL == iter.bst_node->children[LEFT])
	{
		parent->children[RIGHT] = iter.bst_node->children[RIGHT];
	}
	else
	{
		parent->children[RIGHT] = iter.bst_node->children[LEFT];
		while (NULL != parent->children[RIGHT])
		{
			parent = parent->children[RIGHT];
		}
		parent->children[RIGHT] = iter.bst_node->children[RIGHT];
	}
	free(iter.bst_node);
}

static void RemoveSubtree(bst_iter_t iter)
{
	bst_iter_t parent;
	enum DIRECTION direction = LEFT;
	bst_iter_t check_child;

	parent.bst_node = iter.bst_node->parent;
	check_child.bst_node = parent.bst_node->children[direction];

	if (!BSTIterIsEqual(check_child, iter))
	{
		direction = RIGHT;
	}

	if (NULL == iter.bst_node->children[LEFT])
	{
		parent.bst_node->children[direction] = iter.bst_node->children[RIGHT];
	}
	else
	{
		parent.bst_node->children[direction] = iter.bst_node->children[LEFT];
		parent.bst_node = iter.bst_node->children[LEFT];

		while (NULL != parent.bst_node->children[RIGHT])
		{
			parent.bst_node = parent.bst_node->children[RIGHT];
		}
		parent.bst_node->children[RIGHT] = iter.bst_node->children[RIGHT];
	}
	free(iter.bst_node);
}












