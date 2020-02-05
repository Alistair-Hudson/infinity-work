#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include "stack_ds.h"

/*****MACROS*****/
#define ELEMENT_SIZE (sizeof(void*))

/*****STRUCTURE TO HANDLE THE STACK******/
struct stack
{
	void *base;
	void *max;
	void *top;
};

/******FUNCTION DECLARATIONS********/
stack_t *StackCreate(size_t capacity);
void StackDestroy(stack_t *stack);

int StackPop(stack_t *stack);
int StackPush(stack_t *stack, void *data);
void *StackPeek(stack_t *stack);

size_t StackSize(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackCapacity(const stack_t *stack);

/******FUNCTION DEFINITIONS********/
stack_t *StackCreate(size_t capacity)
{
	stack_t *_stack = malloc((capacity * ELEMENT_SIZE) + sizeof(struct stack));
	assert(0 != _stack);
	_stack->base = _stack + 1;
	_stack->max = (size_t *)_stack->base + capacity;
	_stack->top = _stack->base;
	return _stack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack);
	stack = NULL;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	if(stack->base == stack->top) {return 1;}
	return 0;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return (((size_t)stack->max - (size_t)stack->base) / ELEMENT_SIZE);
}

int StackPush(stack_t *stack, void *data)
{
	size_t next_top_loc = (size_t)stack->top + ELEMENT_SIZE;
	assert(NULL != stack);
	if ((size_t)stack->max <= next_top_loc)
	{
		return 0;
	}
	*(size_t**)stack->top = data;
	*(size_t*)&stack->top += ELEMENT_SIZE;
	return 1;
}

void *StackPeek(stack_t *stack)
{
	assert(NULL != stack);
	if(StackIsEmpty(stack))
	{
		return 0;
	}
	return (size_t*)((size_t)(stack->top)-ELEMENT_SIZE);
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return (((size_t)stack->top - (size_t)stack->base) / ELEMENT_SIZE);
}

int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	if(StackIsEmpty(stack))
	{
		return 0;
	}
	*(size_t*)&stack->top -= ELEMENT_SIZE;
	return 1;
}
