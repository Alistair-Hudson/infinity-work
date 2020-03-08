#ifndef __OL85_SORTING_ALG_H__
#define __OL85_SORTING_ALG_H__

/*******************************************************************************
                                 *  OL85 API FOR SORTING ALGORITHMS
                                 * version 08.03.2020.0
 ******************************************************************************/

#include <stddef.h>			 	/* size_t */    

/*
 * Input:  Pointer to array and size of array
 * Process: Sorts the intergers in the array in order
 * using the bubble sort method
 */
void BubbleSort(int *array, size_t array_size);

/*
 * Input:  Pointer to array and size of array
 * Process: Sorts the intergers in the array in order
 * using the bubble sort method
 */
void BubbleSortOpt(int *array, size_t array_size);

/*
 * Input:  Pointer to array and size of array
 * Process: Sorts the intergers in the array in order
 * using the selection sort method
 */
void SelectionSort(int *array, size_t array_size);

/*
 * Input:  Pointer to array and size of array
 * Process: Sorts the intergers in the array in order
 * using the insertion sort method
 */
void InsertionSort(int *array, size_t array_size);

#endif /* __OL85_SORTING_ALG_H__ */
