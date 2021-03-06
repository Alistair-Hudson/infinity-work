#include <stdlib.h>		/* malloc */
#include <assert.h>		/*assert, NDEBUG*/
#include "sorted_list.h"
#include "dlist.h"

/******MACROS*******/
#define ASSERT_NOT_NULL(ptr)		(assert(NULL != ptr))

/********TYPESDEFS AND STRUCTS*******/
struct sorted_list
{
	dlist_t *list;
	sorted_compare_t cmp;	
};

/*******INTERNAL FUNCTIONS AND GLOBAL VARIABLES******/
static sorted_list_iter_t FindSupportFunction(sorted_list_iter_t from, 
						sorted_list_iter_t to, compare_t compare, void *key);

/*******FUNCTIONS*******/
sorted_list_t *SortedListCreate(sorted_compare_t comparator)
{
	dlist_t *new_dlist = NULL;
	sorted_list_t *new_sortedlist = NULL;	

	ASSERT_NOT_NULL(comparator);
	
	new_dlist = DListCreate();
	if (NULL == new_dlist)
	{
		return 0;
	}
	
	new_sortedlist = malloc(sizeof(struct sorted_list));
	if(NULL == new_sortedlist)
	{
		free(new_dlist);
		new_dlist = NULL;
		return 0;
	}
	
	new_sortedlist->list = new_dlist;
	new_sortedlist->cmp = comparator;

	return new_sortedlist;	
}

void SortedListDestroy(sorted_list_t *sortedlist)
{
	ASSERT_NOT_NULL(sortedlist);
	
	DListDestroy(sortedlist->list);
	free(sortedlist);
	sortedlist = NULL;
}

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void* data)
{
	sorted_list_iter_t iterator;

	ASSERT_NOT_NULL(sorted_list);
	

	
	iterator = FindSupportFunction(SortedListBegin(sorted_list), 
							SortedListEnd(sorted_list), sorted_list->cmp, data);

	iterator.dlist_iter_t = DListInsert(sorted_list->list, 
												iterator.dlist_iter_t, data);

	return iterator;
}

int SortedListIsEmpty(const sorted_list_t *sortedlist)
{
	ASSERT_NOT_NULL(sortedlist);
	return DListIsEmpty(sortedlist->list);
}

size_t SortedListSize(const sorted_list_t *sortedlist)
{
	ASSERT_NOT_NULL(sortedlist);
	return DListSize(sortedlist->list);
}

void *SortedListGetData(sorted_list_iter_t iter)
{
	return DListGetData(iter.dlist_iter_t);
}

void SortedListPopFront(sorted_list_t *sortedlist)
{
	ASSERT_NOT_NULL(sortedlist);
	DListPopFront(sortedlist->list);
}

void SortedListPopBack(sorted_list_t *sortedlist)
{
	ASSERT_NOT_NULL(sortedlist);
	DListPopBack(sortedlist->list);
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	iter.dlist_iter_t = DListRemove(iter.dlist_iter_t);
	return iter;
}

sorted_list_iter_t SortedListFind(sorted_list_t *sortedlist, 
					sorted_list_iter_t from, sorted_list_iter_t to, void *key)
{
	sorted_list_iter_t iterator;
	iterator.dlist_iter_t = DListFind(from.dlist_iter_t, to.dlist_iter_t, 
														sortedlist->cmp, key);
	return iterator;
}

int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, 
											sorted_action_t action, void *parm)
{
	return DListForEach(from.dlist_iter_t, to.dlist_iter_t, action, parm);
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *sortedlist)
{
	sorted_list_iter_t iterator;
	ASSERT_NOT_NULL(sortedlist);
	iterator.dlist_iter_t = DListBegin(sortedlist->list);
	return iterator;
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *sortedlist)
{
	sorted_list_iter_t iterator;
	ASSERT_NOT_NULL(sortedlist);
	iterator.dlist_iter_t = DListEnd(sortedlist->list);
	return iterator;
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	sorted_list_iter_t iterator;
	iterator.dlist_iter_t = DListNext(iter.dlist_iter_t);
	return iterator;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{	
	sorted_list_iter_t iterator;
	iterator.dlist_iter_t = DListPrev(iter.dlist_iter_t);
	return iterator;
}

int SortedListIsSame(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return DListIsSame(iter1.dlist_iter_t, iter2.dlist_iter_t);
}

sorted_list_t * SortedListMerge(sorted_list_t *sortedlist1, 
								sorted_list_t *sortedlist2)
{
	sorted_list_iter_t iter1;
	sorted_list_iter_t iter2;
	sorted_list_iter_t where;
	sorted_list_iter_t from;
	sorted_list_iter_t to;

	ASSERT_NOT_NULL(sortedlist2);
	ASSERT_NOT_NULL(sortedlist1);

	iter1 = SortedListBegin(sortedlist1);
	iter2 = SortedListBegin(sortedlist2);

	do
	{

		where = FindSupportFunction(iter1, SortedListEnd(sortedlist1), 
									sortedlist1->cmp, SortedListGetData(iter2));


		from = iter2;
		to = FindSupportFunction(iter2, SortedListEnd(sortedlist2), 
									sortedlist1->cmp, SortedListGetData(where));
	
		where = SortedListPrev(where);

		iter1 = SortedListNext(where);
		iter2 = to;

		DListSplice(from.dlist_iter_t, to.dlist_iter_t, where.dlist_iter_t);
	
		if(!sortedlist1->cmp(SortedListGetData(iter1),SortedListGetData(iter2)))
		{
			iter1 = SortedListNext(iter1);
		}

	}while(!SortedListIsSame(SortedListEnd(sortedlist1), iter1));

	SortedListDestroy(sortedlist2);
	return sortedlist1;
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
							sorted_list_iter_t to, compare_t compare, void *key)
{
	sorted_list_iter_t iterator;
	
	iterator.dlist_iter_t = DListFind(from.dlist_iter_t, to.dlist_iter_t, 
																compare, key);
	return iterator;
}

static sorted_list_iter_t FindSupportFunction(sorted_list_iter_t from, 
							sorted_list_iter_t to, compare_t compare, void *key)
{
	sorted_list_iter_t iterator;

	iterator = from;

	while(!SortedListIsSame(iterator, to) && 
							(0 >= compare(SortedListGetData(iterator), key)))
	{
		iterator = SortedListNext(iterator);
	}
	return iterator;
}


