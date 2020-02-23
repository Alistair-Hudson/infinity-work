
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

/*******************************************************************************
                                 *  OL85 API
                                 * version 23.02.2020.0
 ******************************************************************************/

#include <stddef.h>			 	/* size_t */    

typedef struct pqueue pqueue_t;

/*
*Compare function
*Input : two void pointers:
 first - data from node of the list, second - compare data
*Return :"0" - if successful , difference if not equal.
*/
typedef int (* compare_t)(void* data, void *key);

/*
*IsMatch function
*Input : two void pointers:
 first - data from node of the list, second - compare data
*Return :"0" - if successful , difference if not equal.
*/
typedef int (* ismatch_t)(void* data, void *key);

/*
* Input:  pointer to comparator function that will set default ordering of 
  all elements that will be added.
* Process: allocate memory for empty list
* Return: pointer to queue if successful, NULL if failed
*/
pqueue_t *  PQCreate(compare_t comparator);

/*
* Input:  pointer to queue
* Process: destroy the whole queue (free memory)
* Return: none
*/
void PQDestroy(pqueue_t *pqueue);

/*
* Input:  pointers to the queue and data to be inserted
* Process: adds data to the queue preserving internal order.
* Return: NULL on success, all other values are a failure
*/
int PQEnqueue(pqueue_t *pqueue, void* data);

/*
* Input:  pointer to the queue
* Process: Checks to see if queue is empty
* Return: "1" if empty "0" if not
*/
int PQIsEmpty(const pqueue_t *pqueue);

/*
 * Input: pointer to a queue
 * Process: The function counts the number of elements in the given queue
 * Return: number of elements
 */
size_t PQSize(const pqueue_t *pqueue);


/*
 * Input: Queue
 * Process: Observe data at front of queue.
 * Return: Pointer to data.
 */
void *PQPeek(pqueue_t *pqueue);

/*
*Input:  pointer to queue ;
*Process: Pop element at the begin;
*/
void PQDequeue(pqueue_t *pqueue);

/*
*Input:  Queue, match function, key that is to be looked for;
*Process: Erase the first element that contains the key from the queue
*Return: A pointer to the data that was stored in that element, else returns NULL
*/
void *PQErase(pqueue_t *pqueue, ismatch_t *ismatch, void *key);

/*
* Input: Pointer to the queue to clear
* Process: Removes all elements int the queue, but leaves the queue pointer intact
*/
void PQClear(pqueue_t *pqueue);

#endif /* __PQUEUE_H__ */
