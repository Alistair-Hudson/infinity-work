#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slist.h"

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
	list_t *list_ptr = 0;
	
	list_ptr = SListCreate();

	if(!SListIsEmpty(list_ptr))
	{
		printf("IsEmpty Failed\n");
		return 0;
	}
	if(0 != SListCount(list_ptr))
	{
			printf("Count Failed\n");
			return 0;
	}

	SListDestroy(list_ptr);	
	return 1;
}

static int InsertTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	int num_of_inserts = 0;

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	while(100 > num_of_inserts)
	{
		SListInsertBefore(list_ptr, header, &num_of_inserts);
		++num_of_inserts;
	}
	if(SListIsEmpty(list_ptr))
	{
		printf("Insert Failed\n");
		return 0;
	}
	if(100 != SListCount(list_ptr))
	{
			printf("Insert Failed\n");
			return 0;
	}

	SListDestroy(list_ptr);	
	return 1;
}

static int RemoveTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	int num_of_inserts = 100;

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	while(0 <= num_of_inserts)
	{
		SListInsertBefore(list_ptr, header, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		SListRemove(header);
		++num_of_inserts;
	}

	if(SListIsEmpty(list_ptr))
	{
		printf("Remove Failed\n");
		return 0;
	}
	if(49 != SListCount(list_ptr))
	{
			printf("Remove Failed\n");
			return 0;
	}

	SListDestroy(list_ptr);	
	return 1;
}

static int GetTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	int num_of_inserts = 100;

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	while(0 <= num_of_inserts)
	{
		SListInsertBefore(list_ptr, header, &num_of_inserts);
		--num_of_inserts;
	}
	
	if(num_of_inserts != *(int*)SListGetData(header))
	{
		printf("Get Failed\n");
		return 0;
	}

	SListDestroy(list_ptr);
	return 1;
}

static int SetTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	int num_of_inserts = 100;
	int set_num = 666;
	char *set_str = "Hello";

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	while(0 <= num_of_inserts)
	{
		SListInsertBefore(list_ptr, header, &num_of_inserts);
		--num_of_inserts;
	}
	
	SListSetData(header, &set_num);
	if(set_num != *(int*)SListGetData(header))
	{
		printf("Set Failed\n");
		return 0;
	}
	SListSetData(header, &set_str);
	if(!strcmp(set_str, SListGetData(header)))
	{
		printf("Set Failed\n");
		return 0;
	}

	SListDestroy(list_ptr);
	return 1;
}

static int Stage3Testing()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int num_of_inserts = 100;

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);
	tail = SListEnd(list_ptr);
	iterator = header;
	
	if(!SListIsEqual(header, tail))
	{
		printf("IsEqual Failed\n");
		return 0;
	}

	while(0 <= num_of_inserts)
	{
		SListInsertBefore(list_ptr, header, &num_of_inserts);
		--num_of_inserts;
	}
	while(50 >= num_of_inserts)
	{
		iterator = SListNext(iterator);
		++num_of_inserts;
	}
	if(SListIsEqual(header, iterator))
	{
		printf("Next Failed\n");
		return 0;
	}

	SListDestroy(list_ptr);
	return 1;
}

static int FindTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int array_of_ints[100];
	int index = 0;
	
	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	iterator = header;

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		SListInsertBefore(list_ptr, header, &array_of_ints[index]);
		++index;
	}
	tail = SListEnd(list_ptr);
	index = 0;
	while(100 > index)
	{
		iterator = SListFind(header, tail, IntComp, &array_of_ints[index]);
		if(array_of_ints[index] != *(int*)SListGetData(iterator))
		{
		printf("Find Failed\n");
		return 0;
		}
		++index;
	}
	
	SListDestroy(list_ptr);
	return 1;
}

static int ForEachTest()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	iter_t iterator = 0;
	int array_of_ints[100];
	int index = 0;
	int added_num = 10;

	list_ptr = SListCreate();
	header = SListBegin(list_ptr);

	iterator = header;

	for(index = 0; index < 100; ++index)
	{
		array_of_ints[index] = index;
	}
	index = 0;
	while(100 > index)
	{
		SListInsertBefore(list_ptr, header, &array_of_ints[index]);
		++index;
	}
	tail = SListEnd(list_ptr);
	--index;
	SListForEach(header, tail, AddTo, &added_num);
	while(0 <= index)
	{
		if((array_of_ints[index]) != *(int*)SListGetData(iterator))
		{
		printf("ForEach Failed\n ");
		return 0;
		}
		iterator = SListNext(iterator);
		--index;
	}
	
	SListDestroy(list_ptr);
	return 1;
}
	
int main()
{
	size_t pass = 0;
	
	pass += Stage1Testing();
	pass += InsertTest();
	pass += RemoveTest();
	pass += GetTest();
	pass += SetTest();
	pass += Stage3Testing();
	pass += FindTest();
	pass += ForEachTest();


	if(MAX_PASS == pass)
	{
		printf("\n\n\nAll passed\n\n\n");
	}
	
	return 0;
}
