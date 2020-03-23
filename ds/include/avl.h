
#ifndef __OL85_AVL_H__
#define __OL85_AVL_H__

/*******************************************************************************
                                * OL85 API FOR AVL
                                * version 19.03.2020.0
******************************************************************************/

#include <stddef.h>	/* size_t */

/* returns 1 if first element is before second element, else 0 */
typedef int ( *is_before) (const void*, const void*);

typedef struct avl 
/*{
	is_before isbefore;			 PLEASE INSERT THIS IN YOUR C FILE
	avl_node_t *root;
} */avl_t;

typedef struct node
/*{
	void *data;				PLEASE INSERT THIS IN YOUR C FILE
	struct node *children[NUM_OF_CHILDREN];
	size_t node_height;
}*/ avl_node_t;

typedef enum order 
{
	PRE_ORDER,
	POST_ORDER,
	IN_ORDER
} traversal_order_t;


/*
* Input: pointer to the compare function used for sorting the AVL
          *Compare Function
          *Input: two pieces of information to be compared
          *Process: compares the two pieces of data
          *Return: The difference between the data.
          *
* Process: Create an AVL
* Returns: pointer to the AVL
*/
avl_t *AVLCreate(int(*is_before)(const void* data1, const void* data2));

/*
* Input: pointer to the AVL
* Process: free the AVL and all elements in it.
* Returns: none.
*/
void AVLDestroy(avl_t *btree);

/*
* Input: pointer to the AVL
* Process: traverse AVL and calculate number of nodes
* Returns: size of the tree
*/
size_t AVLSize(const avl_t *btree);

/*
* Input: pointer to the AVL
* Process: calculate height of the AVL
* Returns: height of the tree
*/
size_t AVLHeight(const avl_t *btree); 

/*
* Input: pointer to the AVL
* Process: check if node exist
* Returns: 1 if empty / 0 if not
*/
int AVLIsEmpty(const avl_t *btree);

/*
* Input: pointer to AVL, pointer to data
* Process: traverse tree to find position for new node
* based upon the data
* Returns: 0 if successful / 1 if failed
*/
int AVLInsert(avl_t *btree, void *data);

/*
* Input: Pointer to AVL and data
* Process: free data in the given iterator
* Returns: none
*/
void AVLRemove(avl_t *btree, void *data);

/*
* Input:  Pointer to the AVL, pointer to key.
* Process: Traverse tree looking for desired data
* Returns: data if successful / NULL if failed
*/
void *AVLFind(avl_t *btree, void *to_find);

/*
* Input: Pointer to AVL , pointer to action function that
* performs actions with the elements of AVL, pointer to parameter
* for function, pre/in/post order traversal.
        *Action Function
        *Input: the data to be acted upon, the data that is acting
        *Process: Perform the desired action using the provided data
        *Return: 0 if success, all other values indicate failure
        *
* Will not support change in data
* Process: Perform actions with the elements of AVL using the traversal
* Return: 0 if action was successful, other values from user function if failed
*/
int AVLForEach(avl_t *btree, int (*action)(void* data, void* param), void* param,
							traversal_order_t order);



#endif /* __OL85_AVL_H__ */

