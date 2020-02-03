#include <stdio.h> /*standard inputs and out puts. ie printf*/
#include <stdlib.h> /*for malloc*/
#include <string.h>/*for string functions such ie strlen*/
#include <assert.h>/*for assert*/
#include "ws9.h"

/******************MACROS***********************/
#define WORD_SIZE 			(sizeof(size_t))
#define NO_LETTERS			26
#define IS_LITTLE_ENDIAN() 	(1 == *(char*)&(sizeof(char)))? 1 : 0

/******************FUNCTIONS***********************/
static char *ReverseStr(char *str)
{
	char temp;
	char *end_of_str = str + strlen(str) - 1;

	assert(NULL != str);

	while (str < end_of_str)
	{
		temp = *str;
		*str = *end_of_str;
		*end_of_str = temp;
		++str;
		--end_of_str;
	}

	return 0;
}

void *Memcpy(void *dest, const void *src, size_t size)
{
	unsigned int bytes_used = 0;
	
	assert(NULL != dest);
	assert(NULL != src);

	while ((0 != (size_t)dest % (size_t)WORD_SIZE) && (size >= bytes_used))
	{
		*(char*)dest = *(char*)src;
		++*(size_t*)&dest;
		++*(size_t*)&src;
		++bytes_used;
	}
	while (size >= bytes_used + WORD_SIZE)
	{
		*(size_t*)dest = *(size_t*)src;
		*(size_t*)&dest += WORD_SIZE;
		*(size_t*)&src += WORD_SIZE;
		bytes_used += WORD_SIZE;
	}
	while (size > bytes_used)
	{
		*(char*)dest = *(char*)src;
		++*(size_t*)&dest;
		++*(size_t*)&src;
		++bytes_used;
	}
}

void *Memmove(void *dest, const void *src, size_t size)
{
	unsigned int bytes_remaining = size;

	assert(NULL != dest);
	assert(NULL != src);

	if (((size_t)src + size) < (size_t)dest)
	{
		Memcpy(dest, src, size);
	}
	else
	{
		*(size_t*)&dest += size;
		*(size_t*)&src += size;
		while (0 < bytes_remaining)
		{
			*(char*)dest = *(char*)src;
			--*(size_t*)&dest;
			--*(size_t*)&src;
			--bytes_remaining;
		}
	}
}

void *Memset(void  *dest, int character, size_t size)
{
	unsigned int bytes_used = 0;
	void *buffer = malloc(WORD_SIZE);
	void *buffer_start = buffer;
	int buffer_fill = WORD_SIZE;

	assert(NULL != dest);

	while (0 < buffer_fill)
	{
		*(char*)buffer = (char)character;
		++*(size_t*)&buffer;
		--buffer_fill;
	}
	while ((0 != (size_t)dest % (size_t)WORD_SIZE) && (size >= bytes_used))
	{
		*(char*)dest = (char)character;
		++*(size_t*)&dest;
		++bytes_used;
	}
	while (size >= bytes_used + WORD_SIZE)
	{
		*(size_t*)dest = *(size_t*)buffer_start;
		*(size_t*)&dest += WORD_SIZE;
		bytes_used += WORD_SIZE;
	}
	while (size > bytes_used)
	{
		*(char*)dest = (char)character;
		++*(size_t*)&dest;
		++bytes_used;
	}
	free(buffer_start);
	buffer = NULL;
}

char *Itoa(int value, char *str, int base)
{
	char *str_start;
	int digit = 0;

	assert(NULL != str);
	
	if( 2 > base)
	{
		printf("Base must be greater than or equal to 2");
		return 0;
	}
	if(0 > value)
	{
		*str = '-';
		value *= -1;
		++str;	
	}
	str_start = str;
	while(0 != value)
	{
		digit = value % base;
		value /= base;
		*str = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
		++str;
	} 
	*str = '\0';
	ReverseStr(str_start);
	return 0;
}

int Atoi(const char *str)
{
	int value = 0;
	int minus = 1;

	assert(NULL != str);

	if ('-' == *str)
	{
		minus = -1;
		++str;
	}
	do
	{
		if(('0' <= *str) && ('9' >= *str))
		{
			value += *str -'0';
		}
		else
		{
			return 0;
		}
		value *= 10;
		++str;
	}while(0 != *str);
	return (minus*value/10);
}

int IsLittleEndian()
{
	int dummy = 1;
	if (1 == *(char*)&dummy)
	{
		return 1;
	}
	return 0;
}

void PrintLettersofArrays(	const char *arr1, size_t size1, 
							const char *arr2, size_t size2,
							const char *arr3, size_t size3)
{
	
	char *buffer = (char*)malloc(NO_LETTERS+1);
	int letters_remain = NO_LETTERS;

	while(0 < size1 && 0 != *arr1)
	{

		if('a' <= tolower(*arr1) && 'z' >= tolower(*arr1))
		{
			*(buffer+tolower(*arr1)-'a') = 1;
			++arr1;
			--size1;
		}
		else
		{
			printf("invalid character detetcted\n");
			break;
		}
	}
	while(0 < size2 && 0 != *arr2)
	{
		if('a' <= tolower(*arr2) && 'z' >= tolower(*arr2))
		{
			*(buffer+tolower(*arr2)-'a') *= 2;
			++arr2;
			--size2;
		}
		else
		{
			printf("invalid character detetcted\n");
			break;
		}
	}
	while(0 <= letters_remain)
	{

		if('a' <= tolower(*arr3) && 'z' >= tolower(*arr3))
		{
			*(buffer+tolower(*arr3)-'a') = 0;
			++arr3;
		}
		else if(1 < *(buffer+letters_remain-1))
		{
			printf("%d ", letters_remain);
			printf("%c\n", (char)(letters_remain + 'a' -1));
		}
		--letters_remain;
	}
	free(buffer);
	buffer = NULL;
}


