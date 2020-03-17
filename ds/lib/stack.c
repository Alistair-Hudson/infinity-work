#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include "stack.h"

/*****MACROS*****/
#define ELEMENT_SIZE (sizeof(void*))

/*****STRUCTURE TO HANDLE THE STACK******/
struct stack
{
	size_t capacity;
	size_t top;
	void **elements;
};

/******FUNCTION DECLARATIONS********/

/******FUNCTION DEFINITIONS********/
stack_t *StackCreate(size_t capacity)
{
	stack_t *_stack = malloc((capacity * ELEMENT_SIZE) + sizeof(struct stack));
	assert(0 != _stack);
	_stack->capacity = capacity;
	_stack->top = 0;
	_stack->elements = (void**)_stack + 3;
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
	return !stack->top;
}

size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->capacity;
}

int StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);
	if (stack->capacity <= stack->top)
	{
		return 0;
	}
	stack->elements[stack->top] = data;
	++stack->top;
	return 1;
}

void *StackPeek(stack_t *stack)
{
	assert(NULL != stack);
	if(StackIsEmpty(stack))
	{
		return 0;
	}
	return stack->elements[stack->top - 1];
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	return stack->top;
}

int StackPop(stack_t *stack)
{
	assert(NULL != stack);
	if(StackIsEmpty(stack))
	{
		return 0;
	}
	--stack->top;
	return 1;
}
