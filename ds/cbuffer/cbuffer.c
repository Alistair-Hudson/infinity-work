#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include "cbuffer.h"

/****** MACROS *******/

/****** TYPEDEFS ******/
struct cbuff
{
	size_t capacity;
	size_t read_offset;
	size_t size;
	char array[1];
};

/****** FUNCTIONS ******/
cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t *new_cbuff = malloc(sizeof(cbuff_t) + capacity);
	if(NULL == new_cbuff)
	{
		return 0;
	}

	new_cbuff->capacity = capacity;
	new_cbuff->size = 0;
	new_cbuff->read_offset = new_cbuff->array[0];
	
	return new_cbuff;
}

void CBuffDestroy(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	free(cbuff);
	cbuff = NULL;
}

int CBuffIsEmpty(const cbuff_t *cbuff)
{
	return (!cbuff->size);
}

size_t CBuffCapacity(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return cbuff->capacity;
}


