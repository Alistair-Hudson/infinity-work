#include <stdio.h>
#include <string.h>

float exponCalc(int exponent)
{
	
	float result = 1;
	float base = 10;
	if (exponent <= 0)
	{
		exponent = -exponent;
		base = 1/base;
	}
	
	for (int i = 1; i <= exponent; i++)
	{
		result *= base;
	}
	
	return(result);
}

int revNum(int number)
{
	
	int output_num = 0;

	while (number != 0)
	{
		int remain = number % 10;
		output_num = output_num * 10 + remain;
		number = number/10;
	}

	return(output_num);
}

void swap(int *x, int *y)
{
	
	int z = *x;
	*x = *y;
	*y = z;

}

void txt2Hex(char *string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		printf("%02x", string[i]);
	}
}

void hex2Text (char *array)
{
	printf("%s\n", array);
}

void resultCompare (float result, float expected)
{
	if (result == expected)
	{
		printf("TRUE\n");
	}else
	{
		printf("FALSE\n");
	}
}

int main()
{
	char hex_letters[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22};

	hex2Text(hex_letters);

	printf("\n");
	
	printf("Hello World! in hex is:\n");
	txt2Hex("Hello World!");

	/*input and expected vaules for tests*/
	int pos_exp = 3;
	int neg_exp = -3;
	int zero_exp = 0;
	float expect_pos_exp_res = 1000;
	float expect_neg_exp_res = 0.001;
	float expect_zero_exp_res = 1;

	int pos_rev_num = 12340;
	int neg_rev_num = -12340;
	int expected_pos_rev_num = 4321;
	int expected_neg_rev_num = -4321;

	int int_a = 5;
	int int_b = 9;
	int expect_a = int_b;
	int expect_b = int_a;

	printf("\n");
	/*Tests*/
	float test_pos_exp = exponCalc(pos_exp);
	float test_neg_exp = exponCalc(neg_exp);
	float test_zero_exp = exponCalc(zero_exp);

	int test_pos_rev = revNum(pos_rev_num);
	int test_neg_rev = revNum(neg_rev_num);

	swap(&int_a, &int_b);
	
	/* comparisions to expected results*/
	printf("Postive exponent test works:\n");
	resultCompare(test_pos_exp, expect_pos_exp_res);
	printf("Negative exponent test works:\n");
	resultCompare(test_neg_exp, expect_neg_exp_res);
	printf("Zero exponent test works:\n");
	resultCompare(test_zero_exp, expect_zero_exp_res);

	printf("Postive reverse test works:\n");
	resultCompare(test_pos_rev, expected_pos_rev_num);
	printf("Negative reverse test works:\n");
	resultCompare(test_neg_rev, expected_neg_rev_num);

	printf("The Swap function works with both a positive and negative int: \n");
	resultCompare(int_a, expect_a); 
	/* end of tests*/

	return(0);
}
