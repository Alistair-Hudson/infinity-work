#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ws2.c"

void LenTest(char *test_str)
{
	printf("%s\n", test_str);
	int test_len = Strlen(test_str);
	int exp_len = strlen(test_str);
	if(test_len == exp_len)
	{
		printf("Length test passed\n");
	}else
	{
		printf("Length test failed\n");
		printf("test = %d, exp = %d\n", test_len, exp_len);
	}
}

void CmpTest(char *test_str1, char *test_str2)
{
	printf("Test = %s, Exp = %s\n", test_str1, test_str2);
	int test_res = Strcmp(test_str1, test_str2);
	int exp_res = strcmp(test_str1, test_str2);
	if(test_res == exp_res)
	{
		printf("Compare test passed\n");
	}else
	{
		printf("Compare test failed\n");
		printf("test = %d, exp = %d\n", test_res, exp_res);
	}
}

void CpyTest(char *test_str1, char *test_str2, char *test_str3)
{
	Strcpy(test_str1, test_str3);
	strcpy(test_str2, test_str3);
	if(strcmp(test_str1, test_str2) == 0)
	{
		printf("Copy test passed\n");
		printf("Test = %s, exp = %s\n", test_str1, test_str2);
	}else
	{
		printf("Copy test failed\n");
		printf("Test = %s, exp = %s\n", test_str1, test_str2);
	}
}

void CpynTest(char *test_str1, char *test_str2, char *test_str3, int n)
{
	Strncpy(test_str1, test_str3, n);
	strncpy(test_str2, test_str3, n);
	if(strcmp(test_str1, test_str2) == 0)
	{
		printf("Copy n test passed\n");
		printf("Test = %s, exp = %s\n", test_str1, test_str2);
	}else
	{
		printf("Copy n test failed\n");
		printf("Test = %s, exp = %s\n", test_str1, test_str2);
	}
}

void CaseCmpTest(char *test_str1, char *test_str2)
{
	int test_res = Strcasecmp(test_str1, test_str2);
	int exp_res = strcasecmp(test_str1, test_str2);
	if(test_res == exp_res)
	{
		printf("Case cmp test passed\n");
	}else
	{
		printf("Case cmp test failed\n");
		printf("test = %d, exp = %d\n", test_res, exp_res);
	}
}

void ChrTest(char *test_str, int ch)
{
	char *test_ret = Strchr(test_str, ch);
	char *exp_ret = strchr(test_str, ch);
	if(test_ret == exp_ret)
	{
		printf("Chr test passed\n");
	}else
	{
		printf("Chr test failed\n");
		printf("test = %s, exp = %s\n", test_ret, exp_ret);
	}
}

void DupTest(char *test_str)
{
	char *test_ret = Strdup(test_str);
	char *exp_ret = strdup(test_str);
	if(strcmp(test_ret, exp_ret) == 0)
	{
		printf("Dup test passed\n");
		printf("test = %s, exp = %s\n", test_ret, exp_ret);
	}else
	{
		printf("Dup test failed\n");
		printf("test = %s, exp = %s\n", test_ret, exp_ret);
	}
}


void CatTest(char *test_base, char *exp_base, char *append)
{
	Strcat(test_base, append);
	strcat(exp_base, append);
	if(strcmp(test_base, exp_base) == 0)
	{
		printf("Cat test passed\n");
		printf("test = %s, exp = %s\n", test_base, exp_base);
	}else
	{
		printf("Cat test failed\n");
		printf("test = %s, exp = %s\n", test_base, exp_base);
	}
}

void CatnTest(char *test_base, char *exp_base, char *append, int n)
{
	Strncat(test_base, append, n);
	strncat(exp_base, append, n);
	if(strcmp(test_base, exp_base) == 0)
	{
		printf("Cat n test passed\n");
		printf("test = %s, exp = %s\n", test_base, exp_base);
	}else
	{
		printf("Cat n test failed\n");
		printf("test = %s, exp = %s\n", test_base, exp_base);
	}
}

void StrTest(char *test_hay, char *test_needle)
{
	char *test_ret = Strstr(test_hay, test_needle);
	char *exp_ret = strstr(test_hay, test_needle);
	if(test_ret == exp_ret)
	{
		printf("Str test passed\n");
	}else
	{
		printf("Str test failed\n");
		printf("test = %s, exp = %s\n", test_ret, exp_ret);
		
	}
}

