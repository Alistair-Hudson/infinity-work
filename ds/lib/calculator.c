/******************************************************************************
 *	Title:		Calculator
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	16.03.2020.0
 ******************************************************************************/
#include <stdio.h>		/*TODO*/
#include <stdlib.h>
#include <assert.h>		/* assert */
#include <string.h>		/* strlen */

#include "calculator.h"
#include "stack.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define ASCII_RANGE				(256)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef enum STATE{EXIT, WAIT_OPERATOR, WAIT_OPERAND}state_t;

static calc_status_t SyntaxError(stack_t* stack, char* expression);

static calc_status_t(*OperandLUT[ASCII_RANGE])(stack_t* operand_stack, char* expression) = {SyntaxError};
static calc_status_t(*OperatorLUT[ASCII_RANGE])(stack_t* operator_stack, char* operatr) = {SyntaxError};
                                    
static calc_status_t(*FunctionLUT[ASCII_RANGE])(double* actee, double* actor, 
                                                                double* result);

static void SetOperatorLUT(calc_status_t (*lookup_array[])(stack_t*, char*));

static void SetOperandLUT(calc_status_t (*lookup_array[])(stack_t*, char*));

static void SetFunctionLUT(calc_status_t (*lookup_array[])(double*, double*, double*));

static calc_status_t Add(double* addee, double* adder, double* result);

static calc_status_t Subtract(double* subtractee, double* subtracter, double* result);

static calc_status_t Multiply(double* multipliee, double* multiplier, double* result);

static calc_status_t Division(double* divisee, double* diviser, double* result);

static calc_status_t PushOperand(stack_t* operand_stack, char* expression);

static calc_status_t PushOperator(stack_t* operator_stack, char* operatr);

static calc_status_t Calculate(stack_t* calc_stack, double* result);

/******FUNCTIONS******/
static calc_status_t Calculate(stack_t* calc_stack, double* result)
{
    char *operatr = NULL;
    double *actor = NULL;
    double *actee = NULL;
    calc_status_t status = SUCCESS;
/*    stack_t* buffer = StackCreate(StackSize(calc_stack));
*/    
    operatr = (char*)StackPeek(calc_stack);
    StackPop(calc_stack);
    actor = (double*)StackPeek(calc_stack);
    StackPop(calc_stack);
    actee = (double*)StackPeek(calc_stack);
    
    status = FunctionLUT[*operatr](actee, actor, result);
    
    return status;
    
}

static calc_status_t PushOperand(stack_t* operand_stack, char* expression)
{
    char* buffer = NULL;
	double operand = strtod(expression, &buffer);
	StackPush(operand_stack, &operand);
	strcpy(expression, buffer);
	return SUCCESS;
}

static calc_status_t PushOperator(stack_t* operator_stack, char* operatr)
{
	char operate = *operatr;
	StackPush(operator_stack, &operate);
	return SUCCESS;
}

static calc_status_t Add(double* addee, double* adder, double* result)
{	
	*result = *addee + *adder;
	return SUCCESS;
}

static calc_status_t Subtract(double* subtractee, double* subtracter, double* result)
{
	*result = *subtractee + *subtracter;
	return SUCCESS;
}

static calc_status_t Multiply(double* multipliee, double* multiplier, double* result)
{
	*result = *multipliee + *multiplier;
	return SUCCESS;
}

static calc_status_t Division(double* divisee, double* diviser, double* result)
{	
	if (0 == *diviser)
	{
		return MATH_ERROR;
	}
	*result = *divisee + *diviser;
	return SUCCESS;
}

static void SetOperatorLUT(calc_status_t (*lookup_array[])(stack_t*, char*))
{
	lookup_array['+'] = PushOperator;
	lookup_array['-'] = PushOperator;
	lookup_array['*'] = PushOperator;
	lookup_array['/'] = PushOperator;
}

static void SetOperandLUT(calc_status_t(*lookup_array[])(stack_t*, char*))
{
	lookup_array['0'] = PushOperand;
	lookup_array['1'] = PushOperand;
	lookup_array['2'] = PushOperand;
	lookup_array['3'] = PushOperand;
	lookup_array['4'] = PushOperand;
	lookup_array['5'] = PushOperand;
	lookup_array['6'] = PushOperand;
	lookup_array['7'] = PushOperand;
	lookup_array['8'] = PushOperand;
	lookup_array['9'] = PushOperand;
}

static void SetFunctionLUT(calc_status_t (*lookup_array[])(double*, double*, double*))
{
	lookup_array['+'] = Add;
	lookup_array['-'] = Subtract;
	lookup_array['*'] = Multiply;
	lookup_array['/'] = Division;

}

static calc_status_t SyntaxError(stack_t* stack, char* expression)
{
	ASSERT_NOT_NULL(stack);
	ASSERT_NOT_NULL(expression);
	return SYNTAX_ERROR;
}

calc_status_t Calculator(const char* expression, double* result)
{
	stack_t* operator_stack = NULL;
	stack_t* operand_stack = NULL;
	state_t state = WAIT_OPERAND;
	calc_status_t status = SUCCESS;
	size_t length = 0;
	char operatr = 0;
	char *equation = NULL;
	
	ASSERT_NOT_NULL(expression);

	length = strlen(expression);
	strcpy(equation, expression);

	operator_stack = StackCreate(length);
	operand_stack = StackCreate(length);

	SetOperatorLUT(OperatorLUT);
	SetOperandLUT(OperandLUT);
	SetFunctionLUT(FunctionLUT);
	
	while ((SUCCESS == status) && ('\0' != *equation))
	{
		switch (state)
		{
			case (WAIT_OPERAND):
				status = OperandLUT[*equation](operand_stack, equation);
				state = WAIT_OPERATOR;
				break;
			case (WAIT_OPERATOR):
				operatr = *equation;
				status = OperatorLUT[operatr](operator_stack, &operatr);
				++equation;
				state = WAIT_OPERAND;
				break;
		}
		printf("%lf\n", *(double*)StackPeek(operand_stack));

		if(' ' == *equation)
		{
			++equation;
		}
		
		if('\0' == *equation)
		{
		    while(!StackIsEmpty(operator_stack))
		    {
		        StackPush(operand_stack, StackPeek(operator_stack));
		        StackPop(operator_stack);
		    }
		    status = Calculate(operand_stack, result);
		}
	}
	StackDestroy(operand_stack);
	StackDestroy(operator_stack);
	return status;
}
