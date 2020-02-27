#ifndef __FSA_OL85_H__
#define __FSA_OL85_H__

/*******************************************************************************
                                 * OL85 API FSA
                                 * version 26.02.2020.1
 ******************************************************************************/

#include <stddef.h> /* size_t */

/* Fixed Size Allocator imitates the behavior of malloc and free */
typedef struct allocator fsa_t;

/*
 * Input: (void *)pointer to allocated buffer, (size_t)size of buffer in bytes ,
          (size_t)size of element in bytes .
 * Process: Create and initialize the allocator;
 * Return: (fsa_t *)pointer to the allocator;
 */
fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size);

/*
 * Input: (fsa_t *)pointer to allocator.
 * Process: allocate block of memory;
 * Return:(void *)return pointer to the block, return NULL - if fail;
 */
void *FSAAlloc(fsa_t *allocator);

/*
 * Input: (void *)pointer to block.
 * Process: free this block of memory;
 * Return: none;
 */
void FSAFree(void *block);

/*
 * Input: (fsa_t *)pointer to allocator.
 * Process:count free blocks;
 * Return:(size_t)amount of free blocks;
 */
size_t FSANumOfAvailableBlocks(fsa_t *allocator);

/*
 * Input: (size_t)amount of blocks, (size_t)size of block.
 * Process: calculate , how much memory should be alocated for this 
            amount of blocks with given size of block;
 * Return: (size_t)suggested size in bytes;
 */
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);


#endif /* __FSA_OL85_H__ */
