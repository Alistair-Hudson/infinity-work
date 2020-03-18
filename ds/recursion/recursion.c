/******************************************************************************
 *	Title:		Recusion Exercises
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.03.2020.0
 ******************************************************************************/
#include <stdio.h>		
#include <stdlib.h>
#include <assert.h>		/* assert */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct node node_t;

struct node
{
	int data;
	node_t *next;
};

node_t* FlipList(node_t* node);

int RecFibonacci(int element_index);

int IterFibonacci(int element_index);

size_t RecStrlen(const char *string);

int RecStrcmp(const char *str1, const char *str2); 	 					

char *RecStrcpy(char *str2, const char *str1);

char RecStrcat(char *dest, const char *src);

char *RecStrstr(const char *hay, const char *needle);	

/******FUNCTIONS******/
void SortedInsert(stack_t* stack, int x) 
{ 
    if (StackIsEmpty(stack) || x > StackPeek(stack)) 
    { 
        StackPush(stack, x); 
        return; 
    } 
  
    int temp = StackPeek(stack); 
	StackPop(stack);
    SortedInsert(stack, x); 
  
    StackPushush(stack, temp); 
} 
 
void SortStack(stack_t* stack) 
{ 
 
    if (!StackIsEmpty(stack)) 
    { 
        int x = StackPeek(stack);
		StackPop(stack); 
   
        SortStack(stack); 

        SortedInsert(stack, x); 
    } 
}

node_t* FlipList(node_t* node)
{

	if (NULL == node->next || NULL == node)
	{
		return node;
	}
	
	node_t* rest = FlipList(node->next);
	node->next->next = node;

	node->next = NULL;

	return rest;
}

size_t RecStrlen(const char *string)
{
	if ('\0' == *string)
	{
		return 0;
	}
	return 1 + RecStrlen(string + 1);
	
}

int RecStrcmp(const char *str1, const char *str2)
{
	if (*str1 != *str2)
	{
		return (*str1 - *str2);
	}
	if ('\0' == *str1 && '\0' == *str2)
	{
		return 0;
	}
	return RecStrcmp(str1 + 1, str2 + 1);
}

char *RecStrcpy(char *str2, const char *str1)
{
	*str2 = *str1;
	if ('\0' == *str1)
	{
		return NULL;
	}
	RecStrcpy(str2 + 1, str1 + 1);
}

char RecStrcat(char *dest, const char *src)
{
	if ('\0' != *dest)
	{
		RecStrcat(++dest, src);
	}
	else 
	{
		if('\0' != (*dest = *src))
		{
			RecStrcat(dest, src);
		}
		else
		{
			return NULL;
		}
	}
}

char *RecStrstr(const char *hay, const char *needle)
{

	if ('\0' == *needle)
	{
		return *hay;
	}
	if ('\0' == *hay)
	{
		return NULL;
	}
	if (*hay == *needle && RecStrstr(++hay, ++needle) == ++hay)
	{
		return *hay;
	}
	return RecStrstr(++hay, needle);
}

int RecFibonacci(int element_index)
{
	if (1 >= element_index)
	{
		return element_index;
	}
	
	return RecFibonacci(element_index - 1) + RecFibonacci(element_index - 2);
}

int IterFibonacci(int element_index)
{
	int result = 0;
	int prev1 = 1;
	int prev2 = 0;
	int iteration = 2;

	while (element_index >= iteration)
	{
		result = prev1 + prev2;
		prev2 = prev1;
		prev1 = result;
		++iteration;
	}
	return result;
}

int main()
{
	int fib_num = 9;
	char str[20] = "Hello";
	char str2[20] = "hello";


	printf("RecFib result for %d = %d\n", fib_num, RecFibonacci(fib_num));
	printf("IterFib result for %d = %d\n", fib_num, IterFibonacci(fib_num));
	printf("length of %s = %lu\n", str, RecStrlen(str));
	printf("compare %s w %s = %d\n", str, str, RecStrcmp(str, str));
	printf("compare %s w %s = %d\n", str, str2, RecStrcmp(str, str2));
	
	RecStrcpy(str, str2);
	printf("copy = %d\n",  RecStrcmp(str, str2));

	return 0;
}
