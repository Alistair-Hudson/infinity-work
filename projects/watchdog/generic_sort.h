#ifndef __OL85_GENERIC_SORT_H__
#define __OL85_GENERIC_SORT_H__

/*******************************************************************************
                                 *  OL85 API FOR SORTING ALGORITHMS
                                 * version 04.07.2020.0
 ******************************************************************************/

/*
 * cmp function returns 0, >0 or  < 0 for outcomes where: first = second,
 * first > second or first < second . Param (default =0) is to switch
 * between ascending (0) and descending (1) order of sorting.
 * Returns -1 in case of memory allocation failure.
 */
int MergeSort(void * array, size_t num_elem, size_t elem_size,
     int(*cmp)(const void *, const void *, void * param), void * param);

/*
* cmp function returns 0, >0 or  < 0 for outcomes where: first = second,
* first > second or first < second . Param (default =0) is to switch
* between ascending (0) and descending (1) order of sorting.
*
*/
void QuickSort(void * array, size_t num_elem, size_t elem_size,
    int(*cmp)(const void *, const void *, void * param), void * param);

#endif /*__OL85_GENERIC_SORT_H__ */
