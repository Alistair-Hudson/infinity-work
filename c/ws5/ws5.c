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

enum errors{ext, success, open};


int Compare (char *cmp_str)
{
	int i = 4;
	while(i > 1)
	{
		if(str_handler[i].compare(str_handler[i].string, cmp_str) == 0)
		{

			return i;
		}
		--i;
	}
	if(*cmp_str == '<')
	{
		return 1;
	}
	strcpy(str_handler[0].string, cmp_str);
	return 0;
}

int Exit(char *filename)
{
	return 0;
}

int Append(char *filename)
{
	FILE *file = fopen(filename, "a+");
	fputs(str_handler[0].string, file);
	fputc('\n', file);
	fclose(file);
	return 1;
}

int Remove(char *filename)
{
	int file = remove(filename);
	return 1;
}

int main()
{
	int call;
	char name[] = "ws5_output.txt";
	int active = 1;
	char input[50];

	str_handler[0].compare = strcmp;
	str_handler[0].action = Append;
	str_handler[1].compare = strcmp;
	str_handler[1].action = Append;
	strcpy(str_handler[2].string, "-remove");
	str_handler[2].compare = strcmp;
	str_handler[2].action = Remove;
	strcpy(str_handler[3].string,"-count");
	str_handler[3].compare = strcmp;
	str_handler[3].action = Append;
	strcpy(str_handler[4].string, "-exit");
	str_handler[4].compare = strcmp;
	str_handler[4].action = Exit;

	while(active)
	{
		scanf("%s", input);
		call = Compare(input);
		active = str_handler[call].action(name);

	}
	return 0;
}
