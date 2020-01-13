#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LenTest(char *test_str)
{
	int test_len = Strlen(test_str);
	int exp_len = strlen(test_str);
	if(test_len == exp_len)
	{
		printf("Length test passed");
	}else
	{
		printf("Length test failed");
	}
}

void CmpTest(char *test_str1, char *test_str2)
{
	int test_res = Strcmp(test_str1, test_str2);
	int exp_res = strcmp(test_str1, test_str2);
	if(test_res == exp_res)
	{
		printf("Compare test passed");
	}else
	{
		printf("Compare test failed");
	}
}

void CpyTest(char *test_str1, char *test_str2, char *test_str3)
{
	Strcpy(test_str1, test_str3);
	strpy(test_str2, test_str3);
	if(test_str1 == test_str3)
	{
		printf("Copy test passed");
	}else
	{
		printf("Copy test failed");
	}
}

void main()
{

}
