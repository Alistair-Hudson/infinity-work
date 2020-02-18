#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void MathSoln(int *array, size_t size)
{
	size_t index = 0;
	int factorial = 1;
	size_t iteration = 1;
	int array_prod = 1;
	int sum = 0;
	int array_sum = 0;
	int prod_miss = 0;
	int sum_miss = 0;
	int missing1 = 0;
	int missing2 = 0;

	for(iteration = 1; (size+2) >= iteration; ++iteration)
	{
		factorial *= iteration;
		sum += iteration;
	}
	
	for(index = 0; size > index; ++index)
	{
		array_prod *= array[index];
		array_sum += array[index];
	}

	prod_miss = factorial/array_prod;
	sum_miss = sum - array_sum;

	missing1 = -sum_miss + sqrt((sum_miss * sum_miss) - 4 * prod_miss);
	missing1 /= -2;

	missing2 = -sum_miss - sqrt((sum_miss * sum_miss) - 4 * prod_miss);
	missing2 /= -2;

	printf("missing numbers are: %d, %d\n", missing1, missing2);

}

void XORSoln(int *array, size_t size)
{
	int index = 1;
	int xor = array[0];
	int set_bit = 0;
	int missing1 = 0;
	int missing2 = 0;

	for(index = 1; index < size; ++index)
	{
		xor ^= array[index];
	}
	
	for(index = 1; index <= (size + 2); ++index)
	{
		xor ^= index;
	}
	
	set_bit = xor & ~(xor-1);
	
    for (index = 0; index < size; ++index) 
    { 
        if (array[index] & set_bit) 
            missing1 ^= array[index];
        else
            missing2 ^= array[index];
    } 
    for (index = 1; index <= (size + 2); ++index) 
    { 
        if (index & set_bit) 
            missing1 ^= index;
        else
            missing2 ^= index;
    } 
	printf("missing numbers are: %d, %d\n", missing1, missing2);
}

int main()
{
	int array[] = {1, 3, 5, 2, 6, 7, 9};

	MathSoln(array, 7);
	XORSoln(array, 7);

	return 0;
}
