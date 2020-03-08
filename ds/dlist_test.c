#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

#define MAX_PASS	(8)

int IntComp(void *x, void *y)
{
	return !((int*)x == (int*)y);
}

int AddTo (void *add_to, void *adding)
{
	*(int*)add_to += *(int*)adding;
	return 0;
}

static int Stage1Testing()
{
	dlist_t *list_ptr = 0;
	
	list_ptr = DListCreate();

	if(!DListIsEmpty(list_ptr))
	{
		printf("IsEmpty Failed\n");
		return 0;
	}
	if(0 != DListSize(list_ptr))
	{
			printf("Size Failed\n");
			return 0;
	}

	DListDestroy(list_ptr);	
	return 1;
}

static int InsertTest()
{
	dlist_t *list_ptr = 0;
	iter_t tail = 0;
	int num_of_inserts = 0;

	list_ptr = DListCreate();
	tail = DListEnd(list_ptr);

	while(100 > num_of_inserts)
	{

		DListInsert(list_ptr, tail, &num_of_inserts);
		++num_of_inserts;
	}

	if(DListIsEmpty(list_ptr))
	{
		printf("Insert Failed\n");
		return 0;
	}

	if(100 != DListSize(list_ptr))
	{
			printf("Insert Failed\n");
			return 0;
	}
	
	DListPushFront(list_ptr, &num_of_inserts);
	if(101 != DListSize(list_ptr))
	{
			printf("PushFront Failed\n");
			return 0;
	}

	DListPushBack(list_ptr, &num_of_inserts);
	if(102 != DListSize(list_ptr))
	{
			printf("PushBack Failed\n");
			return 0;
	}

	DListDestroy(list_ptr);	
	return 1;
}

static int RemoveTest()
{
	dlist_t *list_ptr = 0;
	iter_t tail = 0;
	int num_of_inserts = 100;

	list_ptr = DListCreate();
	tail = DListEnd(list_ptr);

	while(0 <= num_of_inserts)
	{
		DListInsert(list_ptr, tail, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		DListRemove(DListBegin(list_ptr));
		++num_of_inserts;
	}

	if(DListIsEmpty(list_ptr))
	{
		printf("Remove Failed\n");
		return 0;
	}
	if(49 != DListSize(list_ptr))
	{
			printf("Remove Failed\n");
			return 0;
	}

	DListPopFront(list_ptr);
	if(48 != DListSize(list_ptr))
	{
			printf("PopFront Failed\n");
			return 0;
	}

	DListPopBack(list_ptr);
	if(47 != DListSize(list_ptr))
	{
			printf("PopFront Failed\n");
			return 0;
	}

	DListDestroy(list_ptr);	
	return 1;
}

static int GetTest()
{
	dlist_t *list_ptr = 0;
	iter_t tail = 0;
	int num_of_inserts = 100;

	list_ptr = DListCreate();
	tail = DListBegin(list_ptr);

	while(0 <= num_of_inserts)
	{
		DListInsert(list_ptr, tail, &num_of_inserts);
		--num_of_inserts;
	}
	
	if(num_of_inserts != *(int*)DListGetData(DListBegin(list_ptr)))
	{
		printf("Get Failed\n");
		return 0;
	}

	DListDestroy(list_ptr);
	return 1;
}

/*static int SetTest()
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
}*/

static int Stage3Testing()
{
	dlist_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int num_of_inserts = 100;

	list_ptr = DListCreate();
	header = DListBegin(list_ptr);
	tail = DListEnd(list_ptr);
	
	
	if(!DListIsSame(header, tail))
	{
		printf("IsSame Failed\n");
		return 0;
	}

	while(0 <= num_of_inserts)
	{
		DListInsert(list_ptr, tail, &num_of_inserts);
		--num_of_inserts;
	}
	header = DListBegin(list_ptr);
	iterator = header;
	while(50 >= num_of_inserts)
	{
		iterator = DListNext(iterator);
		++num_of_inserts;
	}
	if(DListIsSame(header, iterator))
	{
		printf("Next Failed\n");
		return 0;
	}

	DListDestroy(list_ptr);
	return 1;
}

static int FindTest()
{
	dlist_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int array_of_ints[100];
	int index = 0;
	
	list_ptr = DListCreate();
	tail = DListBegin(list_ptr);

	

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		DListInsert(list_ptr, tail, &array_of_ints[index]);
		++index;
	}
	tail = DListEnd(list_ptr);
	header = DListBegin(list_ptr);
	index = 0;
	do
	{
		iterator = DListFind(header, tail, IntComp, &array_of_ints[index]);
		if(array_of_ints[index] != *(int*)DListGetData(iterator))
		{
			printf("Find Failed\n");
			return 0;
		}
		++index;
	}while(100 > index);
	
	DListDestroy(list_ptr);
	return 1;
}

static int ForEachTest()
{
	dlist_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int array_of_ints[100];
	int index = 0;
	int added_num = 10;

	list_ptr = DListCreate();
	tail = DListEnd(list_ptr);



	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		DListInsert(list_ptr, tail, &array_of_ints[index]);
		++index;
	}
	header = DListBegin(list_ptr);
	index = 0;
	DListForEach(header, tail, AddTo, &added_num);
	iterator = header;
	while(100 > index)
	{

		if((array_of_ints[index]) != *(int*)DListGetData(iterator))
		{
		printf("ForEach Failed\n ");
		return 0;
		}
		iterator = DListNext(iterator);
		++index;
	}
	
	DListDestroy(list_ptr);
	return 1;
}

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
}
	
int main()
{
	size_t pass = 0;
	
	pass += Stage1Testing();
	pass += InsertTest();
	pass += RemoveTest();
	pass += GetTest();
	/*pass += SetTest();*/
	pass += Stage3Testing();
	pass += FindTest();
	pass += ForEachTest();
	pass += SpliceTest();

	if(MAX_PASS == pass)
	{
		printf("\n\n\nAll passed\n\n\n");
	}
	
	return 0;
}
