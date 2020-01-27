#include <stdio.h>
#include <string.h>
#include "ws2.h"
#include <stdlib.h>
#include <assert.h>

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

