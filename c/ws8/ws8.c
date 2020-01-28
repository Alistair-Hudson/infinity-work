#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE (7)
#define MAX_STR_LEN (50)

typedef int (*add_t)(void*, const int);
typedef int (*free_t)(void*);
typedef int (*print_t)(void*);

typedef struct action_t
{
	add_t add;
	free_t free;
	print_t print;
}action_struct;

static int AddToInt(void *add_to, const int added)
{
	*(int*)&add_to += added;
printf("%d\n", *(int*)&add_to);
	return 0;
	
}

static int AddToString(void *add_to, const int added)
{
/*	*add_to += added;*/
	return 0;
}

static int AddToFloat(void *add_to, const int added)
{
/*	*add_to += added;*/
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
	free(to_free);
	return 0;
}

static struct action_t int_actions = {AddToInt, FreeInt, PrintInt};
static struct action_t float_actions = {AddToFloat, FreeFloat, PrintFloat};
static struct action_t string_actions = {AddToString, FreeString, PrintString};

typedef struct element_t
{
	void* data;
	struct action_t *action;
}element_struct;

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
	array_of_types[element].data = malloc(MAX_STR_LEN);
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
int main()
{
	int x;
	ArrayInitializer();
	PrintArray();
	/*array_of_types[0].data = */array_of_types[0].action->add(array_of_types[0].data, 10);
	PrintArray();
	return 0;
}
