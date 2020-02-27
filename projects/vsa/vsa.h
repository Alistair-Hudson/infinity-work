
#ifndef __VSA_OL85_H__
#define __VSA_OL85_H__

/*******************************************************************************
                                 * OL85 API VSA
                                 * version 27.02.2020.1
 ******************************************************************************/

#include <stddef.h> /* size_t */

/* Variable Size Allocator imitates the behavior of malloc and free */
typedef struct allocator vsa_t;


/*
 * Input: (void *)pointer to allocated buffer, (size_t)size of buffer in bytes.
 * Process: Create and initialize the allocator;
 * Return: (vsa_t *)pointer to the allocator;
 */
vsa_t *VSAInit(void *buffer, size_t buffer_size);

/*
 * Input: (vsa_t *)pointer to allocator and size of the block.
 * Process: allocate block of memory, defragments if needed;
 * Return:(void *)return pointer to the block or NULL if there is no sufficient chunk;
 */
void *VSAAlloc(vsa_t *allocator, size_t block_size);

/*
 * Input: (void *)pointer to block.
 * Process: free this block of memory;
 * Return: none;
 */
void VSAFree(void *block);

/*
 * Input: (vsa_t *)pointer to allocator.
 * Process: looks for the biggest chunk available, defragments if needed;
 * Return:(size_t)size of the biggest chunk found;
 */
size_t VSABiggestChunk(const vsa_t *allocator);




#endif /* __VSA_OL85_H__ */
