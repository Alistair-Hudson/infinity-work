#include <stdio.h>/*for printf and sprintf*/
#include <stdlib.h>
#include <string.h>/*for strcpy and strcat*/

#define ARRAY_SIZE (7)
#define MAX_STR_LEN (100)
#define ADD_VAL (10)
/*MACROS*/
#define MAX2(a, b) ((a > b) ? a : b)
#define MAX3(a, b, c) ((a > b) ? MAX2(a,c) : MAX2(b, c))
#define SIZEOF_VAR(var) ((char *)(&var+1)-(char*)(&var))
#define SIZEOF_TYPE(type) ((size_t)(1 + ((type*)0)))

typedef int (*add_t)(void**, const int);
typedef int (*free_t)(void*);
typedef int (*print_t)(void*);

typedef struct action_t
{
	add_t add;
	free_t free;
	print_t print;
}action_struct;

typedef struct element_t
{
	void* data;
	struct action_t *action;
}element_struct;

static int AddToInt(void **add_to, const int added)
{
	*(int*)add_to += added;
	return 0;	
}

static int AddToString(void **add_to, const int added)
{
	char int_string[MAX_STR_LEN];
	char *buffer = (char *)malloc(MAX_STR_LEN);
	sprintf(int_string, "%d", added);
	strcpy(buffer, *add_to);
	strcat(buffer, int_string);
	*add_to = buffer;
	free(buffer);
	buffer = NULL;
	return 0;
}

static int AddToFloat(void **add_to, int added)
{
	*(float*)add_to += added;
	return 0;
}

static int PrintInt(void *to_print)
{
	printf("%d\n", *(int*)&to_print);
	return 0;
}

static int PrintString(void *to_print)
{
	printf("%s\n", to_print);
	return 0;
}

static int PrintFloat(void *to_print)
{
	printf("%f\n", *(float*)&to_print);
	return 0;
}

static int FreeInt(void *to_free)
{
	return 0;
}

static int FreeFloat(void *to_free)
{
	return 0;
}

static int FreeString(void *to_free)
{
	return 0;
}

static struct action_t int_actions = {AddToInt, FreeInt, PrintInt};
static struct action_t float_actions = {AddToFloat, FreeFloat, PrintFloat};
static struct action_t string_actions = {AddToString, FreeString, PrintString};

static struct element_t array_of_types[ARRAY_SIZE];

static int IntInitializer(int element, int value)
{
	*(int*)&array_of_types[element].data = value;
	array_of_types[element].action = &int_actions;
	return 0;
}

static int FloatInitializer(int element, float value)
{
	*(float*)&array_of_types[element].data = value;
	array_of_types[element].action = &float_actions;
	return 0;
}

static int StringInitializer(int element, char *value)
{
	array_of_types[element].data = value;
	array_of_types[element].action = &string_actions;
	return 0;
}
static int ArrayInitializer()
{
	IntInitializer(0, 88);
	IntInitializer(1, 13);
	IntInitializer(2, 66);
	FloatInitializer(3, 3.14);
	FloatInitializer(4, 2.71);
	StringInitializer(5, "Hello world");
	StringInitializer(6, "Bob's your uncle");
	return 0;
}

static int PrintArray()
{
	int index;
	for(index = 0; index < ARRAY_SIZE; ++index)
	{
		array_of_types[index].action->print(array_of_types[index].data);
	}
	return 0;
}

static int AddToArray()
{
	int index;
	for(index = 0; index < ARRAY_SIZE; ++index)
	{
		array_of_types[index].action->add(&array_of_types[index].data, ADD_VAL);
	}
	return 0; 
}

static int FreeArray()
{
	int index;
	for(index = 0; index < ARRAY_SIZE; ++index)
	{
		array_of_types[index].action->free(array_of_types[index].data);
	}
	return 0; 
}

int main()
{
	ArrayInitializer();
	PrintArray();
	AddToArray();
	PrintArray();
	FreeArray();
	return 0;
}
