
#ifndef __OL85_HEAP_H__
#define __OL85_HEAP_H__

/*******************************************************************************
                                * OL85 API FOR HEAP
                                * version 26.03.2020.1
******************************************************************************/

#include <stddef.h>	/* size_t */
#include "vector.h" /* dynamic vector functions*/

/*
* Input: pointers to two sets of data to cmmpare
* Return: 1 if before, 0 if not;
*/
typedef int(*heap_cmp_t)(void* lhs, void* rhs);

typedef struct heap heap_t;

/*
* Input:
* Process: create a heap datat structure
* Return; Pointer to Heap if successful, NULL if failed
*/
heap_t* HeapCreate(heap_cmp_t cmp);

/*
* Input: Pointer to the heap that is to be destroyed
*/
void HeapDestroy(heap_t* heap);

/*
* Input: Pointer to heap to push onto, pointer to the data to push
* Process: pushes data onto the heap,
* Return: 0 if successfull
*/
int HeapPush(heap_t* heap, void* data);

/*
* Input: pointer to theheap to pop from
* Process: Pops the first element from the heap
*/
void HeapPop(heap_t* heap);

/*
* Input: pointer to the heap to peek at
* Process: looks at the data stored in the first element of the heap
* Return: pointer to the data stored in the first element
*/
void* HeapPeek(const heap_t* heap);

/*
* Input: pointer to the heap 
* Process: finds the size of the heap
* Return: the size of the heap
*/
size_t HeapSize(const heap_t* heap);

/*
* Input: pointer to the heap
* Process: Determins if the heap is empty
* Return: 1 if empty, 0 if not
*/
int HeapIsEmpty(const heap_t* heap);

/*
* Input: pointer to the heap to remove from, pointer to the data to remove
* Process: locate and remove data fromt he heap
* Return: pointer to data removed, NULL if failed
*/
void* HeapRemove(heap_t* heap, int(*is_match)(void* data, void* param), void* param);

#endif /* __OL85_HEAP_H__ */
