#include <stdio.h>	/*standard inputs and outputs*/
#include <stdlib.h>	/*Standard library functions*/	
#include <string.h>	/*Handling strings*/
#include "ws5.h"

#define STRING_LIMIT (100)
#define NUM_FUNCS (5)

typedef int (*cmp_t)(const char*, const char*);
typedef int (*act_t)(char*);

typedef struct _str_hand
{
	char string[STRING_LIMIT];
	cmp_t compare;
	act_t action;
}str_handler_t;

static struct _str_hand str_handler[NUM_FUNCS];
enum statuses{SUCCESS, EXIT, OPEN, NO_STRING, NO_INPUT, NO_RENAME, NO_REMOVE};

static const int max_iterations = NUM_FUNCS -1;

static int CommandCmp(char *cmp_str)
{
	int i = max_iterations;
	while(i > 1)
	{
		if(str_handler[i].compare(str_handler[i].string, cmp_str) == 0)
		{
			return i;
		}
		--i;
	}
	return 0;
}
static int Compare (char *cmp_str)
{
	int action_call = 0;
	if(NULL == cmp_str)
	{
		perror("Error: ");
		return NO_STRING;
	}
	action_call = CommandCmp(cmp_str);
	if('<' == *cmp_str)
	{
		strcpy(str_handler[1].string, cmp_str+1);
		action_call = 1;
	}
	strcpy(str_handler[0].string, cmp_str);
	return action_call;
}

static int Exit(char *filename)
{
	printf("Exiting program %s, Have a nice day\n", filename);
	return EXIT;
}

static int Append(char *filename)
{
	FILE *file = fopen(filename, "a+");
	if(NULL == file)
	{
		perror("Error: ");
		return OPEN;
	}
	if(NULL == str_handler[0].string)
	{
		perror("Error: ");
		return NO_STRING;
	}
	fputs(str_handler[0].string, file);
	fclose(file);
	return SUCCESS;
}

static int Remove(char *filename)
{
	int file = remove(filename);
	if(0 != file)
	{
		perror("Error: ");
		return NO_REMOVE;
	}
	return SUCCESS;
}

static int CountLines(char *filename)
{
	FILE *file = fopen(filename, "r");
	int line_count = 0;
	char line[STRING_LIMIT];
	if(NULL == file)
	{
		perror("Error: ");
		return OPEN;
	}
	do
	{
		fgets(line, STRING_LIMIT, file);
		++line_count;
	}while (!EOF);
	printf("Line count = %d\n", line_count);
	return SUCCESS;
}

static int AppendToStart(char *filename)
{
	FILE *dest_file;
	FILE *src_file;
	int ret;
	char line[STRING_LIMIT];
	dest_file = fopen("temp.txt", "a+");
	src_file = fopen(filename, "a+");
	if(NULL == dest_file)
	{
		perror("Error: ");
		return OPEN;
	}
	if(NULL == src_file)
	{
		perror("Error: ");
		return OPEN;
	}
	if(NULL == str_handler[1].string)
	{
		perror("Error: ");
		return NO_STRING;
	}
	fputs(str_handler[1].string, dest_file);
	do
	{
		fgets(line, STRING_LIMIT, src_file);
		fputs(line, dest_file);
	}while(!EOF);
	fclose(dest_file);
	fclose(src_file);
	ret = rename("temp.txt", filename);
	if(0 != ret)
	{
		perror("Error:");
		return NO_RENAME;
	}
	return SUCCESS;
}
static int InitializeHandler()
{
	strcpy(str_handler[2].string, "-remove\n");
	strcpy(str_handler[3].string, "-count\n");
	strcpy(str_handler[4].string, "-exit\n");

	str_handler[0].compare = NULL;
	str_handler[1].compare = NULL;
	str_handler[2].compare = strcmp;
	str_handler[3].compare = strcmp;
	str_handler[4].compare = strcmp;

	str_handler[0].action = Append;
	str_handler[1].action = AppendToStart;
	str_handler[2].action = Remove;
	str_handler[3].action = CountLines;
	str_handler[4].action = Exit;
	
	return SUCCESS;
}

int EditFile(char *filename)
{
	int call;
	int status = InitializeHandler();
	char input[STRING_LIMIT];

	while(!status)
	{
		fgets(input, STRING_LIMIT, stdin);
		if(NULL == input)
		{
			perror("Error: ");
			return NO_INPUT;
		}
		call = Compare(input);
		status = str_handler[call].action(filename);

	}
	return 0;
}
