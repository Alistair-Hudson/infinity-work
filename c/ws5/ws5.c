#include <stdio.h>	/*standard inputs and outputs*/
#include <stdlib.h>	/*Standard library functions*/	
#include <string.h>	/*Handling strings*/
#include "ws5.h"

typedef int (*cmp_t)(const char*, const char*);
typedef int (*act_t)(char*);

typedef struct _str_hand
{
	char string[50];
	cmp_t compare;
	act_t action;
}STR;
struct _str_hand str_handler[5];

enum statuses{EXIT, SUCCESS, OPEN, NO_STRING, NO_INPUT, NO_RENAME, NO_REMOVE};

int Compare (char *cmp_str)
{
	int i = 4;
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

int Exit(char *filename)
{
	printf("Exiting program %s, Have a nice day\n", filename);
	return EXIT;
}

int Append(char *filename)
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

int Remove(char *filename)
{
	int file = remove(filename);
	if(0 != file)
	{
		perror("Error: ");
		return NO_REMOVE;
	}
	return SUCCESS;
}

int CountLines(char *filename)
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

int AppendToStart(char *filename)
{
	FILE *dest_file;
	FILE *src_file;
	int ret;
	int chr;
	dest_file = fopen("temp.txt", "a+");
	src_file = fopen(filename, "r");
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

int EditFile(char *filename)
{
	int call;
	int status = 1;
	char input[50];
	int i = 0;
/*Permenant string values*/
	strcpy(str_handler[2].string, "-remove\n");
	strcpy(str_handler[3].string, "-count\n");
	strcpy(str_handler[4].string, "-exit\n");
/*Assign strcmp to all structures*/
	for(; 4 >= i; ++i)
	{
		str_handler[i].compare = strcmp;
	}
/*Assign actions to structures*/
	str_handler[0].action = Append;
	str_handler[1].action = AppendToStart;
	str_handler[2].action = Remove;
	str_handler[3].action = CountLines;
	str_handler[4].action = Exit;

	while(status)
	{
		fgets(input, 50, stdin);
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
