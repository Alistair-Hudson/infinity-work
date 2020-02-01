#include <stdio.h> /*standard inputs and out puts. ie printf*/
#include <stdlib.h> /*for malloc*/
#include <string.h>/*for string functions such ie strlen*/

#define WORD_SIZE (sizeof(size_t))

static char *ReverseStr(char *str)
{
	char temp;
	char *end_of_str = str + strlen(str) - 1;
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
	unsigned int bytes_used = 0;
	
	while ((0 != (size_t)dest % (size_t)WORD_SIZE) && (size >= bytes_used))
	{

		++bytes_used;
	}
}

void *Memset(void  *dest, int character, size_t size)
{
	unsigned int bytes_used = 0;
	void *buffer = malloc(WORD_SIZE);
	void *buffer_start = buffer;
	int buffer_fill = WORD_SIZE;

	while (0 <= buffer_fill)
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
	free(buffer);
	buffer = NULL;
}

char *Itoa(int value, char *str, int base)
{
	char *str_start = str;
	int digit = 0;
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

int ISLittleEndian()
{

	return 1;
}

int main()
{
	char dest[] = "123456789abcdefg";
	char src[] = "abcdefghijklmnop";
	Memset(dest, 'H', 13);
	printf("after: %s\n", dest);
	return 0;
}	
