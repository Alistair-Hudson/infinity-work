/******************************************************************************
 *	Title:		Fixed Storage Allocator
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel Pablo
 *	Version:	27.02.2020.1
 ******************************************************************************/

/******INCLUDED FILES******/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "fsa.h"


/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define HEADER_SIZE				(sizeof(size_t))
#define INFO_SIZE(type)			(sizeof(type))
#define PADDING(block)			((HEADER_SIZE - (block % HEADER_SIZE)) % HEADER_SIZE)

/******TYPEDEFS******/
struct allocator
{
	size_t next_free;	
};

/******GLOBAL VARIABLES******/

/******INTERNAL FUNCTIONS******/

/******FUNCTIONS******/

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t true_block_size = 0;
	size_t total_for_blocks = 0;
	size_t final_buffer_size = 0;

	true_block_size = block_size + HEADER_SIZE + PADDING(block_size);
	total_for_blocks = num_of_blocks * true_block_size;
	final_buffer_size = total_for_blocks + INFO_SIZE(struct allocator);

	return final_buffer_size;
}

fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size)
{
	size_t address_offset = 0;
	size_t *header = NULL;
	fsa_t *new_alloc = NULL;

	ASSERT_NOT_NULL(buffer);

	address_offset = (HEADER_SIZE + block_size + PADDING(block_size)) 
																/ HEADER_SIZE;
	
	header = (size_t*)buffer;
	new_alloc = buffer;
	*header = header + 1;
	new_alloc->next_free = *header;
	header = *header;

	while (header < (buffer + buffer_size))
	{
		*header = header + address_offset;
		header = *header;
	}
	
	header -= address_offset;
	*header = NULL;

	return new_alloc;
}

void *FSAAlloc(fsa_t *allocator)
{
	size_t *header = NULL;
	void *to_return = NULL;

	ASSERT_NOT_NULL(allocator);

	header = allocator->next_free;

	if (NULL == header)
	{
		return NULL;
	}
	to_return = header + 1;
	allocator->next_free = *header;
	*header = allocator;

	return to_return;
}

void FSAFree(void *block)
{
	size_t *header = NULL;
	fsa_t *allocator = NULL;

	ASSERT_NOT_NULL(block);

	header = block - HEADER_SIZE;
	allocator = *header;
	*header = allocator->next_free;
	allocator->next_free = header;

}

size_t FSANumOfAvailableBlocks(fsa_t *allocator)
{
	size_t *header = NULL;
	size_t count = 0;
	
	ASSERT_NOT_NULL(allocator);

	header = allocator->next_free;

	while (NULL != header)
	{
		header = *header;
		++count;
	}
		
	return count;
}







