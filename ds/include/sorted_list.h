
#ifndef __SORTEDLIST_H__
#define __SORTEDLIST_H__

/*******************************************************************************
                                 *  OL85 API
                                 * version 1.5
 ******************************************************************************/

#include<stddef.h> /* size_t */    
#include "dlist.h" /* double linked list */

typedef struct sorted_list sorted_list_t;

typedef struct iter 
{
	iter_t dlist_iter_t;
	#ifndef NDEBUG
	sorted_list_t * sorted_list_ptr;
	#endif
} sorted_list_iter_t;



/*
*Compare function
*Input : two void pointers:
 first - data from node of the list, second - compare data
 Return :"0" - if successful , difference if not equal.
*/
typedef int (* sorted_compare_t)(void* data, void *key);

/*
*Action function
*Input : two void pointers:
 first - data from node of the list, second - additional parameter from user;
 Retun : "0"- if successful , and any ther user's return on failure.
*/
typedef int (* sorted_action_t)(void *data, void *param);

/*
* Input:  pointer to comparator function that will set default ordering of 
* all elements that will be added.
* Process: allocate memory for empty list
* Return: pointer to sorted list if successful, NULL if failed
*/
sorted_list_t *  SortedListCreate(sorted_compare_t comparator);

/*
* Input:  pointer to sorted list
* Process: destroy the whole sortedlist (free memory)
* Return: none
*/
void SortedListDestroy(sorted_list_t *sortedlist);


/*
* Input:  pointers to the list and data to be inserted
* Process: adds data to the list preserving internal order.
* Return: pointer to the element just inserted, or null on failure.
*/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void* data);



/*
 * The function checks the given list and returns ‘1’ if list is empty
 * or ‘0’ if not
 */
int SortedListIsEmpty(const sorted_list_t *sortedlist);

/*
 * Input: pointer to a sorted list
 * Process: The function counts the number of elements in the given list
 * Return: number of elements
 */
size_t  SortedListSize(const sorted_list_t *sortedlist);


/*
 * Input: Iterator
 * Process: Take data from the specific iterator.
 * Return: Pointer to data.
 */
void *SortedListGetData(sorted_list_iter_t iter);


/*
*Input:  pointer to sorted list ;
*Process: Pop element at the begin;
*/
void SortedListPopFront(sorted_list_t *sortedlist);

/*
*Input:  pointer to sortedlist;
*Process: Pop element at the end of the list;
*/
void SortedListPopBack(sorted_list_t *sortedlist);

/*
*Input:  iterator ;
*Process: Remove element pointed by the iterator;
*Return: The iterator to the next element or
* And all previous iterators become invalid.
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iterator);

/*
* Input:  the iterator from which the user wants to start (included) and
* the iterator to which user wants to finish (excluded)and a pointer
* to a compare function.
* Process: Traverse through the list and compare data from elements with
*  key from void pointer using compare function
* Return: iterator to position if successful, iterator to "to" if failed
*/
sorted_list_iter_t SortedListFind(sorted_list_t *sortedlist, sorted_list_iter_t from, 
					sorted_list_iter_t to , void * key);

/*
*Input: the iterator from which the user wants to start (included) and
* the iterator to which user wants to finish (excluded) and a pointer
* to a function that user wants to perform on this range
* Process: sends the data from each of the elements between "from" and "to"
* to the action function, along with parameter param passes as argument.
* Stops if the function fails (returns other than zero), even though not
* all elements were sent.  
* Returns: 0 if success or a status from the last call to the action function on
* failure.
*/
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, 
												sorted_action_t action, void *param);

/*
Input:  pointer to the list
Return: iterator to the first element of the list;
*/
sorted_list_iter_t SortedListBegin(const sorted_list_t *sortedlist);

/*
Input: pointer to the list
Return: iterator to the tail of the list;
*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *sortedlist);

/*
Input: iterator to the element, from which user want to receive the next element
Return: iterator that points to the next in sortedlist or undefined behavior 
if it points to the end;
 */
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/*
Input: iterator to the element, from which user want to receive the next element
Return: iterator that points to the previous element,  or undefined behavior 
if it points to the begin of the list;
 */
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);
/*
 * Input: Two iterators;
 * Process: The function compares iterators to see if they are pointing to
 * the same element.
 * Return:
 * 1 -  in case is same
 * 0 - if is not same
 */
int SortedListIsSame(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*
 * Input: two sorted lists with the same comparator function.
 * Process: merging two sorted list in the way that preserves order;
 * given by the comparators. The two comparator functions must be 
 * interchangeable among the lists, otherwise, behavior is undefined.
 * Return: pointer combined array;
*/
sorted_list_t * SortedListMerge(sorted_list_t *sortedlist1, 
										sorted_list_t *sortedlist2);

/*
* Input:  the iterator from which the user wants to start (included) and
* the iterator to which user wants to finish (excluded), 
* data search parameter and a pointer
* to a custom compare function, which may be different from that of the 
* sorted List.
* Process: Traverses through the list elements and compares data from them with
* key from void pointer using the compare function
* Return: pointer to the destination of the element if successful, 
* iterator to "to" if failed
*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
					sorted_list_iter_t to, sorted_compare_t compare, void *key);

#endif /* __SORTEDLIST_H__ */


