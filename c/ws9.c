#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <ctype.h> /*tolower*/
#define SIZE_WORD (8)
#define ASCII_OFFSET (48)
#define ASCII_OFFSET_CHAR (97)
#define NUM_CHAR (26)

#include "ws9.h"



static size_t SizeOfNumber(int a);
static size_t Power(size_t base , size_t exponent);

void *Memcpy(void *dest, const void *src, size_t size)
{
	char *dest_char = NULL;
	char *src_char = NULL;

	dest_char = (char *) dest;
	src_char = (char *) src;
	while(0 != ((size_t)dest_char % SIZE_WORD))
	{	
		* dest_char = * src_char;
		++dest_char;
		++src_char;
		--size; 
	}

	while(SIZE_WORD <= size)
	{
		*(size_t *) dest_char = *(size_t *) src_char;
		dest_char += SIZE_WORD;
		src_char += SIZE_WORD;
		size -= SIZE_WORD; 
	}

	while(0 < size)
	{
		*dest_char = *src_char;
		++dest_char;
		++src_char;
		--size; 
	}
	
	return dest;

}

void *Memset(void *dest, int c, size_t size)
{
	char *dest_char = NULL;
	size_t *buffer = NULL;
	size_t *buffer_start = NULL;
	int index = SIZE_WORD;

	/*Creation of the buffer filled with c on 8 bytes*/
	buffer = malloc(SIZE_WORD);
	if (!buffer)
	{
		return NULL;
	}
	buffer_start = buffer;

	while(0 < index)
	{
		* (char *) buffer = (char) c;
		++  *(char **) &buffer;
		--index; 
	}
	
	buffer = buffer_start;

	dest_char = (char *) dest;
	while(0 != ((size_t)dest_char % SIZE_WORD))
	{
		*dest_char = (char) c;
		++dest_char;
		--size; 
	}

	while(SIZE_WORD <= size)
	{
		*(size_t *) dest_char = *buffer;
		dest_char += SIZE_WORD;
		size -= SIZE_WORD; 
	}

	while(0 < size)
	{
		*dest_char = (char) c;
		++dest_char;
		--size; 
	}
	
	free(buffer);

	return dest;
}


void *Memmove(void *dest, const void *src, size_t size)
{
	char *dest_char = NULL;
	char *src_char = NULL;

	dest_char = (char *) dest + size - 1;
	src_char = (char *) src + size - 1;

	while(0 != ((size_t)dest_char % SIZE_WORD))
	{	
		printf("Loop 1\n");
		* dest_char = * src_char;
		--dest_char;
		--src_char;
		--size; 
	}

	while(SIZE_WORD <= size)
	{
		dest_char = dest_char - SIZE_WORD + 1;
		src_char = src_char - SIZE_WORD + 1;
		printf("Loop 2\n");		
		*(size_t *) dest_char = *(size_t *) src_char;
		size -= SIZE_WORD;
 		--dest_char ;
		--src_char;
	}

	while(0 < size)
	{
		printf("Loop 3\n");	
		*dest_char = *src_char;
		--dest_char;
		--src_char;
		--size; 
	}
	
	return dest;

}

char *Itoa(int value, char *str, int base)
{
	char c = 0;
	size_t index = 0;
	size_t len_str = SizeOfNumber(value);
	
	printf("%d\n", (int) len_str);

	str += len_str;

	*str = '\0';	

	for (index = 0; index < len_str; ++index)
	{
		--str;
		c = (value % base) + ASCII_OFFSET;
		*str = c;
		value = value/base;
	}

	return str;

}


static size_t SizeOfNumber(int a)
{
	int remain = a;	
	size_t count = 0;
	while(remain > 0)
	{
		remain = remain / 10;
		++count;
	}
	return count;
}

int Atoi(const char *str)
{
	int number = 0;
	size_t len_str = strlen(str);
	
	while (0 < len_str)
	{
		number += ((int) *str - ASCII_OFFSET) * Power(10, len_str - 1) ;
		--len_str;
		++str;
	}

	return number;

}

static size_t Power(size_t base , size_t exponent)
{
	size_t result = 1;	

	if (0 == exponent)
	{
		return result;
	}


	while(exponent > 0)
	{
		result = result * base;
		--exponent;
	}

	return result;
}

int IsLittleEndian()
{
	unsigned int x = 1;
	char *ptr_to_x = (char *) &x;

	return (*ptr_to_x);

}

void PrintLettersofArrays(const char *array1, size_t size1, const char *array2, size_t size2, const char *array3, size_t size3)
{
	size_t index = 0;
	size_t LookupTable[NUM_CHAR] = {0}; 
	size_t key = 0;
	char letter_to_print = '0';
	for (index = 0; index < size1; ++index)
	{
		key = (size_t) tolower(array1[index]) - ASCII_OFFSET_CHAR;
		LookupTable[key] = 1;
	}
	for (index = 0; index < size2; ++index)
	{
		key = (size_t) tolower(array2[index]) - ASCII_OFFSET_CHAR;
		if (1 == LookupTable[key])
		{
			LookupTable[key] = (size_t) tolower(array2[index]);
		}
	}
	for (index = 0; index < size3; ++index)
	{
		key = (size_t) tolower(array3[index]) - ASCII_OFFSET_CHAR;
		LookupTable[key] = 0;
	}
	printf("The letters appearing in the first two arrays, but not in the third are : ");
	for (index = 0; index < NUM_CHAR; ++index)
	{
		if(index == (LookupTable[index] - ASCII_OFFSET_CHAR))
		{
			letter_to_print = (char) (LookupTable[index]);
			printf("%c ", letter_to_print);
		}
	}
	printf("\n");
}




