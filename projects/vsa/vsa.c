/******************************************************************************
 *	Title:		Variable Storage Allocator
 *	Authour:	Alistair Hudson
 *	Reviewer:	Yurri
 *	Version:	01.03.2020.0
 ******************************************************************************/

/******INCLUDED FILES******/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "vsa.h"


/******MACROS******/
#define ASSERT_NOT_NULL(ptr) (assert(NULL != ptr))
#define HEADER_SIZE			 (sizeof(size_t))
#define PADDING(block)		 ((HEADER_SIZE - (block % HEADER_SIZE)) % HEADER_SIZE)

/******TYPEDEFS******/
struct allocator
{
	long free_space;
};

typedef struct block
{
	long size_of_block;
}block_t;

/******GLOBAL VARIABLES******/
static size_t ALLOCATOR_SIZE = sizeof(struct allocator);

/******INTERNAL FUNCTIONS******/
block_t *DeFrag(block_t *block, block_t *prev_block);
long ABSBlockSize(block_t *block);

/******FUNCTIONS******/
vsa_t *VSAInit(void *buffer, size_t buffer_size)
{
	vsa_t *new_vsa = NULL;
	block_t *first_block = NULL;
	block_t *final_block = NULL;

	ASSERT_NOT_NULL(buffer);
	
	buffer_size -= (buffer_size % HEADER_SIZE);
	new_vsa = buffer;
	new_vsa->free_space = (buffer_size - ALLOCATOR_SIZE - HEADER_SIZE);
	first_block = (block_t*)buffer + 1;
	first_block->size_of_block = (new_vsa->free_space - 2 * HEADER_SIZE);
	final_block = first_block + new_vsa->free_space/HEADER_SIZE;
	final_block->size_of_block = 0;

	return new_vsa;
}

void *VSAAlloc(vsa_t *allocator, size_t block_size)
{
	void *block = NULL;
	block_t *block_head = NULL;
	block_t *prev_block = NULL;
	long full_block = block_size + PADDING(block_size);
	long free_space = 0;

	ASSERT_NOT_NULL(allocator);

	block_head = (block_t*)allocator + 1;
	prev_block = block_head;
	while ((0 != block_head->size_of_block) && 
									(full_block > block_head->size_of_block))
	{
		prev_block = DeFrag(block_head, prev_block);
		block_head = prev_block + (HEADER_SIZE + ABSBlockSize(prev_block))
																/HEADER_SIZE;
	}

	if (0 != block_head->size_of_block)
	{
		free_space = block_head->size_of_block - (full_block + HEADER_SIZE);
		block_head->size_of_block = -full_block;
		block = block_head + 1;
		block_head += (HEADER_SIZE + full_block)/HEADER_SIZE;
		if (0 > free_space)
		{
			free_space = 0;
		}
		block_head->size_of_block = free_space;

	}

	return block;
}

void VSAFree(void *block)
{
	block_t *block_head = NULL;

	ASSERT_NOT_NULL(block);
	
	block_head = (block_t*)block - 1;
	block_head->size_of_block *= -1;
	
}

size_t VSABiggestChunk(const vsa_t *allocator)
{
	long chunk = 0;
	block_t *block_head = NULL;
	block_t *prev_block = NULL;

	ASSERT_NOT_NULL(allocator);

	block_head = (block_t*)allocator + 1;
	prev_block = block_head;

	while (0 != block_head->size_of_block)
	{
		prev_block = DeFrag(block_head, prev_block);
		block_head = prev_block + (HEADER_SIZE + ABSBlockSize(prev_block))
																/HEADER_SIZE;
		if (chunk < prev_block->size_of_block)
		{
			chunk = prev_block->size_of_block;
		}
	}

	return chunk;
}

block_t *DeFrag(block_t *block, block_t *prev_block)
{
	if ((0 < prev_block->size_of_block) && (0 < block->size_of_block) && 
														(prev_block != block))
		{
			prev_block->size_of_block += block->size_of_block + HEADER_SIZE; 
			block = prev_block;
		}

	return block;
}

long ABSBlockSize(block_t *block)
{
	long abs_size = block->size_of_block;
	if (0 > abs_size)
	{
		abs_size *= -1;
	}

	return abs_size;
}
