/******************************************************************************
 *	Title:		Generic Sort
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	07.04.2020.0
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "generic_sort.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
static void QSortImp(void* base, size_t low, size_t high,
					int (*compar)(const void *, const void *));

static size_t QSPartion(void* base, size_t low, size_t high,
						int (*compar)(const void *, const void *));

static int MSortImp(void* base, size_t left, size_t right,   
					int (*compar)(const void *, const void *));

static int MSMege(void* base, size_t left, size_t middle, size_t right, 
					int (*compar)(const void *, const void *));

/******FUNCTIONS******/
void QSort(void* base, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *));
{
	QSortImp(base, 0, nmemb-1, compar);
}

static void QSortImp(void* base, size_t low, size_t high,
					int (*compar)(const void *, const void *))
{
	/*if low is before high*/
		/*create a partition index*/
		/*recursion on lower partition*/
		/*recursion on upper partition*/
}

static size_t QSPartion(void* base, size_t low, size_t high,
						int (*compar)(const void *, const void *))
{
	/*for index from low to high*/
		/*if index is before pivot*/
			/*increase low*/
			/*swap*/
	/*swap low and high*/
	/*return low +1*/
}

static void QSSwap()
{
	
}

int MSort(void* base, size_t nmemb, size_t size,  
			int (*compar)(const void *, const void *))
{
	return MSortImp(base, 0, nmemb - 1, compar);
}

static int MSortImp(void* base, size_t left, size_t right,   
					int (*compar)(const void *, const void *))
{
	/*if left is before right*/
		/*find middle*/
		/*recursion on left*/
		/*recursion on right*/

		/*merge the two halves*/

	return status;
}

static int MSMege(void* base, size_t left, size_t middle, size_t right, 
					int (*compar)(const void *, const void *))
{
	/*set
		*n1
		*n2
		*/
	/*Allocate for array LEFT and RIGHTH*/
	/*if either fails return 1*/
	
	/*for i from 0 until n1*/
		/*LEFT[i] = base[left + i]*/

	
	/*for j from 0 until n1*/
		/*RIGHT[i] = base[middle + i]*/

	/*reset i and j*/

	/*while i is before n1 && j is before n2*/
		/*if LEFT is before RIGHT*/
			/*base[k] = LEFT*/
			/*increase i*/
		/*else*/
			/*base[k] = RIGHT*/
			/*increase j*/
		/*increase k*/

	/*fill reamining LEFT*/
	
	/*fill reamaining RIGHT*/

	/*free LEFT and RIGHT*/

	return 0;

}








