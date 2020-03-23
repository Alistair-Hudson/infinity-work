/******************************************************************************
 *	Title:		AVL Tree
 *	Authour:	Alistair Hudson
 *	Reviewer:	Yurri
 *	Version:	22.03.2020.0
 ******************************************************************************/
#include <stdio.h>		/*TODO*/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "avl.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
enum DIRECTION{LEFT, RIGHT, NUM_CHILDREN};

struct node
{
	void *data;
	size_t height;
	avl_node_t *children[NUM_CHILDREN];
};

struct avl
{
	avl_node_t *root;
	int (*compare)(const void*, const void*);
};

static int Balance(avl_node_t* node);

static size_t NodeHeight(avl_node_t* node);

static size_t MaxHeight(size_t height1, size_t height2);

static size_t SizeSupport(avl_node_t* node);

static void* FindSupport(avl_node_t* node, void* to_find, 
						int(*is_before)(const void* data1, const void* data2));

static int PreOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param);

static int InOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param);

static int PostOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param);

static avl_node_t* InsertNode(avl_node_t* node, void* data, 
						int(*is_before)(const void* data1, const void* data2));

static avl_node_t* CreateNewNode(void* data);

static avl_node_t* RemoveNode(avl_node_t *node, void* data, 
						int(*is_before)(const void* data1, const void* data2));

static avl_node_t* FindSmallestNode(avl_node_t* node);

static avl_node_t* RightRotate(avl_node_t* node);

static avl_node_t* LeftRotate(avl_node_t* node);

static void DestroySupport(avl_node_t* node);

/******FUNCTIONS******/
static int Balance(avl_node_t* node)
{
	if(NULL == node)
	{
		return 0;
	}
	return NodeHeight(node->children[LEFT]) - NodeHeight(node->children[RIGHT]);	
}

static avl_node_t* RightRotate(avl_node_t* node)
{
	avl_node_t* left_node = node->children[LEFT];
	avl_node_t* right_node = node->children[RIGHT];

	left_node->children[RIGHT] = node;
	node->children[LEFT] = right_node;

	node->height = 1 + MaxHeight(NodeHeight(node->children[LEFT]), 
								NodeHeight(node->children[RIGHT]));
	left_node->height = 1 + MaxHeight(NodeHeight(left_node->children[LEFT]), 
									NodeHeight(left_node->children[RIGHT]));

	return left_node;
}

static avl_node_t* LeftRotate(avl_node_t* node)
{
	avl_node_t* left_node = node->children[LEFT];
	avl_node_t* right_node = node->children[RIGHT];

	right_node->children[LEFT] = node;
	node->children[RIGHT] = left_node;

	node->height = 1 + MaxHeight(NodeHeight(node->children[LEFT]), 
								NodeHeight(node->children[RIGHT]));
	right_node->height = 1 + MaxHeight(NodeHeight(right_node->children[LEFT]), 
									NodeHeight(right_node->children[RIGHT]));

	return right_node;

}

static int PreOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param)
{
	if (NULL != node)
	{
		action(node->data, param);
		PreOrder(node->children[LEFT], action, param);
		PreOrder(node->children[RIGHT], action, param);
	}
	return 0;
}
static int InOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param)
{
	if (NULL != node)
	{
		InOrder(node->children[LEFT], action, param);
		action(node->data, param);
		InOrder(node->children[RIGHT], action, param);
	}
	return 0;
}

static int PostOrder(avl_node_t* node, 
							int (*action)(void* data, void* param), 
							void* param)
{
	if (NULL != node)
	{
		PostOrder(node->children[LEFT], action, param);
		PostOrder(node->children[RIGHT], action, param);
		action(node->data, param);
	}
	return 0;
}

static size_t SizeSupport(avl_node_t* node)
{
	size_t size = 0;

	if (NULL == node)
	{
		return 0;
	}
	if (NULL != node->children[LEFT])
	{
		size += SizeSupport(node->children[LEFT]);
	}
	if (NULL != node->children[RIGHT])
	{
		size += SizeSupport(node->children[RIGHT]);
	}
	return ++size;
}

static void DestroySupport(avl_node_t* node)
{
	if (NULL != node->children[LEFT])
	{
		DestroySupport(node->children[LEFT]);
	}
	if (NULL != node->children[RIGHT])
	{
		DestroySupport(node->children[RIGHT]);
	}
	free(node);
}

avl_node_t* FindSmallestNode(avl_node_t* node)
{
	if (NULL == node->children[LEFT])
	{
		return node;
	}
	return FindSmallestNode(node->children[LEFT]);
}

