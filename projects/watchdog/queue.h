#ifndef __QUEUE_H__
#define __QUEUE_H__

/*******************************************************************************
                                 *  OL85 API
                                 * version 1.0
 ******************************************************************************/

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/*
* Input:  none
* Process: allocate memory for queue
* Return: pointer to queue_t if successful, NULL if failed
*/
queue_t *QCreate(void);

/*
* Input:  pointer to queue_t
* Process: destroy the whole queue (free memory)
* Return: none
*/
void QDestroy(queue_t *queue);

/*
 * The function checks the given queue and returns ‘1’ if queue is empty
 * or ‘0’ if not
 */
int QIsEmpty(const queue_t *queue);

/*
 * Input: pointer to the queue
 * Process: The function counts the number of elements in queue
 * Return: number of elements
 */
size_t QCount(const queue_t *queue);

/*
 * Input: pointer to the queue, void pointer to data;
 * Process: adds an element to the queue;
 * Return: 0 if success and 1 if failure;
 */
int QEnqueue(queue_t *queue, void *data);

/*
* Input : pointer to the queue;
* Process: removes first element from the queue;
* Return : none;
 */
void QDequeue(queue_t *queue);

/*
*Input: pointer to the queue;
*Process: retrieves data from the first element for queue;
*Return: pointer to data;
*/
void *QPeek(queue_t *queue);

/*
 * Input: pointer to queue_dest and queue_src;
 * Process: add queue_src to the end of queue_dest;
 * Return: ointer to the queue_dest;
 * queue_src will be invalid;
 */
queue_t *QAppend(queue_t *dest, queue_t *src);


#endif /* __QUEUE_H__ */
