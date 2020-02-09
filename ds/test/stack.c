#include<stdio.h> /*printf*/
#include<stdlib.h> /*malloc*/
#include<string.h> /*memcpy*/

#include "stack_ds.h"



/**you need to remove comments, if I can't understand the code without them it is badly written*/
/**remove printfs*/

struct stack
	{
		void * BaseOfData;
		void * MaxOfStack;/**these do not meet naming convention*/
		void * TopOfStack;

	} ;


stack_t * StackCreate(size_t capacity)/**change this to only require one malloc*/
{										/**It is an inefficent use of allocation*/
	/*allocate memory to new instance of structure stack, 
	and this will be returned. Also do memory allocation check*/	
	stack_t *newstack;
	newstack = malloc(sizeof(stack_t));

	if(NULL == newstack)
	{
		return NULL;
	}

	/*allocating memory for data storage within this structure */

	newstack->BaseOfData = (void*)malloc(sizeof(void*) * capacity);
/**sizeof(void*) should be a macro if I come back in 100 days will you know what it means*/
	if(NULL == newstack->BaseOfData)
	{
		return NULL;
	}

	/*Setting up the other pointers to their initial positions*/

	newstack->MaxOfStack = (size_t *)newstack->BaseOfData + capacity;
	newstack->TopOfStack = NULL; /*our top pointer is initially pointing to NULL if stack is empty*/
	
	printf("Stack is created and pointer to it returned\n");
	return newstack;
}


int IsStackEmpty(const stack_t *stack)
{
	/*By design of StackCreate() we set TopOfStack pointer to NULL when stack is empty*/

	if(NULL == stack->TopOfStack)
	{
		printf("This stack is empty\n");		
		return 1;
	}

	
	
	printf("This stack is not empty\n");
	return 0;
	 
}

size_t StackCapacity(const stack_t *stack)
{
	
	return ((char *)stack->MaxOfStack - (char *)stack->BaseOfData)/sizeof(void*);
}/**the above line is too long 80 characters max*/


size_t StackSize(const stack_t *stack)
{	
	if(NULL == stack->TopOfStack)

	{
	
		return 0; /*that is, stack is empty*/
	}

	
		
	return 1+((char *)stack->TopOfStack - (char *)stack->BaseOfData)/sizeof(void*);
	
	
}


int StackPush(stack_t *stack, void *element)
{
	
	/*Check if stack not full*/
	if(stack->TopOfStack >= stack->MaxOfStack)
		{
			printf("Nizzya: stack is full\n");
			return 0;
		}

	/*if it will be the first element to write, set top to first element, else, increment top pointer */

	if(NULL == stack->TopOfStack)
	{
		stack->TopOfStack = stack->BaseOfData;
	}

	else
	{
		stack->TopOfStack = (char *) stack->TopOfStack+ sizeof(void*);
	}
		
	memcpy(stack->TopOfStack, element, sizeof(void*)); /*!!!! need to check if casting to char* needed!*/

	printf("Element written successfully\n");

return 1;

}


int StackPop(stack_t *stack)
{
	if(NULL == stack->TopOfStack)/**Too many conditionals*/
	{
		return 0; /*that is, stack is empty*/
	}
	else if (stack->TopOfStack == stack->BaseOfData)
	{
		/*if top is on first element, we set it to NULL, thus making the stack empty*/		 
		stack->TopOfStack = NULL;
	}

	else
	{
		stack->TopOfStack = (char*) stack->TopOfStack - sizeof(void*);
	}
	
	
	return 1;
}


void *StackPeek(stack_t *stack)
{
	if(NULL == stack->TopOfStack)
	{
		return 0; /*that is, stack is empty*/
	}

	
	return stack->TopOfStack;
	
	
}


void StackDestroy(stack_t *stack)
{
	 /* release data inside the stack structure*/	
	free(stack->BaseOfData);
	/* set all internal pointers to NULL*/
	stack->BaseOfData = NULL; 
	stack->MaxOfStack = NULL;
	stack->TopOfStack = NULL;
	/* finally release memory allocated to stack structure itself*/
	free(stack);
	printf("Stack destroyed, memory freed\n");
}






