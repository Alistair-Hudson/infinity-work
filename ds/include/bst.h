
#ifndef __OL85_BINARY_TREE_H__
#define __OL85_BINARY_TREE_H__

/*******************************************************************************
                                * OL85 API FOR BINARY SEARCH TREE
                                * version 11.03.2020.0
******************************************************************************/

typedef struct btree bst_t;
typedef struct node bst_node_t;

typedef struct iter
{
    bst_node_t* bst_node;
}bst_iter_t;


/*
* Input: pointer to the compare function used for sorting the binary tree
          *Compare Function
          *Input: two pieces of information to be comapared
          *Process: compares the two pieces of data
          *Return: The difference betweeen the data.
          *
* Process: Create a binary tree
* Returns: pointer to the binary tree
*/
bst_t *BSTCreate(int(*cmp_funct)(const void* data1, const void* data2));

/*
* Input: pointer to the binary tree
* Process: free the binary tree and all elements in it.
* Returns: none.
*/
void BSTDestroy(bst_t *btree);

/*
* Input: pointer to the binary tree
* Process: traverse binary tree and calculate number of nodes
* Returns: size of the tree
*/
size_t BSTSize(const bst_t *btree);

/*
* Input: pointer to the binary tree
* Process: check if node exist
* Returns: 1 if empty/ 0 if not
*/
int BSTIsEmpty(const bst_t *btree);

/*
* Input: pointer to binary tree, pointer to data
* Process: traverse tree to find position for new node
* based upon the data
* Returns: valid iter if successful / iter to the end  if failed
*/
bst_iter_t BSTInsert(bst_t *btree, void *data);

/*
* Input: Iterator (bst_iter_t)
* Process: free the given iterator
* Returns: none
*/
void BSTRemove(bst_iter_t iter);

/*
* Input: pointer to binary tree
* Process: find node with the smallest data
* Returns: iterator to the first element in the binary
* tree
*/
bst_iter_t BSTBegin(const bst_t *btree);

/*
* Input: pointer to binary tree
* Process: find node with the biggest data
* Returns: iterator to the last element in the binary
* tree
*/
bst_iter_t BSTEnd(const bst_t *btree);

/*
* Input:  Iterator (bst_iter_t)
* Process: find node with the closest smallest data to
* given iterator.
* Return: pointer to previous node
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*
* Input:  Iterator (bst_iter_t)
* Process: find node with the closest biggest data to
* given iterator.
* Return: pointer to next node
*/
bst_iter_t BSTNext(bst_iter_t iter);

/*
* Input:  Iterator1 (bst_iter_t), iterator2 (bst_iter_t)
* Process: Compare 2 iterators
* Return: 1 if nodes are equal/ 0 if not
*/
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/*
* Input:  iterator (bst_iter_t)
* Process: Obtain data stored in iterator
* Return: pointer to the data
*/
void *BSTGetData(bst_iter_t iter);

/*
* Input:  Pointer to the binary tree, pointer to search function that
* compare key with the elements in the binary tree, pointer to key.
        * Search Function
        * Input: two pieces of information to be comapared
        * Process: compares the two pieces of data
        * Return: The difference betweeen the data.
        *
* Process: Traverse tree looking for desired data
* Returns: valid iter if successful / iter to the end  if failed
*/
bst_iter_t BSTFind(bst_t *btree, int(*search)(void* data, void* to_find),
                    											void *to_find);

/*
* Input: Iter from, iter to, pointer to action function that
* performs actions with the elements of binary tree, pointer to parameter
* for function.
        *Action Function
        *Input: the data to be acted upon, the data that is acting
        *Process: Perform the desired action using the provided data
        *Return: 0 if success, all other values indicate failure
        *
* Process: Perform actions with the elements of binary tree in from(included)
* to to(exluded)
* Return: 0 if action was successful, other values from user function if failed
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, 
									int (*action)(void*, void*), void* param);

/*
 *Input: bst to get from, data to look for
 *Process: searches the tree for the data in O(log(n))
 *Return: the iterator that meets the exact data, end if the data doesn't exist
 */
bst_iter_t BSTGet(bst_t *btree, const void *data);

#endif /* __OL85_BINARY_TREE_H__ */

