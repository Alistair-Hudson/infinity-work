#ifndef __STACK_DS__
#define __STACK_DS__

#include <stddef.h>  /* size_t */

/* pointer to the structure that represents stack */
typedef struct stack stack_t;


/* 
 * The function creates the stack_t structure with given capacity 
 *
 * Return value:
 * pointer to the stack_t structure or NULL in case of creation failed
 * 
 * */
stack_t * StackCreate(size_t capacity);


/*
 * The function deletes stack_t and frees memory
 *
 * */
void StackDestroy(stack_t *stack);


/*
 * The function deletes the top element in the given stack_t
 * 
 * Return value:
 * 1 - operation was successfull
 * 0 - operation was unsuccessfull
 * 
 * */
int StackPop(stack_t *stack);


/*
 * The function puts the element into the stack_t
 * 
 * Return value:
 * 1 - adding the element was successfull
 * 0 - adding the element was unsuccessfull
 *
 * */
int StackPush(stack_t *stack, void *element);


/*
 * The function returns pointer that stores the last added element 
 * in the stack_t 
 * 
 * Note: NULL can be stored as value as well
 *
 * */
void *StackPeek(stack_t *stack);


/*
 * The function accepts pointer to stack_t structure and returns the number
 * of elements in this structure
 * 
 * */
size_t StackSize(const stack_t *stack);


/*
 * The function accepts pointer to stack_t structure and checks if it empty
 *
 * Return value:
 * 1 - the stack is empty
 * 0 - the stack is non-empty
 * 
 * */
int IsStackEmpty(const stack_t *stack);


/*
 * The function returns the capacity value of the given stack_t structure
 *
 * */
size_t StackCapacity(const stack_t *stack);


#endif /* __STACK_DS__ */
