
#ifndef __OL85_GENERIC_SORT_H__
#define __OL85_GENERIC_SORT_H__

/*******************************************************************************
                                * OL85 API FOR GENERIC SORT
                                * version 07.04.2020.0
******************************************************************************/

#include <stddef.h>	/* size_t */

void QSort(void* base, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *));

#endif /* __OL85_GENERIC_SORT_H__ */

