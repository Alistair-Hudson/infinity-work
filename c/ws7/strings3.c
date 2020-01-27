#include <stdio.h>
#include <string.h>
#include "ws2.h"
#include <stdlib.h>
#include <assert.h>

int IsPalindrome (const char *str)
{
	int r = Strlen(str)-1;
	char *char1 = (char *)str;
	char *char2 = (char *)(str+r);
	assert (str != NULL);

	while (char1 <= char2)
	{
		if(tolower(*char1) != tolower(*char2))
		{
			return 0;
		}
		++char1;
		--char2;
	}
	if (char1 > char2)
	{
		return 1;
	}
	return 0;
}

void Boom7(int from, int to)
{
	assert (from != NULL);
	assert (to != NULL);
	for( ; from <= to; ++from)
	{
		int hit = 0;
		int i = from;
		for(; i > 0; i /= 10)
		{
			if((i % 10) == 7)
			{
				hit = 1;
				break;
			}
		}
		if ((from % 7) == 0)
		{
			printf("BOOM\n");
		}else if(hit == 1) 
		{
			printf("BOOM\n");
		}else
		{
			printf("%d\n", from);
		}
	}
}

void RmSpaces(char *str)
{
	char *buffer = str;
	char *start = buffer;
	char *str_start = str;
	int j = 0;
	assert (str != NULL);
	while(*str != '\0')
	{
		*buffer = *str;
		if (((*str == ' ') || (*str == '\t')) && ((*(str+1) == ' ') || (*(str+1) == '\t')))
		{
			++str;
		}else if ((j == 0) && ((*str == ' ') || (*str == '\t')))
		{
			++str;
			++j;
		}else if ((*(str+1) == '\0') && ((*str == ' ') || (*str == '\t')))
		{
			++str;
		}else
		{
			++str;
			++buffer;
		}
	}
	*buffer = '\0';
	str = str_start;
	Strcpy(str, start);
}


