#ifndef __DLIST_H__
#define __DLIST_H__

/*******************************************************************************
                                 *  OL85 API
                                 * version 1.0
 ******************************************************************************/

#include<stddef.h> /* size_t */

typedef struct dlist dlist_t;
typedef void * iter_t;
/*
*Compare function
*Input : two void pointers:
 first - data from node of the dlist, second - compare data
 Return :"0" - if successful , difference if not equal.
*/
typedef int (* compare_t)(void* data, void *key);
/*
*Action function
*Input : two void pointers:
 first - data from node of the list, second - additional parameter from user;
 Retun : "0"- if successful , "1" if faild
*/
typedef int (* action_t)(void *data, void *param);

/*
* Input:  none
* Process: allocate memory for empty list
* Return: pointer to dlist_t if successful, NULL if failed
*/
dlist_t*  SListCreate(void);

/*
* Input:  pointer to dlist_t
* Process: destroy the whole dlist (free memory)
* Return: none
*/
void DListDestroy(dlist_t *list);

/*
 * The function checks the given list and returns ‘1’ if list is empty
 * or ‘0’ if not
 */
int DListIsEmpty(const dlist_t *list);

/*
 * Input: pointer to the dlist
 * Process: The function counts the number of elements in the given list
 * Return: number of elements
 */
size_t DListSize(const dlist_t *list);

/*
 * Input: Iterator
 * Process: Take data from the specific iterator.
 * Return: Pointer to data.
 */
void *DListGetData(iter_t iter);


/*
* Input : pointer to dlist, iterator, void pointer to data ;
* Process :Insert a new node before iterator ;
* Return : new iterator if successful,  pointer to tail if fails.
*/
iter_t DListInsert(dlist_t *dlist, iter_t iter, void *data);

/*
* Input : pointer to dlist, void pointer to data ;
* Process :Insert a new node before begin;
* Return : new iterator if successful,  pointer to tail if fails.
*/
iter_t DListPushFront (dlist_t *dlist, void *data);

/*
* Input : pointer to dlist, void pointer to data ;
* Process :Insert a new node before end;
* Return : new iterator if successful,  pointer to tail if fails.
*/
iter_t DListPushBack (dlist_t *dlist, void *data);

/*
*Input:  pointer to dlist ;
*Process: Pop node at the begin;
*/
void * DListPopFront(dlist_t *dlist);

/*
*Input:  pointer to dlist;
*Process: Pop node before the end;
*/
void * DListPopBack(dlist_t *dlist);

/*
*Input:  iterator ;
*Process: Remove node pointed by the iterator;
*Return: The iterator pointing to the next node or
 Undefined if last node was passed.
 And all previous iterators become invalid.
*/
iter_t DListRemove(iter_t iterator);

/*
* Input:  the iterator from which the user wants to start (included) and
 the iterator to which user wants to finish (excluded)and a pointer
 to a compare function.
* Process: Traverse through the list iterators and compare data from them with
  key from void pointer using compare function
* Return: iterator to position if successful, iterator to if failed
*/
iter_t DListFind(iter_t from, iter_t to, compare_t compare , void* key);

/*
*Input: the iterator from which the user wants to start (included) and
 the iterator to which user wants to finish (excluded) and a pointer
 to a function that user wants to perform on this range
*Process: performs the action through the range
*Returns: 0 if success and 1 if failure
*/
int DListForEach(iter_t from, iter_t to, action_t action, void *param);

/*
Input:  pointer to DList struct
Return: iterator that points to the first node in Linked List;
*/
iter_t DListBegin(const dlist_t *dlist);

/*
Input: pointer to DList struct
Return: iterator that points to the end in Linked List;
*/
iter_t DListEnd(const dlist_t *dlist);

/*
Input: iterator to the node, from which user want to receive the next node
Return: iterator that points to the next in LinkedList or undefined behavior if it points to the end;
 */
iter_t DListNext(iter_t iter);

/*
Input: iterator to the node, from which user want to receive the next node
Return: iterator that points to the previous in LinkedList or undefined behavior if it points to the begin;
 */
iter_t DListPrev(iter_t iter);
/*
 * Input: Two iterators;
 * Process: The function compares iterators to see if they are pointing to
 * the same node.
 * Return:
 * 1 -  in case is same
 * 0 - if is not same
 */
int DListIsSame(iter_t iter1, iter_t iter2);

/*
 * Input: iterator on node, from user wants to splice, iterator on node, to which user wants to splice and iterator on node, after which user wants to put splced nodes;
 * Process: copying nodes to another place;
 * Return: iterator that points the last spliced node;
*/
iter_t DListSplice(iter_t from, iter_t to, iter_t where);

/*
* Input:  the iterator from which the user wants to start (included) and
 the iterator to which user wants to finish (excluded)and a pointer
 to a compare function.
* Process: Traverse through the list iterators and compare data from them with
  key from void pointer using compare function
* Return: pointer to the destination dlist if successful, iterator to if failed
*/
dlist_t DListMultifind(iter_t from, iter_t to, compare_t compare, void *key, dlist_t dest);

#endif /* __DLIST_H__ */

