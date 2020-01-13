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
	strcpy(test_str2, test_str3);
	if(test_str1 == test_str2)
	{
		printf("Copy test passed");
	}else
	{
		printf("Copy test failed");
	}
}

void CpynTest(char *test_str1, char *test_str2, char *test_str3, int n)
{
	Strncpy(test_str1, test_str3, n);
	strncpy(test_str2, test_str3, n);
	if(test_str1 == test_str2)
	{
		printf("Copy n test passed");
	}else
	{
		printf("Copy n test failed");
	}
}

void CaseCmpTest(char *test_str1, char *test_str2)
{
	int test_res = Strcasecmp(test_str1, test_str2);
	int exp_res = strcasecmp(test_str1, test_str2);
	if(test_res == exp_res)
	{
		printf("Case cmp test passed");
	}else
	{
		printf("Case cmp test failed");
	}
}

void ChrTest(char *test_str, int ch)
{
	char *test_ret = Strchr(test_str, ch);
	char *exp_ret = strchr(test_str, ch);
	if(test_ret == exp_ret)
	{
		printf("Chr test passed");
	}else
	{
		printf("Chr test failed");
	}
}

void DupTest(char *test_str)
{
	char *test_ret = Strdup(test_str);
	char *exp_ret = strdup(test_str);
	if(test_ret == exp_ret)
	{
		printf("Dup test passed");
	}else
	{
		printf("Dup test failed");
	}
}


void CatTest()
{

}

void CatnTest()
{

}

void StrTest(char *test_hay, char *test_needle)
{
	char *test_ret = Strstr(test_hay, test_needle);
	char *exp_ret = strstr(test_hay, test_needle);
	if(test_ret == exp_ret)
	{
		printf("Str test passed");
	}else
	{
		printf("Str test failed");
	}
}

void SpnTest(char *test_str, char *test_span)
{
	int test_len = Strspn(test_str, test_span);
	int exp_len = strspn(test_str, test_span);
	if(test_len == exp_len)
	{
		printf("Spn test passed");
	}else
	{
		printf("Spn test failed");
	}
}

void TokTest()
{

}

void PalindromeTest()
{
	int total_pass = 0;
	if(IsPalindrome("HANNAH") == 1){++total_pass;}
	if(IsPalindrome("Hannah") == 1){++total_pass;}
	if(IsPalindrome("ABC123") == 0){++total_pass;}
	if(IsPalindrome("12321") == 1){++total_pass;}
	if(IsPalindrome("!@# #@!") == 1){++total_pass;}
	printf("Palindrome test passed %d times", total_pass);
}

void Boom7Test()
{
	
}

void SwapTest()
{
	int num1 = 6;
	int num2 = 9;
	int *add1 = &num1;
	int *add2 = &num2;
	Swap(&add1, &add2);

	if((num1 == add2) && (num2 == add1)
	{
		printf("Swap test passed");
	}else
	{
		printf("Swap test failed");
	}
}

void SumTest()
{
	int total_pass = 0;
	char *res;
	res = StringSum("1234", "851");
	if(res == "2085"){++total_pass;}
	printf("Sum test passed %d times", total_pass);
}

void main()
{

}
