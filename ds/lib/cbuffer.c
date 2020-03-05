#include <stdlib.h>		/* malloc */
#include <assert.h>		/* assert */
#include "cbuffer.h"

/****** MACROS *******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
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
	new_cbuff->read_offset = 0;
	
	return new_cbuff;
}

void CBuffDestroy(cbuff_t *cbuff)
{
	ASSERT_NOT_NULL(cbuff);
	free(cbuff);
	cbuff = NULL;
}

int CBuffIsEmpty(const cbuff_t *cbuff)
{
	ASSERT_NOT_NULL(cbuff);

	return (!cbuff->size);
}

size_t CBuffCapacity(const cbuff_t *cbuff)
{
	ASSERT_NOT_NULL(cbuff);
	
	return cbuff->capacity;
}

ssize_t CBuffWrite(cbuff_t *cbuff, const void *source, size_t nbytes)
{
	ssize_t bytes_to_copy = nbytes;
	size_t write_offset = 0;

	ASSERT_NOT_NULL(cbuff);
	ASSERT_NOT_NULL(source);
	
	if(0 == CBuffFreespace(cbuff))
	{
		return -1;
	}

	while(nbytes)
	{
		write_offset = (cbuff->read_offset + cbuff->size) % cbuff->capacity;
		if(0 == CBuffFreespace(cbuff))
		{
			break;
		}
		cbuff->array[write_offset] = *(char*)source;
		source = (char*)source + 1;
		++cbuff->size;
		--nbytes;
	}
	
	return (bytes_to_copy - nbytes);

}

ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t nbytes)
{
	ssize_t bytes_to_copy = nbytes;
	size_t bytes_to_end = 0;

	ASSERT_NOT_NULL(cbuff);
	ASSERT_NOT_NULL(dest);
	
	if(CBuffIsEmpty(cbuff))
	{
		return -1;
	}

	bytes_to_end = CBuffCapacity(cbuff) - cbuff->read_offset;

	while(nbytes)
	{
		if(0 >= bytes_to_end)
		{
			cbuff->read_offset = 0;
			bytes_to_end = cbuff->capacity;
		}
		if(CBuffIsEmpty(cbuff))
		{
			break;
		}
		*(char*)dest = cbuff->array[cbuff->read_offset];
		++cbuff->read_offset;
		dest = (char*)dest + 1;
		--cbuff->size;
		--nbytes;
		--bytes_to_end;
	}
	
	return (bytes_to_copy - nbytes);

}

size_t CBuffFreespace(const cbuff_t *cbuff)
{
	return (cbuff->capacity - cbuff->size);
}
