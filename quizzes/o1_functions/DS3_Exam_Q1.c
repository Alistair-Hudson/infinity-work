/*
 * =============================================================================
 *
 *       Filename:  DS3_Exam_Q1.c
 *
 *    Description:  Data structures exam 3, question 1:
 *    				Array data structure with O(1) SetVal, GetVal, and SetAll
 *
 *        Version:  1.0
 *        Created:  05/21/20 12:22:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kobi Rappaport (KR), kobi.rappaport@gmail.com
 *
 * =============================================================================
 */




/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################# */

typedef struct array array_T;

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

struct element
{
	int val;
	unsigned long version;
};

struct array
{
	struct element all;
	struct element *arr;
};

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

void SetVal(int indx, int val, array_T *arr)
{
	arr->arr[indx].val = val;
	arr->arr[indx].version = arr->all.version;
}


int GetVal(int indx, array_T *arr)
{
	if (arr->all.version > arr->arr[indx].version) 
	{
		return (arr->all.val);
	}

	return (arr->arr[indx].val);
}


void SetAll(int val, array_T *arr)
{
	arr->all.val = val;
	++arr->all.version;
}


