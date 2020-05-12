#ifndef __CBUFF_H__
#define __CBUFF_H__

/*******************************************************************************
                                 *  OL85 API 
                                 * version 1.0
 ******************************************************************************/

#include<stddef.h> /* size_t */
#include <sys/types.h>	/* ssize_t */
#include <unistd.h>

typedef struct cbuff cbuff_t;

/*
* Input:  size_t capacity
* Process: allocate memory for empty cbuffer
* Return: pointer to cbuff_t if successful, NULL if failed 
*/
cbuff_t*  CBuffCreate(size_t capacity);

/*
* Input:  pointer to cbuff_t
* Process: destroy the entire buffer (free memory)
* Return: none
*/
void CBuffDestroy(cbuff_t *cbuff);

/*
* Input:  pointer to cbuff_t
* Process: checks if cbuff_t has elelemnts
* Return: boolean int 1/0 
 */
int CBuffIsEmpty(const cbuff_t *cbuff);

/*
 * Input: pointer to constant cbuff_t
 * Process: Calculate difference between size and capacity
 * Return: size_t result
 */
size_t CBuffFreespace(const cbuff_t *cbuff);

/*
 * Input: pointer to constant cbuff_t
 * Process: Retrieve capacity from struct cbuff_t
 * Return: size_t capacity
 */
size_t CBuffCapacity(const cbuff_t *cbuff);

/*
 * Input: pointer to cbuff_t, void pointer to constant source, size_t number
 * of bytes to write;
 * Process: Copy specified numbger of bytes from source to cbuff_t;
 * Return: Number of bytes copied if successful / -1 if unsuccessful.
 */
ssize_t CBuffWrite(cbuff_t *cbuff, const void* source, size_t nbytes);

/*
 * Input: pointer to cbuff_t, void pointer to destination, size_t number
 * of bytes
 * Process: Retreive and/or copy specified numbger of bytes from cbuff_t to
 * destination
 * Return: Number of bytes retrieved if successful / -1 if unsuccessful.
 */
ssize_t CBuffRead(cbuff_t *cbuff, void* dest, size_t nbytes);



#endif /* __CBUFF_H__ */
