#include <stdio.h>
#include <string.h>
#include "cbuffer.h"

#define ALL_PASSED		(3)
int Stage1Tests()
{
	cbuff_t *cbuff_ptr = CBuffCreate(20);
	
	if(!CBuffIsEmpty(cbuff_ptr))
	{
		printf("Is empty failed\n");
		return 0;
	}
	
	if(20 != CBuffCapacity(cbuff_ptr))
	{
		printf("Capacity failed\n");
		return 0;
	}

	CBuffDestroy(cbuff_ptr);
	return 1;
}

int WriteTest()
{
	cbuff_t *cbuff_ptr = CBuffCreate(20);
	char str1[] = "Hello";
	char str2[] = "123456789ABCDEFG";
	ssize_t byte_write_check = 0;
	
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	
	if(CBuffIsEmpty(cbuff_ptr))
	{
		printf("Failed to Write to buffer\n");
		return 0;
	}
	if(byte_write_check != strlen(str1))
	{
		printf("Failed to completely write to buffer\n");
		return 0;
	}
	
	byte_write_check = CBuffWrite(cbuff_ptr, str2, strlen(str2));
	
	if(byte_write_check != (strlen(str2)-1))
	{
		printf("Failed to stop writing when full\n");
		return 0;
	}

	CBuffDestroy(cbuff_ptr);

	return 1;

}

int ReadTest()
{
	cbuff_t *cbuff_ptr = CBuffCreate(20);
	char str1[] = "Hello";
	char str2[20] = {0};
	ssize_t byte_write_check = 0;
	
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1)+1);
	byte_write_check = CBuffRead(cbuff_ptr, str2, strlen(str1)+1);
	if(strcmp(str1, str2))
	{
		printf("Failed to Read or write correctly\n");
		return 0;
	}

	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	byte_write_check = CBuffWrite(cbuff_ptr, str1, strlen(str1));
	byte_write_check = CBuffRead(cbuff_ptr, str2, strlen(str1)*3+1);
	if(byte_write_check != strlen(str1)*3+1)
	{
		printf("Failed to completely read from buffer\n");
		return 0;
	}
	
	byte_write_check = CBuffRead(cbuff_ptr, str2, strlen(str1)+2);

	if(!CBuffIsEmpty(cbuff_ptr))
	{
		printf("Failed to stop writing when empty\n");
		return 0;
	}

	CBuffDestroy(cbuff_ptr);
	return 1;
}

int main()
{
	int pass = 0;	
	
	pass += Stage1Tests();
	pass += WriteTest();
	pass += ReadTest();

	if(ALL_PASSED == pass)
	{
		printf("\n");
		printf("\n");
		printf("ALL PASSED\n");
		printf("\n");
		printf("\n");
	}

	return 0;
}
