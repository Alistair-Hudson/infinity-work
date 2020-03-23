#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

int main()
{
	char equation[] = "1^2^3^4";
	double result = 0;
	
	Calculator(equation, &result);
	
	printf("result = %f\n", result);
	
	return 0;
}
