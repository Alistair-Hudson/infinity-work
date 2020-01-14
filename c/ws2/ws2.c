#include <stdio.h>
#include <string.h>
#include "ws2.h"
#include <stdlib.h>

size_t Strlen(const char *string)
{
	int length = 0;
	while (*string != 0x0)
	{
		++string;
		++length;
	}

	return length;
}

int Strcmp(const char *str1, const char *str2)
{
	int len1 = Strlen(str1);
	int len2 = Strlen(str2);
	int compare = 0;
	int i = 0;
	int j = 0;
	while((i <= len1) || (j <= len2))
	{
		if ((i >= len1) && (j <= len2))
		{
			compare -= *(str2+j);
		}else if ((i <= len1) && (j >= len2))
		{
			compare += *(str1+i);
		}else 
		{
			compare = *(str1+i) - *(str2+j);
		}
		if (compare != 0)
		{
			return compare;
			break;
		}
		++i;
		++j;
	}
	return 0;
}

char *Strcpy(char *str2, const char *str1)
{
	while(*str1 != '\0')
	{
		*str2 = *str1;
		++str1;
		++str2;
	}
	return 0;
}

char *Strncpy(char *str2, const char *str1, size_t n)
{

	for (int i = 0; i < n; ++i)
	{
		*str2 = *str1;
		++str1;
		++str2;
	}
	return 0;
}

char *StrLowerConvert(char *str)
{
	while(*str != '\0')
	{
		if ((*str > 'A') && (*str < 'Z'))
		{
			*str = *str + ('a'-'A');
		}
		++str;
	}
	return 0;
}

int Strcasecmp(char *str1, char *str2)
{
	StrLowerConvert(str1);
	StrLowerConvert(str2);
	int result = Strcmp(str1, str2);

	return result;	
}

char *Strchr(char *str, int ch)
{
	while(*str != '\0')
	{
		if (*str == ch)
		{
			return str;
			break;
		}
		++str;
	}
	return 0;
}

char *Strdup(char *str)
{
	char *output;
	output = str;
	return output;
}

char Strcat(char *dest, const char *src)
{
	int length = Strlen(dest);
	int added = Strlen(src);
	dest += length;
	for (int i = 0; i < added; ++i)
	{
		*dest = *src;
		++dest;
		++src;	
	}
	return 0;
}

char Strncat(char *dest, const char *src, size_t n)
{
	int length = Strlen(dest);
	dest += length;
	for (int i = 0; i < n; ++i)
	{
		*dest = *src;
		++dest;
		++src;	
	}
	return 0;
}

char *Strstr(char *hay, char *needle)
{	
	int j = 0;
	while(*hay != '\0')
	{
		if(*hay == *(needle+j))
		{
			++j;
		}else if (*(needle+j) == '\0')
		{	
			hay-=j;
			return hay;
			break;
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
	int length_span = Strlen(span);
	int char_count = 0;
	while(*initial != '\0')
	{
		for(int j = 0; j <= length_span; ++j)
		{
			if(*initial == *span)
			{
				++char_count;
				break;
			}else if((*span == '\0') && (char_count != 0))
			{
				return char_count;
			}
			++span;
		}
		++initial;
	}
	if (char_count == 0)
	{
		return char_count;
	}
	return 0;
}

char *Strtok(char *str, const char *delin)
{
	static char *buffer;
	char *start = buffer;
	if(str != NULL)
	{
		buffer = str;
	}
	int iter = 0;
	start = buffer;
	if(*buffer == '\0'){ return 0;}
	while(*buffer != '\0')
	{
		while(*delin != '\0')
		{
			if(*buffer == *delin)
			{
				*buffer = '\0';
				++buffer;
				return start;
			}
			++delin;
			++iter;
		}
		delin -= iter;
		iter = 0;
		++buffer;
		if(*buffer == '\0')
		{
			return start;
		}
	}
	
	return 0;
}

int IsPalindrome (char *str)
{
	int l = 0;
	int r = Strlen(str) -1;
	StrLowerConvert(str);
	while (l <= r)
	{
		if(*(str+l) != *(str+r))
		{
			return 0;
			break;
		}
		++l;
		--r;
	}
	if (l > r)
	{
		return 1;
	}
	return 0;
}

void Boom7(int from, int to)
{
	for( ; from <= to; ++from)
	{
		int hit = 0;
		for(int i = from; i > 0; i /= 10)
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
	*num1 = *num2;
	*num2 = temp;
}

void RmSpaces(char *str)
{
	char *buffer = str;
	char *start = buffer;
	int j = 0;
	while(*str != '\0')
	{
		*buffer = *str;
		if ((j == 0) && (*str == ' '))
		{
			++str;
			++j;
		}else if ((*(str+1) == '\0') && (*str == ' '))
		{
			++str;
		}else if ((*str == ' ') && (*(str+1) == ' '))
		{
			++str;
		}else
		{
			++str;
			++buffer;
			
		}
	}
	*buffer = '\0';
	Strcpy(str, start);
}

char *StringSum(char *num1, char *num2)
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
