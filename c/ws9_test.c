#include <stdio.h> /*standard inputs and out puts. ie printf*/
#include <stdlib.h> /*for malloc*/
#include <string.h>/*for string functions such ie strlen*/
#include <assert.h>/*for assert*/
#include "ws9.c"

void MemcpyTest()
{
	char src[] = "123456789ABCDEF";
	char dest_test[] = "abcdefghijklmnopqrstuvwxyz";
	char dest_exp[] = "abcdefghijklmnopqrstuvwxyz";
	size_t bytes_to_copy = 10;
	size_t bytes_to_cmp = 16;
	Memcpy(dest_test, src, bytes_to_copy);
	memcpy(dest_exp, src, bytes_to_copy);
	
	if( 0 != memcmp(dest_test, dest_exp, bytes_to_cmp))
	{
		printf("Memcpy failed\n");
	}
	Memcpy(dest_test, dest_test, bytes_to_copy);
	memcpy(dest_exp, dest_exp, bytes_to_copy);

	if( 0 == memcmp(dest_test, dest_exp, bytes_to_cmp))
	{
		printf("Memcpy passed\n");
	}
	else
	{
		printf("Memcpy failed\n");
	}
}

void MemmoveTest()
{
	char src[] = "123456789ABCDEF";
	char dest_test[] = "abcdefghijklmnopqrstuvwxyz";
	char dest_exp[] = "abcdefghijklmnopqrstuvwxyz";
	size_t bytes_to_copy = 10;
	size_t bytes_to_cmp = 16;
	Memmove(dest_test, src, bytes_to_copy);
	memmove(dest_exp, src, bytes_to_copy);
	
	if( 0 != memcmp(dest_test, dest_exp, bytes_to_cmp))
	{
		printf("Memmove failed\n");
	}
	Memcpy(dest_test, dest_test, bytes_to_copy);
	memcpy(dest_exp, dest_exp, bytes_to_copy);

	if( 0 == memcmp(dest_test, dest_exp, bytes_to_cmp))
	{
		printf("Memmove passed\n");
	}
	else
	{
		printf("Memmove failed\n");
	}
}

void MemsetTest()
{
	int character = 'Z';
	char dest_test[] = "abcdefghijklmnopqrstuvwxyz";
	char dest_exp[] = "abcdefghijklmnopqrstuvwxyz";
	size_t bytes_to_copy = 10;
	size_t bytes_to_cmp = 16;
	Memset(dest_test, character, bytes_to_copy);
	memset(dest_exp, character, bytes_to_copy);
	
	if( 0 != memcmp(dest_test, dest_exp, bytes_to_cmp))
	{
		printf("Memset failed\n");
	}
	else
	{
		printf("Memset passed\n");
	}
}

void ItoaTest()
{
	char exp[] = "-10A";
	char out[5];
	Itoa(-266, out, 16);

	if(0 == strcasecmp(exp, out))
	{
		printf("Itoa passed\n");
	}
	else
	{
		printf("Itoa failed\n");
	}
}

void AtoiTest()
{
	int test = Atoi("-159");
	if(-159 == test)
	{
		printf("Atoi passed\n");
	}
	else
	{
		printf("Atoi failed\n");
	}
}

int main()
{
	char arr1[] = "HelloWorrld";
	char arr2[] = "Walkondown";
	char arr3[] = "ld";
	int endian = IsLittleEndian();
	MemcpyTest();
	MemmoveTest();
	MemsetTest();
	ItoaTest();
	AtoiTest();
	printf("Endian: %d\n", endian);
	PrintLettersofArrays(	arr1, sizeof(arr1), 
							arr2, sizeof(arr2), 
							arr3, sizeof(arr3));
	return 0;
}