void SpnTest(char *test_str, char *test_span)
{
	printf("Span = %s\n", test_span);
	int test_len = Strspn(test_str, test_span);
	int exp_len = strspn(test_str, test_span);
	if(test_len == exp_len)
	{
		printf("Spn test passed\n");
	}else
	{
		printf("Spn test failed\n");
		printf("test = %d, exp = %d\n", test_len, exp_len);
	}
}

void TokTest(char *test_str, char *delin)
{
	int round = 0;
	char *test_ret = Strtok(test_str, delin);
	char *exp_ret = strtok(test_str, delin);
	while((test_ret != NULL) && (exp_ret != NULL))
	{
		++round;
		test_ret = Strtok(NULL, delin);
		exp_ret = strtok(NULL, delin);
	}
	if(test_ret == exp_ret)
	{
		printf("Tok test passed\n");
	}else
	{
		printf("Tok test failed\n");
		printf("test = %s, exp = %s\n, round = %d", test_ret, exp_ret, round);
	}
}

void PalindromeTest()
{	
	printf("Palindrome Test:\n");
	int total_pass = 0;
	char test1[] ="HANNAH";
	char test2[] ="Hannah";
	char test3[] ="ABCdef123";
	char test4[] ="12321";
	char test5[] ="!@# #@!";
	if(IsPalindrome(test1) == 1){++total_pass;}
	if(IsPalindrome(test2) == 1){++total_pass;}
	if(IsPalindrome(test3) == 0){++total_pass;}
	if(IsPalindrome(test4) == 1){++total_pass;}
	if(IsPalindrome(test5) == 1){++total_pass;}
	printf(" passed %d times\n", total_pass);
	if(total_pass == 5){printf("Complete pass\n");}
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

	if((num1 == *add2) && (num2 == *add1))
	{
		printf("Swap test passed\n");
	}else
	{
		printf("Swap test failed\n");
	}
}

void SumTest()
{
	int total_pass = 0;
	char *res;
	res = StringSum("1234", "851");
	//if(res == "2085"){++total_pass;}
	printf("Sum test passed %d times", total_pass);
}

int main()
{
	/*Testing variables*/
	/*Length test*/
	char test_len[] = "Length is 12";
	/*Cmp tests*/
	char test_cmp[] = "Hello";
	char exp_cmp_equ[] = "Hello";
	char exp_cmp_gtr[] = "hello";
	char exp_cmp_lss[] = "HELLO";
	char exp_cmp_lng[] = "Hello+";
	/*Copy, copy n, and Dup tests*/
	char cpy[] = "this is the copy";
	char test[] = "this is the test";
	char exp[] = "this is the expected";
	char n_test[] = "12345";
	char n_exp[] = "12345";
	char n_test_lng[] = "123456";
	char n_exp_lng[] = "123456";
	int n = 5;
	/*Chr test*/
	int ch = ' ';
	/*Cat and Cat n tests*/
	char base[15] = "hello";
	char append[] = " world";
	/*Str and Spn tests*/
	char hay[] = "Hello world!";
	char needle[] = " wor";
	char span[] = "Hell";
	/*Tok test*/
	char source[] = "Hello-Shalom-Ki ora";
	char delin[] = "-";

	/*Function test order*/
	/*Length Test*/
	LenTest(test_len);
	/*Cmp and case compare tests*/
	CmpTest(test_cmp, exp_cmp_equ);
	CmpTest(test_cmp, exp_cmp_gtr);
	CmpTest(test_cmp, exp_cmp_lss);
	CmpTest(test_cmp, exp_cmp_lng);
	CaseCmpTest(test_cmp, exp_cmp_lss);
	/*Copy, copy n and Dup tests*/
	CpyTest(test, exp, cpy);
	CpynTest(n_test, n_exp, cpy, n);
	CpynTest(n_test_lng, n_exp_lng, cpy, n);
	DupTest(cpy);
	/*Chr test*/
	ChrTest(test, ch);
	/*Cat and Cat n tets*/
	CatTest(base, base, append);
	CatnTest(base, base, append, n);
	/*Str and Spn tests*/
	StrTest(hay, needle);
	SpnTest(hay, span);
	/*Tok test*/
	TokTest(source, delin);
	/*Palindrome tests*/
	PalindromeTest();
	/*Swap test*/
	SwapTest();

	return 0;
}
