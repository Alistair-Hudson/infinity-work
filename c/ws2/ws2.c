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

char *Strcpy(char *str2, const char *str1)
{
	assert (str1 != NULL);
	assert (str2 != NULL);
	while(*str1 != '\0')
	{
		*str2 = *str1;
		++str1;
		++str2;
	}
	*str2 = '\0';
	return 0;
}

char *Strncpy(char *str2, const char *str1, size_t n)
{
	unsigned int i = 0;
	assert (str1 != NULL);
	assert (str2 != NULL);
	for (; i < n; ++i)
	{
		*str2 = *str1;
		++str1;
		++str2;
	}
	++str2;
	*str2 = '\0';
	return 0;
}

char StrLowerConvert(char ch)
{
	assert (ch != NULL);
	if ((ch > 'A') && (ch < 'Z'))
	{
		ch = ch + ('a'-'A');
		return ch;
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

char *Strchr(const char *str, int ch)
{
	assert (str != NULL);
	assert (ch != NULL);
	while(*str != '\0')
	{
		if (*str == ch)
		{	
			return (char *)str;
		}
		++str;
	}
	return 0;
}

char *Strdup(const char *str)
{
	char *output = (char *) malloc(Strlen(str)+1);
	assert (output);
	Strcpy(output, str);
	return output;
}

char Strcat(char *dest, const char *src)
{
	int length = Strlen(dest);
	int added = Strlen(src);
	int i = 0;
	assert (dest != NULL);
	assert (src != NULL);
	dest += length;
	for (; i < added; ++i)
	{
		*dest = *src;
		++dest;
		++src;	
	}
	*dest = '\0';
	return 0;
}

char Strncat(char *dest, const char *src, size_t n)
{
	int length = Strlen(dest);
	unsigned int i = 0;
	assert (dest != NULL);
	assert (src != NULL);
	dest += length;
	for (; i < n; ++i)
	{
		*dest = *src;
		++dest;
		++src;	
	}
	return 0;
}

char *Strstr(const char *hay, const char *needle)
{	
	int j = 0;
	assert (hay != NULL);
	assert (needle != NULL);
	while(*hay != '\0')
	{
		if(*hay == *(needle+j))
		{
			++j;
		}else if (*(needle+j) == '\0')
		{	
			hay -= j; 
			return (char *)hay;
		}else
		{
			j = 0;
		}
		++hay;
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

char *Strtok(char *str, const char *delin)
{
	static char *buffer;
	char *start = buffer;
	const char *del_start = delin;
	assert (str != NULL);
	assert (delin != NULL);
	if(str != NULL)
	{
		buffer = str;
	}
	start = buffer;
	if(*buffer == '\0'){ return 0;}
	while(*buffer != '\0')
	{
		while(*delin != '\0')
		{
			if(*buffer == *delin)
			{
				if(buffer != start)
				{
					*buffer = '\0';
					++buffer;
					return start;
				}else
				{
					++buffer;
					++start;
				}
			}
			++delin;
		}
		delin = del_start;
		++buffer;
		if(*buffer == '\0')
		{
			return start;
		}
	}
	
	return 0;
}

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

void Swap(int **num1, int **num2)
{
	int *temp = *num1;
	assert (num1 != NULL);
	assert (num2 != NULL);
	*num1 = *num2;
	*num2 = temp;
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

char *StringSum(const char *num1, const char *num2)
{
	int len1 = Strlen(num1);
	int len2 = Strlen(num2);
	int out_pos = (len1 > len2) ? (len1+1):(len2+1);
	char *output = (char *) malloc(out_pos);
	int buffer = 0;
	int carry = 0;
	while(out_pos >= 0)
	{
		if((*(num1+len1) == 0) && (*(num2+len2) == 0))
		{
			buffer = 0;
		}
		else if((len1 < 0) && (len2 < 0))
		{
			buffer = 48 + carry;
		}else if((len1 >= 0) && (len2 < 0))
		{
			buffer = *(num1+len1) + carry;
		}else if((len1 < 0) && (len2 >= 0))
		{
			buffer = *(num2+len2) + carry;
		}else
		{	
			buffer = (*(num1+len1) + *(num2+len2)) - 48 + carry;
		}
		
		if(buffer > 57)
		{
			buffer -= 10;
			carry = 1;
		}else
		{
			carry = 0;
		}
		*(output+out_pos) = buffer;
		--out_pos;
		--len1;
		--len2;
	}
	return output;
}
