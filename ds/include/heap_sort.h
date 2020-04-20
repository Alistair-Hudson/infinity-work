#ifndef __OL85_HEAP_SORT_H__
#define __OL85_HEAP_SORT_H__

/*******************************************************************************
                                 *  OL85 API FOR SORTING ALGORITHMS
                                 * version 20.04.2020.0
 ******************************************************************************/

/*
 * cmp function returns 0, >0 or  < 0 for outcomes where: first = second,
 * first > second or first < second . Param (default =0)
 * Returns 1 in case of memory allocation failure.
 */
int HeapSort(void * array, size_t num_elem, size_t elem_size,
     int(*cmp)(const void *, const void *, void * param), void * param);

#endif /*__OL85_HEAP_SORT_H__ */
