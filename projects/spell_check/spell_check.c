#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hash_table.h"

#define LETTERS			(27)
#define STRING_LIMIT	(1000)
size_t IndexWords(void* str)
{
	size_t index = 0;
	if ('A' <= *(char*)str && 'Z' >= *(char*)str)
	{
		index = (*(char*)str - 'A') + 1;
	}
	else if ('a' <= *(char*)str && 'z' >= *(char*)str)
	{
		index = (*(char*)str - 'a') + 1;
	}

	return index;
}

int StrcmpWrapper(void* str1, void* str2)
{
	return strcmp((char*)str1, (char*)str2);
}

char* NewLine(char* src)
{
	char* new_line = NULL;
	new_line = malloc(STRING_LIMIT);
	strcpy(new_line, src);
	return new_line;
}

void LoadDictionaryToHTable(htable_t* htable)
{
	FILE* dict;
	char* word_store = malloc(STRING_LIMIT * 500000);
	char* word = word_store;
	
	dict = fopen("/usr/share/dict/american-english", "r");
	
	do
	{
		fscanf(dict, "%s", word);
		printf("%s\n", word);
		HTableInsert(htable, word);
		word += STRING_LIMIT;
	}while(!EOF);
}

int main()
{
	char input[STRING_LIMIT];
	char* output = NULL;
	htable_t* htable = HTableCreate(IndexWords, LETTERS, StrcmpWrapper);
	
	LoadDictionaryToHTable(htable);

	while(1)
	{
		fgets(input, STRING_LIMIT, stdin);
		output = (char*)HTableFind(htable, &input);
		printf("%s", output);
	}

}
