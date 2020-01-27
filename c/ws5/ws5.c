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
struct str_handler_t str_handler[NUM_FUNCS];

enum statuses{EXIT, SUCCESS, OPEN, NO_STRING, NO_INPUT, NO_RENAME, NO_REMOVE};

static const int max_iterations = NUM_FUNCS -1;

static int Compare (char *cmp_str)
{
	int i = max_iterations;
	if(NULL == cmp_str)
	{
		perror("Error: ");
		return NO_STRING;
	}
	while(i > 1)
	{
		if(str_handler[i].compare(str_handler[i].string, cmp_str) == 0)
		{
			return i;
		}
		--i;
	}
	if('<' == *cmp_str)
	{
		strcpy(str_handler[1].string, cmp_str+1);
		return 1;
	}
	strcpy(str_handler[0].string, cmp_str);
	return 0;
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
	if(NULL == file)
	{
		perror("Error: ");
		return OPEN;
	}
	while (1)
	{
		if(fgetc(file) == '\n')
		{
			++line_count;
		}
		if (feof(file))
		{
			printf("Line count = %d\n", line_count);
			break;
		}
	}
	return SUCCESS;
}

static int AppendToStart(char *filename)
{
	FILE *dest_file;
	FILE *src_file;
	int ret;
	int chr;
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
	while(1)
	{
		chr = fgetc(src_file);
		if(feof(src_file))
		{
			break;
		}
		fputc(chr, dest_file);
	}
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

str_handler[NUM_FUNCS] = {
						{NULL, NULL, Append}, /*default*/
						{NULL, NULL, AppendToStart},
						{"-remove\n", strcmp, Remove},
						{"-count\n", strcmp, CountLines},
						{"-exit\n", strcmp, Exit}
						};

int EditFile(char *filename)
{
	int call;
	int status = SUCCESS;
	char input[STRING_LIMIT];

	while(status)
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
