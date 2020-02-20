#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortedlist.c"

#define MAX_PASS	(10)

int IntComp(void *x, void *y)
{
	return (*(int*)x - *(int*)y);
}


int AddTo (void *add_to, void *adding)
{
	*(int*)add_to += *(int*)adding;
	return 0;
}

static int Stage1Testing()
{
	sorted_list_t *list_ptr = 0;
	
	list_ptr = SortedListCreate(IntComp);

	if(!SortedListIsEmpty(list_ptr))
	{
		printf("IsEmpty Failed\n");
		return 0;
	}
	if(0 != SortedListSize(list_ptr))
	{
			printf("Size Failed\n");
			return 0;
	}

	SortedListDestroy(list_ptr);	
	return 1;
}

static int InsertTest()
{
	sorted_list_t *list_ptr = 0;
	int num_of_inserts = 0;

	list_ptr = SortedListCreate(IntComp);

	while(100 > num_of_inserts)
	{

		SortedListInsert(list_ptr, &num_of_inserts);
		++num_of_inserts;
	}

	if(SortedListIsEmpty(list_ptr))
	{
		printf("Insert Failed\n");
		return 0;
	}

	if(100 != SortedListSize(list_ptr))
	{
			printf("Insert Failed\n");
			return 0;
	}
	
	SortedListDestroy(list_ptr);	
	return 1;
}

static int RemoveTest()
{
	sorted_list_t *list_ptr = 0;
	int num_of_inserts = 100;

	list_ptr = SortedListCreate(IntComp);

	while(0 <= num_of_inserts)
	{
		SortedListInsert(list_ptr, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		SortedListRemove(SortedListBegin(list_ptr));
		++num_of_inserts;
	}

	if(SortedListIsEmpty(list_ptr))
	{
		printf("Remove Failed\n");
		return 0;
	}
	if(49 != SortedListSize(list_ptr))
	{
			printf("Remove Failed\n");
			return 0;
	}

	SortedListPopFront(list_ptr);
	if(48 != SortedListSize(list_ptr))
	{
			printf("PopFront Failed\n");
			return 0;
	}

	SortedListPopBack(list_ptr);
	if(47 != SortedListSize(list_ptr))
	{
			printf("PopFront Failed\n");
			return 0;
	}

	SortedListDestroy(list_ptr);	
	return 1;
}

static int GetTest()
{
	sorted_list_t *list_ptr = 0;
	sorted_list_iter_t iterator;
	int int_array[50];
	int index = 0;

	list_ptr = SortedListCreate(IntComp);

	while(50 > index)
	{
		int_array[index] = index;
		++index;
	}

	index = 0;
	while(50 >index)
	{
		SortedListInsert(list_ptr, &int_array[index]);
		++index;
	}
	index = 0;
	while(50 >index)
	{
		SortedListInsert(list_ptr, &int_array[index]);
		++index;
	}
	index = 0;
	iterator = SortedListBegin(list_ptr);
	while(100 > index)
	{
		if(int_array[index/2] != *(int*)SortedListGetData(iterator))
		{
			printf("Get Failed at index: %d, value in list %d\n",
									index, *(int*)SortedListGetData(iterator));
			return 0;
		}
		iterator = SortedListNext(iterator);
		++index;
	}

	SortedListDestroy(list_ptr);
	return 1;
}
/*
static int SetTest()
{
	dlist_t *list_ptr = 0;
	iter_t header = 0;
	int num_of_inserts = 100;
	int set_num = 666;
	char *set_str = "Hello";

	list_ptr = DListCreate();
	header = DListBegin(list_ptr);

	while(0 <= num_of_inserts)
	{
		DListInsert(list_ptr, header, &num_of_inserts);
		--num_of_inserts;
	}
	
	DListSetData(header, &set_num);
	if(set_num != *(int*)DListGetData(header))
	{
		printf("Set Failed\n");
		return 0;
	}
	DListSetData(header, &set_str);
	if(!strcmp(set_str, DListGetData(header)))
	{
		printf("Set Failed\n");
		return 0;
	}

	DListDestroy(list_ptr);
	return 1;
}
*/
static int Stage3Testing()
{
	sorted_list_t *list_ptr = 0;
	sorted_list_iter_t header;
	sorted_list_iter_t tail;
	sorted_list_iter_t iterator;
	int num_of_inserts = 100;

	list_ptr = SortedListCreate(IntComp);
	header = SortedListBegin(list_ptr);
	tail = SortedListEnd(list_ptr);
	
	
	if(!SortedListIsSame(header, tail))
	{
		printf("IsSame Failed\n");
		return 0;
	}

	while(0 <= num_of_inserts)
	{
		SortedListInsert(list_ptr, &num_of_inserts);
		--num_of_inserts;
	}
	header = SortedListBegin(list_ptr);
	iterator = header;
	while(50 >= num_of_inserts)
	{
		iterator = SortedListNext(iterator);
		++num_of_inserts;
	}
	if(SortedListIsSame(header, iterator))
	{
		printf("Next Failed\n");
		return 0;
	}

	SortedListDestroy(list_ptr);
	return 1;
}

static int FindTest()
{
	sorted_list_t *list_ptr = 0;
	sorted_list_iter_t header;
	sorted_list_iter_t tail;
	sorted_list_iter_t iterator;
	int array_of_ints[100];
	int index = 0;
	
	list_ptr = SortedListCreate(IntComp);

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		SortedListInsert(list_ptr, &array_of_ints[index]);
		++index;
	}
	tail = SortedListEnd(list_ptr);
	header = SortedListBegin(list_ptr);
	index = 0;
	do
	{
		iterator = SortedListFind(list_ptr, header, tail, &array_of_ints[index]);
		if(array_of_ints[index] != *(int*)SortedListGetData(iterator))
		{
			printf("Find Failed\n");
			return 0;
		}
		++index;
	}while(100 > index);
	
	SortedListDestroy(list_ptr);
	return 1;
}

