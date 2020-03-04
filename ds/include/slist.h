#ifndef __SLIST_H__
#define __SLIST_H__

/*******************************************************************************
                                 *  OL85 API 
                                 * version 1.2
 ******************************************************************************/

#include<stddef.h> /* size_t */

typedef struct list list_t;
typedef void * iter_t;
/*
*Compare function 
*Input : two void pointers: 
 first - data from node of the list, second - compare data 
 Return :"0" - if successful , difference if not equal.
*/
typedef int (* compare_t)(void* data, void *compared_data);
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
* Return: pointer to list_t if successful, NULL if failed 
*/
list_t*  SListCreate(void);

/*
* Input:  pointer to list_t
* Process: destroy the whole list (free memory)
* Return: none
*/
void SListDestroy(list_t *list);

/*
 * The function checks the given list and returns ‘1’ if list is empty
 * or ‘0’ if not
 */
int SListIsEmpty(const list_t *list);

/*
 * Input: pointer to the list
 * Process: The function counts the number of elements in the given list
 * Return: number of elements
 */
size_t SListCount(const list_t *list);

/*
 * Input: Iterator
 * Process: Take data from the specific iterator.
 * Return: Pointer to data.
 */
void *SListGetData(iter_t iter);

/*
* Input : iterator, void pointer to data ;
* Process: Change the address pointing to the value of a given iterator;
* Return : none.
 */
void SListSetData(iter_t iter, void *value); 

/*
* Input : pointer to list, iterator, void pointer to data ;
* Process :Insert a new node before iterator ;
* Return : new iterator if successful,  pointer to tail if fails.
*/
iter_t SListInsertBefore(list_t *list, iter_t iter, void *data);


/*
*Input:  iterator ;
*Process: Remove node pointed by the iterator;
*Return: The iterator pointing to the next node or 
 Undefined if last node was passed.
 And all previous iterators become invalid.
*/
iter_t SListRemove(iter_t iterator);

/*
* Input:  the iterator from which the user wants to start (included) and 
 the iterator to which user wants to finish (excluded)and a pointer 
 to a compare function. 
* Process: Traverse through the list iterators and compare data from them with
  data from void pointer using compare function
* Return: iterator to position if successful, iterator to end if failed
*/
iter_t SListFind(iter_t from, iter_t to, compare_t compare , void* data); 

/*
*Input: the iterator from which the user wants to start (included) and 
 the iterator to which user wants to finish (excluded) and a pointer 
 to a function that user wants to perform on this range
*Process: performs the action through the range
*Returns: 0 if success and 1 if failure
*/
int SListForEach(iter_t from, iter_t to, action_t action, void *param);

/*
Input:  pointer to List struct 
Return: iterator that points to the first node in Linked List;
*/
iter_t SListBegin(const list_t *list);

/*
Input: pointer to List struct 
Return: iterator that points to the end in Linked List;
*/
iter_t SListEnd(const list_t *list);

/* 
Input: iterator to the node, from which user want to receive the next node
Return: iterator that points to the next in LinkedList;
 */
iter_t SListNext(iter_t iter);

/*
 * Input: Two iterators;
 * Process: The function compares iterators to see if they are pointing to 
 * the same node.
 * Return: 
 * 1 -  in case is equal
 * 0 - if is not equal
 */
int SListIsEqual(iter_t iter1, iter_t iter2);


#endif /* __SLIST_H__ */
