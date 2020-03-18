/******************************************************************************
 *	Title:		Calculator
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.03.2020.0
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

typedef struct calculator
{
	stack_t* operator_stack;
	stack_t* operand_stack;
	state_t state;
}calc_t;

static char ASCII_TABLE[ASCII_RANGE] = {0};
static void InitASCII();

static calc_status_t SyntaxErrorOperand(calc_t* calc, char* expression);
static calc_status_t SyntaxErrorOperator(calc_t* calc, char* expression, 
																double* result);
static calc_status_t SystemError(double* actor, double* actee);

static calc_status_t(*OperandLUT[ASCII_RANGE])(calc_t* calc, char* expression)
														= {SyntaxErrorOperand};
static calc_status_t(*OperatorLUT[ASCII_RANGE])(calc_t* calc, char* operatr, 
										double* result) = {SyntaxErrorOperator};
                                    
static calc_status_t(*FunctionLUT[ASCII_RANGE])(double* actee, double* actor) 
																= {SystemError};

static void SetOperatorLUT(calc_status_t (*lookup_array[])(calc_t*, char*, 
																	double*));

static void SetOperandLUT(calc_status_t (*lookup_array[])(calc_t*, char*));

static void SetFunctionLUT(calc_status_t (*lookup_array[])
												(double*, double*));

static calc_status_t Add(double* addee, double* adder);

static calc_status_t Subtract(double* subtractee, double* subtracter);

static calc_status_t Multiply(double* multipliee, double* multiplier);

static calc_status_t Division(double* divisee, double* diviser);

static calc_status_t PushOperand(calc_t* calc, char* expression);

static calc_status_t PushOperatorDM(calc_t* calc, char* operatr, 
																double* result);

static calc_status_t PushOperatorAS(calc_t* calc, char* operatr, 
																double* result);

static calc_status_t PushOpenBracket(calc_t* calc, char* expression);

static calc_status_t PushClosedBracket(calc_t* calc, char* operatr, 
																double* result);
static calc_status_t Calculate(calc_t* calc, double* result);

/******FUNCTIONS******/
static void InitASCII()
{
    size_t index = 0;
    for (index = 0; index < ASCII_RANGE; ++index)
    {
        ASCII_TABLE[index] = index;
    }
}

static calc_status_t Calculate(calc_t* calc, double* result)
{
    char *operatr = NULL;
    double *actor = NULL;
	double *actee = NULL;
    calc_status_t status = SUCCESS;

	operatr = (char*)StackPeek(calc->operator_stack);
	StackPop(calc->operator_stack);
	actor = (double*)StackPeek(calc->operand_stack);

	StackPop(calc->operand_stack);
	if (StackIsEmpty(calc->operand_stack))
	{
		*result  = *actor;
		free(actor);
		return status;
	}

	actee = (double*)StackPeek(calc->operand_stack);

	status = FunctionLUT[*operatr](actee, actor);

	*result = *actee;
	free(operatr);
	free(actor);

    return status;
    
}

static calc_status_t PushOperand(calc_t* calc, char* expression)
{
    char* buffer = NULL;
    double *operand = malloc(sizeof(double));
	*operand = strtod(expression, &buffer);
	StackPush(calc->operand_stack, operand);
	strcpy(expression, buffer);
	calc->state = WAIT_OPERATOR;
	return SUCCESS;
}

static calc_status_t PushOperatorDM(calc_t* calc, char* operatr, double* result)
{
	char *optr = malloc(sizeof(char));
	*optr = ASCII_TABLE[*operatr];
    StackPush(calc->operator_stack, optr);
	calc->state = WAIT_OPERAND;
	return SUCCESS;
}