static int ForEachTest()
{
	sorted_list_t *list_ptr = 0;
	sorted_list_iter_t header;
	sorted_list_iter_t tail;
	sorted_list_iter_t iterator;
	int array_of_ints[100];
	int index = 0;
	int added_num = 10;

	list_ptr = SortedListCreate(IntComp);

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		SortedListInsert(list_ptr, &array_of_ints[index]);
		++index;
	}
	tail = SortedListEnd(list_ptr);
	header = SortedListBegin(list_ptr);
	index = 0;
	SortedListForEach(header, tail, AddTo, &added_num);
	iterator = header;
	while(100 > index)
	{
		if((array_of_ints[index]) != *(int*)SortedListGetData(iterator))
		{
		printf("ForEach Failed\n ");
		return 0;
		}
		iterator = SortedListNext(iterator);
		++index;
	}
	
	SortedListDestroy(list_ptr);
	return 1;
}

static int FindIfTest()
{
	sorted_list_t *list_ptr = 0;
	sorted_list_iter_t header;
	sorted_list_iter_t tail;
	sorted_list_iter_t iterator;
	int array_of_ints[100];
	int index = 0;
	int search_val = 25;
	
	list_ptr = SortedListCreate(IntComp);

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	array_of_ints[search_val] = 0;
	index = 0;
	while(100 > index)
	{
		SortedListInsert(list_ptr, &array_of_ints[index]);
		++index;
	}
	tail = SortedListEnd(list_ptr);
	header = SortedListBegin(list_ptr);
	index = 0;

	iterator = SortedListFindIf(header, tail, IntComp, &search_val);

	if(array_of_ints[search_val] == *(int*)SortedListGetData(iterator))
	{
		printf("FindIf Failed\n");
		return 0;
	}

	SortedListDestroy(list_ptr);
	return 1;
}
/*
int SpliceTest()
{
	dlist_t *list1 = 0;
	dlist_t *list2 = 0;
	iter_t tail1 = 0;
	iter_t tail2 = 0;
	iter_t from = 0;
	iter_t to = 0;
	iter_t where = 0;
	int num_of_inserts = 0;

	list1 = DListCreate();
	list2 = DListCreate();
	tail1 = DListEnd(list1);
	tail2 = DListEnd(list2);


	while(100 > num_of_inserts)
	{
		DListInsert(list1, tail1, &num_of_inserts);
		DListInsert(list2, tail2, &num_of_inserts);
		++num_of_inserts;
	}

	from = DListBegin(list1);
	to = DListBegin(list1);
	where = DListBegin(list2);
	num_of_inserts = 0;
	while(50 > num_of_inserts)
	{
		to = DListNext(to);
		where = DListNext(where);
		++num_of_inserts;
	}

	DListSplice(from, to, where);
	if(150 != DListSize(list2))
	{
			printf("Splice Failed, %ld\n", DListSize(list2));
			return 0;
	}
	
	DListDestroy(list1);
	DListDestroy(list2);
	return 1;
}*/

