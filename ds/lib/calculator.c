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
#define CHARACTER_MASK          (0xFF)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef enum STATE{EXIT, WAIT_OPERATOR, WAIT_OPERAND}state_t;

static char ASCII_TABLE[ASCII_RANGE] = {0};
static void InitASCII();

static calc_status_t SyntaxError(stack_t* stack, char* expression);
static calc_status_t SystemError(double* actor, double* actee);

static calc_status_t(*OperandLUT[ASCII_RANGE])(stack_t* operand_stack, 
											char* expression) = {SyntaxError};
static calc_status_t(*OperatorLUT[ASCII_RANGE])(stack_t* operator_stack, 
												char* operatr,
												double* result) = {SyntaxError};
                                    
static calc_status_t(*FunctionLUT[ASCII_RANGE])(double* actee, double* actor) 
																= {SystemError};

static void SetOperatorLUT(calc_status_t (*lookup_array[])
													(stack_t*, char*, double*));

static void SetOperandLUT(calc_status_t (*lookup_array[])(stack_t*, char*));

static void SetFunctionLUT(calc_status_t (*lookup_array[])
												(double*, double*));

static calc_status_t Add(double* addee, double* adder);

static calc_status_t Subtract(double* subtractee, double* subtracter);

static calc_status_t Multiply(double* multipliee, double* multiplier);

static calc_status_t Division(double* divisee, double* diviser);

static calc_status_t PushOperand(stack_t* operand_stack, char* expression);

static calc_status_t PushOperatorDM(stack_t* operator_stack, char* operatr, 
																double* result);

static calc_status_t PushOperatorAS(stack_t* operator_stack, char* operatr, 
																double* result);

static calc_status_t Calculate(stack_t* operator_stack, stack_t* operand_stack, 
																double* result);

/******FUNCTIONS******/
static void InitASCII()
{
    size_t index = 0;
    for (index = 0; index < ASCII_RANGE; ++index)
    {
        ASCII_TABLE[index] = index;
    }
}

static calc_status_t Calculate(stack_t* operator_stack, stack_t* operand_stack, 
																double* result)
{
    char *operatr = NULL;
    double *actor = NULL;
	double *actee = NULL;
    calc_status_t status = SUCCESS;

	operatr = (char*)StackPeek(operator_stack);
	StackPop(operator_stack);
	actor = (double*)StackPeek(operand_stack);
	StackPop(operand_stack);
	if (StackIsEmpty(operand_stack))
	{
		*result  = *actor;
		free(actor);
		return status;
	}
	actee = (double*)StackPeek(operand_stack);

	status = FunctionLUT[*operatr](actee, actor);

	*result = *actee;
	free(operatr);
	free(actor);

	free(actee);
    return status;
    
}

static calc_status_t PushOperand(stack_t* operand_stack, char* expression)
{
    char* buffer = NULL;
    double *operand = malloc(sizeof(double));
	*operand = strtod(expression, &buffer);
	StackPush(operand_stack, operand);
	strcpy(expression, buffer);
	return SUCCESS;
}

static calc_status_t PushOperatorDM(stack_t* operator_stack, char* operatr, 
																double* result)
{
	char *optr = malloc(sizeof(char));
	ASSERT_NOT_NULL(result);
	*optr = ASCII_TABLE[*operatr];
    StackPush(operator_stack, optr);
	return SUCCESS;
}

static calc_status_t PushOperatorAS(stack_t* operator_stack, char* operatr, 
																double* result)
{
	calc_status_t status = SUCCESS;
	char *optr = malloc(sizeof(char));
	if ('*' == *(char*)StackPeek(operator_stack) || 
									'/' == *(char*)StackPeek(operator_stack))
	{
		status = Calculate(operator_stack, operand_stack, result);		
	}
	*optr = ASCII_TABLE[*operatr];
    StackPush(operator_stack, optr);
	return status;
}

static calc_status_t Add(double* addee, double* adder)
{	
	*addee += *adder;
	return SUCCESS;
}

static calc_status_t Subtract(double* subtractee, double* subtracter)
{
	*subtractee -= *subtracter;
	return SUCCESS;
}

static calc_status_t Multiply(double* multipliee, double* multiplier)
{
	*multipliee *= *multiplier;
	return SUCCESS;
}

static calc_status_t Division(double* divisee, double* diviser)
{	
	if (0 == *diviser)
	{
		return MATH_ERROR;
	}
	*divisee /= *diviser;
	return SUCCESS;
}

static void SetOperatorLUT(calc_status_t (*lookup_array[])(stack_t*, char*, 
																	double*))
{
	lookup_array['+'] = PushOperatorAS;
	lookup_array['-'] = PushOperatorAS;
	lookup_array['*'] = PushOperatorDM;
	lookup_array['/'] = PushOperatorDM;
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

static void SetFunctionLUT(calc_status_t (*lookup_array[])(double*, double*))
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

static calc_status_t SystemError(double* actor, double* actee)
{
    ASSERT_NOT_NULL(actor);
    ASSERT_NOT_NULL(actee);
   
    return SYSTEM_ERROR;
}
calc_status_t Calculator(const char* expression, double* result)
{
	stack_t* operator_stack = NULL;
	stack_t* operand_stack = NULL;
	state_t state = WAIT_OPERAND;
	calc_status_t status = SUCCESS;
	size_t length = 0;
	char operatr = 0;
	char equation[1000] = {0};
	char *eqptr = equation;
	
	ASSERT_NOT_NULL(expression);

	length = strlen(expression);
	strcpy(eqptr, expression);
    
    InitASCII();
    
	operator_stack = StackCreate(length);
	operand_stack = StackCreate(length);

	SetOperatorLUT(OperatorLUT);
	SetOperandLUT(OperandLUT);
	SetFunctionLUT(FunctionLUT);
	
	while ((SUCCESS == status) && ('\0' != *eqptr))
	{
		switch (state)
		{
			case (WAIT_OPERAND):
				status = OperandLUT[*eqptr](operand_stack, eqptr);
				state = WAIT_OPERATOR;
				break;
			case (WAIT_OPERATOR):
				operatr = *eqptr;
				status = OperatorLUT[operatr](operator_stack, &operatr);
				++eqptr;
				state = WAIT_OPERAND;
				break;
		}

		if(' ' == *eqptr)
		{
			++eqptr;
		}

		if('\0' == *eqptr)
		{
			while (!StackIsEmpty(operator_stack) && 
											!StackIsEmpty(operand_stack))
			{
				status = Calculate(operator_stack, operand_stack, result);
			}
		}
	}
	StackDestroy(operand_stack);
	StackDestroy(operator_stack);
	return status;
}
