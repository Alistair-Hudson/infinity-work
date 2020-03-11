
#ifndef __OL85_BINARY_TREE_H__
#define __OL85_BINARY_TREE_H__

/*******************************************************************************
                                 *  OL85 API FOR BINARY TREE
                                 * version 10.03.2020.0
 ******************************************************************************/

typedef struct btree btree_t;
typedef iter iter_t;

/*
 *Input: two pieces of information  to be comapared
 *Process: compares the two pieces of data
 *Return: The difference betweeen the data
 */
typedef (int)(*cmp_funct)(void*, void*);

/*
 *Input: the data to be acted upon, the data that is acting
 *Process: Perform the desired action using the provided data
 *Return: 0 if success, all other values indicate failure
 */
typedef (int)(*action)(void*, void*);

/*
 * Input: pointer to the compare function used for sorting the binary tree
 * Process: Create a binary tree
 * Returns: pointer to the binary tree
 */
btree_t *BTreeCreate(cmp_funct comparison);

/*
 * Input: pointer to the binary tree
 * Process: free the binary tree and all elements in it.
 * Returns: none.
 */
void BTreeDestroy(btree_t *btree);

/*
 * Input: pointer to the binary tree
 * Process: traverse binary tree and calculate number of nodes 
 * Returns: size of the tree
 */
size_t BTreeSize(const btree_t *btree);

/*
 * Input: pointer to the binary tree
 * Process: check if node exist
 * Returns: 1 if empty/ 0 if not
 */
int BTreeIsEmpty(const btree_t *btree);

/*
 * Input: pointer to data 
 * Process: traverse tree to find position for new node
 * based upon the data
 * Returns: 0 successful / 1 if failed
 */
int BTreeInsert(btree_t *btree, void *data);

/*
 * Input: iterartor to data to be removed
 * Process: free data in the given iterator
 * Returns: none
 */
void BTreeRemove(iter_t iter);

/*
 * Input: pointer to binary tree 
 * Process: find node with the smallest data
 * Returns: iterator to the first element in the binary 
 * tree
 */
iter_t BTreeBegin(btree_t *btree);

/*
 * Input: pointer to binary tree 
 * Process: find node with the biggest data
 * Returns: iterator to the last element in the binary 
 * tree
 */
iter_t BTreeEnd(btree_t *btree);

/*
 * Input:  Pointer to iterator
 * Process: find node with the closest smallest data to
 * given iterator.
 * Return: pointer to previous node
 */
iter_t BTreePrev(iter_t iter);

/*
 * Input:  Pointer to iterator
 * Process: find node with the closest biggest data to
 * given iterator.
 * Return: pointer to next node
 */
iter_t BTreeNext(iter_t iter);

/*
 * Input:  Pointer to iterator1, pointer to iterator2
 * Process: Compare 2 iterators
 * Return: 1 if nodes are equal/ 0 if not
 */
int BTreeIterIsEqual(iter_t iter1, iter_t iter2);

/*
 * Input:  Pointer to iterator
 * Process: Obtain data stored in iterator 
 * Return: pointer to the data 
 */
void *BTreeGetData(iter_t iter);

/*
 * Input:  Pointer to the binary tree, pointer to search function that 
 * compare key with the elements in the binary tree, pointer to key. 
 * Process: Traverse tree looking for desired data
 * Return: pointer to data stored in the node found
 */
iter_t BTreeFind(btree_t *btree, int *search(void*)(void*), void *key);

/*
 * Input:  Pointer to the binary tree, pointer to action function that 
 * performs actions with the elements of binary tree, pointer to parameter 
 * for function. 
 * Process: Perform actions with the elements of binary tree
 * Return: 0 if action was succesfull, other values if failed
 */
int BTForEach(btree_t *btree, int *action(void*)(void), void* param); 


#endif /* __OL85_BINARY_TREE_H__ */
