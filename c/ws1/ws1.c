#include<stdio.h>

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

	while (number > 0)
	{
		int remain = number % 10;
		output_num = output_num * 10 + remain;
		number = number/10;
	}

	return(output_num);
}

void swap(int *array)
{
	
	int z = array[0];
	array[0] = array[1];
	array[1] = z;

}

int main()
{
	int hex_letters[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22};
	for (int i = 0; i < sizeof(hex_letters)/sizeof(int); i++)
	{
		printf("%c", hex_letters[i]);
	}
	
	printf("\n");


	float pos_exp = exponCalc(3);
	float neg_exp = exponCalc(-3);
	float zero_exp = exponCalc(0);
	int check = revNum(12340);
	printf("positive exponent 10^3 = %f \n", pos_exp);
	printf("negative exponent 10^-3= %f \n", neg_exp);
	printf("zero exponent 10^0 = %f \n", zero_exp);
	printf("reverse of the number 12340 = %d \n", check);

	int a[] = {5, 9};
	swap(a);
	printf("a = 5 and b = 9, swaped they are a = %d and b = %d \n", a[0], a[1]); 
	return(0);
}
