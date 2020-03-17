#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

int main()
{
	char equation[] = "3+2";
	double result = 0;
	
	Calculator(equation, &result);
	
	printf("result = %f", result);
	
	return 0;
}