avl_node_t* RemoveNode(avl_node_t *node, void* data, 
						int(*is_before)(const void* data1, const void* data2))
{
	if (NULL == node)
	{
		return node;
	}
	if (is_before(node->data, data))
	{
		node->children[LEFT] = RemoveNode(node->children[LEFT], 
															data, is_before);
	}
	else if (!is_before(data, node->data))
	{
		if (is_before(data, node->data) == is_before(data, node->data))
		{
			if (NULL == node->children[LEFT] || NULL == node->children[RIGHT])
			{
				avl_node_t* temp = node->children[LEFT] ? node->children[LEFT]:
														node->children[RIGHT];
				
				if (NULL == temp)
				{
					temp = node;
					node = NULL;
				}
				else
				{
					*node = *temp;
					free(temp);
				}
			}
			else
			{
				avl_node_t* temp = FindSmallestNode(node->children[RIGHT]);
				temp->data = node->data;
				node->children[RIGHT] = RemoveNode(node->children[RIGHT], data, 
																	is_before);
			}
			
			if (NULL == node)
			{
				return node;
			}
		}
		node->children[RIGHT] = RemoveNode(node->children[RIGHT], 
															data, is_before);
	}
	node->height = 1 + MaxHeight(NodeHeight(node->children[LEFT]),
											NodeHeight(node->children[RIGHT]));

	if (Balance(node) > 1 && Balance(node->children[LEFT]) >= 0)
	{
		return RightRotate(node);
	}

	if (Balance(node) < -1 && Balance(node->children[RIGHT]) <= 0)
	{
		return LeftRotate(node);
	}
	if (Balance(node) > 1 && Balance(node->children[LEFT]) < 0)
	{
		node->children[LEFT] = LeftRotate(node->children[LEFT]);
		return RightRotate(node);
	}

	if (Balance(node) < -1 && Balance(node->children[RIGHT]) > 0)
	{	
		node->children[RIGHT] = RightRotate(node->children[RIGHT]);
		return LeftRotate(node);
	}

	return node;
}

static void* FindSupport(avl_node_t* node, void* to_find, 
						int(*is_before)(const void* data1, const void* data2))
{
	if (NULL == node)
	{
		return NULL;
	}
	if (is_before(to_find, node->data))
	{
		return FindSupport(node->children[LEFT], to_find, is_before);
	}
	else if (!is_before(to_find, node->data))
	{
		if (is_before(node->data, to_find) == is_before(to_find, node->data))
		{
			return node->data;
		}
		return FindSupport(node->children[RIGHT], to_find, is_before);
	}
	return NULL;
}

static size_t MaxHeight(size_t height1, size_t height2)
{
	return (height1 > height2)? height1 : height2;
}

static avl_node_t* CreateNewNode(void* data)
{
	avl_node_t* new_node = (avl_node_t*)malloc(sizeof(struct node));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->height = 0;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;

	return new_node;
	
}

static avl_node_t* InsertNode(avl_node_t* node, void* data, 
						int(*is_before)(const void* data1, const void* data2))
{
	if (NULL == node)
	{
		return CreateNewNode(data);
	}
	if (is_before(data, node->data))
	{
		node->children[LEFT] = InsertNode(node->children[LEFT], 
															data, is_before);
	}
	else if (!is_before(data, node->data))
	{
		if (is_before(node->data, data) == is_before(data, node->data))
		{
			return node;
		}
		node->children[RIGHT] = InsertNode(node->children[RIGHT], 
															data, is_before);
	}
	node->height = 1 + MaxHeight(NodeHeight(node->children[LEFT]),
											NodeHeight(node->children[RIGHT]));
/*
	if (Balance(node) > 1 && is_before(data, node->children[LEFT]->data))
	{
		return RightRotate(node);
	}

	if (Balance(node) < -1 && !is_before(data, node->children[RIGHT]->data))
	{
		return LeftRotate(node);
	}
	if (Balance(node) > 1 && !is_before(data, node->children[LEFT]->data))
	{
		node->children[LEFT] = LeftRotate(node->children[LEFT]);
		return RightRotate(node);
	}

	if (Balance(node) < -1 && is_before(data, node->children[RIGHT]->data))
	{	
		node->children[RIGHT] = RightRotate(node->children[RIGHT]);
		return LeftRotate(node);
	}
*/
	return node;
}

static size_t NodeHeight(avl_node_t* node)
{
	if (NULL == node)
	{
		return 0;
	}
	return node->height;
}

avl_t *AVLCreate(int(*is_before)(const void* data1, const void* data2))
{
	avl_t* new_avl = NULL;

	ASSERT_NOT_NULL(is_before);

	new_avl = (avl_t*)malloc(sizeof(struct avl));
	if (NULL == new_avl)
	{
		return NULL;
	}

	new_avl->compare = is_before;
	new_avl->root = NULL;

	return new_avl;
}

void AVLDestroy(avl_t *btree)
{
	if (NULL != btree->root)
	{
		DestroySupport(btree->root);
	}
	free(btree);
}

size_t AVLSize(const avl_t *btree)
{
	return SizeSupport(btree->root);
}

size_t AVLHeight(const avl_t *btree)
{
	return NodeHeight(btree->root);
}

int AVLIsEmpty(const avl_t *btree)
{
	return (NULL == btree->root);
}

int AVLInsert(avl_t *btree, void *data)
{
	btree->root = InsertNode(btree->root, data, btree->compare);
	return 0;
}

void AVLRemove(avl_t *btree, void *data)
{
	RemoveNode(btree->root, data, btree->compare);
}

void *AVLFind(avl_t *btree, void *to_find)
{
	return FindSupport(btree->root, to_find, btree->compare);
}


int AVLForEach(avl_t *btree, int (*action)(void* data, void* param), void* param,
													traversal_order_t order)
{
	if (PRE_ORDER == order)
	{
		return PreOrder(btree->root, action, param);
	}
	if (IN_ORDER == order)
	{
		return InOrder(btree->root, action, param);
	}
	if (POST_ORDER == order)
	{
		return PostOrder(btree->root, action, param);
	}
	return 1;
}