int MergeTest1()
{
	sorted_list_t *list1 = 0;
	sorted_list_t *list2 = 0;
	sorted_list_iter_t iterator;
	int array_of_ints[100];
	int index = 0;

	list1 = SortedListCreate(IntComp);
	list2 = SortedListCreate(IntComp);

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}

	index = 0;
	while(25 > index)
	{
		SortedListInsert(list1, &array_of_ints[index]);
		SortedListInsert(list2, &array_of_ints[index+25]);
		SortedListInsert(list1, &array_of_ints[index+50]);
		SortedListInsert(list2, &array_of_ints[index+75]);
		++index;
	}
	SortedListMerge(list1, list2);

	if(100 != SortedListSize(list1))
	{
			printf("Merge1 Failed, %ld\n", SortedListSize(list1));
			return 0;
	}

	iterator = SortedListBegin(list1);
	index = 0;
	while(100 > index)
	{
		if((array_of_ints[index]) != *(int*)SortedListGetData(iterator))
		{
		printf("Merge1 Failed\n ");
		return 0;
		}
		iterator = SortedListNext(iterator);
		++index;
	}
	
	SortedListDestroy(list1);

	return 1;
}

int MergeTest2()
{
	sorted_list_t *list1 = 0;
	sorted_list_t *list2 = 0;
	sorted_list_iter_t iterator;
	int array_of_ints[100];
	int index = 0;

	list1 = SortedListCreate(IntComp);
	list2 = SortedListCreate(IntComp);

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}

	index = 0;
	while(25 > index)
	{
		SortedListInsert(list2, &array_of_ints[index]);
		SortedListInsert(list1, &array_of_ints[index+25]);
		SortedListInsert(list2, &array_of_ints[index+50]);
		SortedListInsert(list1, &array_of_ints[index+75]);
		++index;
	}
	SortedListMerge(list1, list2);

	if(100 != SortedListSize(list1))
	{
			printf("Merge2 Failed, %ld\n", SortedListSize(list1));
			return 0;
	}

	iterator = SortedListBegin(list1);
	index = 0;
	while(100 > index)
	{
		if((array_of_ints[index]) != *(int*)SortedListGetData(iterator))
		{
		printf("Merge2 Failed\n ");
		return 0;
		}
		iterator = SortedListNext(iterator);
		++index;
	}
	
	SortedListDestroy(list1);
	return 1;
}

int main()
{
	size_t pass = 0;
	
	pass += Stage1Testing();
	pass += InsertTest();
	pass += RemoveTest();
	pass += GetTest();
	pass += Stage3Testing();
	pass += FindTest();
	pass += ForEachTest();
	pass += FindIfTest();
	pass += MergeTest1();
	pass += MergeTest2();

	if(MAX_PASS == pass)
	{
		printf("\n\n\nAll passed\n\n\n");
	}
	
	return 0;
}
