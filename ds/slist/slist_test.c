#include <stdio.h>
#include <stdlib.h>

#include "slist.c"

int main()
{
	list_t *list_ptr = 0;
	iter_t header = 0;
	iter_t tail = 0;
	list_ptr = SListCreate();
	header = SListBegin(list_ptr);
	tail = SListEnd(list_ptr);

	SListInsertBefore(header, (void *)666);
	SListInsertBefore(header, (void *)666);

	printf("empty =  %d\n", SListIsEmpty(list_ptr));
	printf("count =  %ld\n", SListCount(list_ptr));
	SListDestroy(list_ptr);
	return 0;
}
