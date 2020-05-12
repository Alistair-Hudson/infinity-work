
#ifndef __OL85_HTABLE_H__
#define __OL85_HTABLE_H__

/*******************************************************************************
                                * OL85 API FOR HASHTABLE
                                * version 23.03.2020.0
******************************************************************************/

#include <stddef.h>	/* size_t */
#include "dlist.h" /* double linked list */

/*
*Hash function
*Input : data:
 first - data from node of the list, second - compare data
 Return: index of array:.
*/
typedef size_t (* hash_func_t)(void* entry);

/*
* action function
* Input : two void pointers:
* first - value from node of the list, second - param
* Return :"0" - if successful , "1" - if fails.
*/
/*typedef int (* action_t)(void *value, void* param);
*/

/*
* Is match function
* Input : two void pointers:
* first - data from node of the list, second - compare data
* Return :"0" - if successful , difference if not equal.
*/
typedef int (*hash_compare_t)(void* value, void* key);
typedef struct htable
{
	hash_func_t hash_func;
	hash_compare_t compare;
	size_t table_size;
	dlist_t **table;
} htable_t;


/*
* Input: number of elements of array, compare function
* Process: Create an HashTable
* Returns: pointer to the HashTable
*/
htable_t *HTableCreate(hash_func_t hash_func, size_t table_size, compare_t comapre);

/*
* Input: pointer to the HashTable
* Process: free the HashTable and all elements in it.
* Returns: none.
*/
void HTableDestroy(htable_t *htable);

/*
* Input: pointer to the HashTable
* Process: traverse HashTable and calculate number of nodes
* Returns: size of the HashTable
*/
size_t HTableSize(const htable_t *htable);

/*
* Input: pointer to the HashTable
* Process: check if node exist
* Returns: 1 if empty / 0 if not
*/
int HTableIsEmpty(const htable_t *htable);

/*
* Input: Pointer to HashTable and data
* Process: insert the new node
* Returns: pointer to
*/
void HTableInsert(htable_t *htable, void *entry);

/*
* Input: Pointer to HashTable and data
* Process: find node with data and remove the node
* Returns: none
*/
void HTableRemove(htable_t *htable, void *key);

/*
* Input:  Pointer to the HTable, pointer to key.
* Process: Traverse HashTable looking for desired data
* Returns: data if successful / NULL if failed
*/
void *HTableFind(const htable_t *htable, void *to_find);

/*
* Input:  Pointer to the HTable, pointer to parameters, ation func.
* Process: Traverse HashTable and do an action for each node
* Returns: '0' if successful / '1' if failed
*/
int HTableForEach(htable_t *htable, action_t action, void *param);

/*
* Input:  Pointer to the HTable
* Process: calculate the Load Factor of the Hash Table
* Returns: Load Factor
*/
double HTableLoadFactor(const htable_t *htable);

/*
* Input:  Pointer to the HTable
* Process: calculate the Standar Deviation of the Hash Table
* Returns: Standar Deviation
*/
double HTableSD(const htable_t *htable);

#endif /* __OL85_HTABLE_H__ */