static calc_status_t PushOperatorAS(calc_t* calc, char* operatr, double* result)
{
	calc_status_t status = SUCCESS;
	char *optr = malloc(sizeof(char));
	while (!StackIsEmpty(calc->operator_stack) && 
			('*' == *(char*)StackPeek(calc->operator_stack) || 
			'/' == *(char*)StackPeek(calc->operator_stack)))
	{
		status = Calculate(calc, result);		
	}
	*optr = ASCII_TABLE[*operatr];
    StackPush(calc->operator_stack, optr);
	calc->state = WAIT_OPERAND;
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

static calc_status_t PushOpenBracket(calc_t* calc, char* expression)
{
	char* buffer = expression;
    char *operatr = malloc(sizeof(char));
	*operatr = '(';
	StackPush(calc->operator_stack, operatr);
	++buffer;
	strcpy(expression, buffer);
	calc->state = WAIT_OPERAND;
	return SUCCESS;
}

static calc_status_t PushClosedBracket(calc_t* calc, char* operatr, 
																double* result)
{
	char* to_free = NULL;
	calc_status_t status = SUCCESS;

	ASSERT_NOT_NULL(operatr);

	while ('(' != *(char*)StackPeek(calc->operator_stack))
	{
		status = Calculate(calc, result);
	}

	to_free = (char*)StackPeek(calc->operator_stack);
	StackPop(calc->operator_stack);

	free(to_free);

	calc->state = WAIT_OPERATOR;
	return status;

}

static void SetOperatorLUT(calc_status_t (*lookup_array[])(calc_t*, 
											                   char*, double*))
{
	lookup_array[')'] = PushClosedBracket;
	lookup_array['+'] = PushOperatorAS;
	lookup_array['-'] = PushOperatorAS;
	lookup_array['*'] = PushOperatorDM;
	lookup_array['/'] = PushOperatorDM;
}

static void SetOperandLUT(calc_status_t(*lookup_array[])(calc_t*, char*))
{
	lookup_array['('] = PushOpenBracket;
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

static calc_status_t SyntaxErrorOperand(calc_t* calc, char* expression)
{
	ASSERT_NOT_NULL(calc);
	ASSERT_NOT_NULL(expression);
	return SYNTAX_ERROR;
}

static calc_status_t SyntaxErrorOperator(calc_t* calc, char* expression, 
																double* result)
{
	ASSERT_NOT_NULL(calc);
	ASSERT_NOT_NULL(expression);
	ASSERT_NOT_NULL(result);
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
	calc_t* calculator = NULL;
	calc_status_t status = SUCCESS;
	size_t length = 0;
	char operatr = 0;
	char equation[1000] = {0};
	char *eqptr = equation;
	
	ASSERT_NOT_NULL(expression);

	length = strlen(expression);
	strcpy(eqptr, expression);
    
    InitASCII();
 	calculator = malloc(sizeof(struct calculator));
	if (NULL == calculator)
	{
		return SYSTEM_ERROR;
	}
   
	calculator->operator_stack = StackCreate(length);
	calculator->operand_stack = StackCreate(length);
	calculator->state = WAIT_OPERAND;

	SetOperatorLUT(OperatorLUT);
	SetOperandLUT(OperandLUT);
	SetFunctionLUT(FunctionLUT);
	
	while ((SUCCESS == status) && ('\0' != *eqptr))
	{
		switch (calculator->state)
		{
			case (WAIT_OPERAND):
				status = OperandLUT[*eqptr](calculator, eqptr);
				break;
			case (WAIT_OPERATOR):
				operatr = *eqptr;
				status = OperatorLUT[operatr](calculator, &operatr, result);
				++eqptr;
				break;
		}

		if(' ' == *eqptr)
		{
			++eqptr;
		}

		if('\0' == *eqptr)
		{
			while (!StackIsEmpty(calculator->operator_stack) && 
									!StackIsEmpty(calculator->operand_stack))
			{
				status = Calculate(calculator, result);
			}
			while (!StackIsEmpty(calculator->operand_stack))
			{
				free(StackPeek(calculator->operand_stack));
				StackPop(calculator->operand_stack);
			}
			while (!StackIsEmpty(calculator->operator_stack))
			{
				free(StackPeek(calculator->operator_stack));
				StackPop(calculator->operator_stack);

			}
		}
	}
	StackDestroy(calculator->operand_stack);
	StackDestroy(calculator->operator_stack);
	free(calculator);
	return status;
}
