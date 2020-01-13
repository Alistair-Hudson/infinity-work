#include <stdio.h>
#include <string.h>
#include "ws2.h"
#include <stdlib.h>

size_t Strlen(const char *string)
{
	int length = 0;
	while (*(string + length) != 0x0)
	{
		++length;
	}

	return (length+1);
}

int Strcmp(const char *str1, const char *str2)
{
	int len1 = Strlen(str1);
	int len2 = Strlen(str2);
	int tot1 = 0;
	int tot2 = 0;
	int i = 0;
	int j = 0;
	while((i <= len1) || (j <= len2))
	{
		if ((i >= len1) && (j <= len2))
		{
			tot2 += *(str2+j);
		}else if ((i <= len1) && (j >= len2))
		{
			tot1 += *(str1+i);
		}else
		{
			tot1 += *(str1+i);
			tot2 += *(str2+j);
		}
		++i;
		++j;
	}
	/*if (tot1 > tot2)
	{
		return 1;
	}else if (tot1 < tot2)
	{
		return -1;
	}else if (tot1 == tot2)
	{
		return 0;
	}*/
	return (tot1 - tot2);
}

char *Strcpy(char *str2, const char *str1)
{
	int length = Strlen(str1);
	for (int i = 0; i < length; ++i)
	{
		*(str2+i) = *(str1+i);
	}
}

char *Strncpy(char *str2, const char *str1, size_t n)
{

	for (int i = 0; i < n; ++i)
	{
		*(str2+i) = *(str1+i);
	}
}

char *StrLowerConvert(char *str)
{
	char *output;
	int length = Strlen(str);
	for (int i = 0; i <= length; ++i)
	{
		if ((*(str+i) > 0x40) && (*(str+i) < 0x5b))
		{
			*(str+i) = *(str+i)+0x20;
		}
	}
	
}

int Strcasecmp(char *str1, char *str2)
{
	StrLowerConvert(str2);
	StrLowerConvert(str2);
	int result = Strcmp(str1, str2);

	return result;	
}

char *Strchr(char *str, int ch)
{
	int length = Strlen(str);
	for (int i = 0; i <= length; ++i)
	{
		if (*(str+i) == ch)
		{
			return (str+i);
			break;
		}
	}
}

char *Strdup(char *str)
{
	char *output;
	output = str;
	return output;
}

char Strcat(char *dest, const char *src)
{
	int length = Strlen(dest) -1;
	int added = Strlen(src);
	for (int i = 0; i < added; ++i)
	{
		*(dest+i+length) = *(src+i);	
	}
}

char Strncat(char *dest, const char *src, size_t n)
{
	int length = Strlen(dest) -1;
	char output[length+n];
	for (int i = 0; i < n; ++i)
	{
		*(dest+i+length) = *(src+i);	
	}
}

char *Strstr(char *hay, char *needle)
{
	int length = Strlen(hay);
	char *output;	
	int j = 0;
	for(int i = 0; i <= length; ++i)
	{
		if(*(hay+i) == *(needle+j))
		{
			++j;
		}else if (*(needle+j) == 0x0)
		{	
			output = (hay+i-j);
			return output;
			break;
		}else
		{
			j = 0;
		}
	}
}


size_t Strspn(const char *initial, const char *span)
{
	int length_init = Strlen(initial)-1;
	int length_span = Strlen(span);
	int char_count = 0;
	for(int i = 0; i < length_init; ++i)
	{
		for(int j = 0; j < length_span; ++j)
		{
			if(*(initial+i) == *(span+j))
			{
				++char_count;
				break;
			}else if((*(span+j) == 0x0) && (char_count != 0))
			{
				return char_count;
			}
		}
	}
	if (char_count == 0)
	{
		return char_count;
	}
}

char *Strtok(char *str, const char *delin)
{
	static char *buffer;
	static int previous = 0;
	static int length = 0;
	static int end = 0;
	if(str != NULL)
	{
		previous = 0;
		length = Strlen(str);
		buffer = str;
	}
	char *output = (char *)malloc(length);
	for(int i = previous; i <= length; ++i)
	{	
		if(end == 1)
		{
			return 0x0;
			break;
		}else if(*(buffer+i) == *delin)
		{
			previous = ++i;
			return output;
			break;
		}else if(*(buffer+i) == 0x0)
		{
			end = 1;
			return output;
			break;
		}
		*(output+i-previous) = *(buffer+i);
	}
}

int IsPalindrome (char *str)
{
	int l = 0;
	int r = Strlen(str) -2;
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
}

void Boom7(int from, int to)
{
	for(from; from <= to; ++from)
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
	int length = Strlen(str);
	char *buffer = (char *) malloc(length);
	int j = 0;
	for (int i = 0; i <= length; ++i)
	{
		*(buffer+j) = *(str+i);
		if ((i == 0) && (*(str+i) == 32))
		{
			--j;
		}else if ((i == (length-1)) && (*(str+i) == 32))
		{
			--j;
		}else if ((*(str+i) == 32) && (*(str+i-1) == 32))
		{
			--j;
		}
		++j;
	}
	for(j; j <= length; ++j)
	{
		*(buffer+j) = 0x0;
	}
	Strcpy(str, buffer);
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
