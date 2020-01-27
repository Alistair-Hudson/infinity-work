#include <stdio.h>
#include <string.h>
#include "ws2.h"
#include <stdlib.h>
#include <assert.h>

size_t Strlen(const char *string)
{
	int length = 0;
	assert (string != NULL);
	while (*string != 0x0)
	{
		++string;
		++length;
	}

	return length;
}

int Strcmp(const char *str1, const char *str2)
{
	int compare = 0;
	assert (str1 != NULL);
	assert (str2 != NULL);
	while(*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 == '\0' && *str2 != '\0')
		{
			compare -= *str2;
		}else if (*str1 != '\0' && *str2 == '\0')
		{
			compare += *str1;
		}else 
		{
			compare = *str1 - *str2;
		}
		if (compare != 0)
		{
			return compare;
		}
		++str1;
		++str2;
	}
	return 0;
}

int Strcasecmp(const char *str1, const char *str2)
{
	int compare = 0;
	char char1;
	char char2;
	assert (str1 != NULL);
	assert (str2 != NULL);
	while(*str1 != '\0' || *str2 != '\0')
	{
		char1 = tolower(*str1);
		char2 = tolower(*str2);
		if (*str1 == '\0' && *str2 != '\0')
		{
			compare -= char2;
		}else if (*str1 != '\0' && *str2 == '\0')
		{
			compare += char1;
		}else 
		{
			compare = char1 - char2;
		}
		if (compare != 0)
		{
			return compare;
		}
		++str1;
		++str2;
	}
	return 0;
}

size_t Strspn(const char *initial, const char *span)
{
	const char *span_end = span;
	int char_count = 0;
	assert (initial != NULL);
	assert (span != NULL);
	while(*initial != '\0')
	{
		while(*span != '\0')
		{
			if(*initial == *span)
			{
				++char_count;
				break;
			}
			++span;
			if(*span == '\0')
			{
				return char_count;
			}
		}
		span = span_end;
		++initial;
	} 
	return 0;
}

