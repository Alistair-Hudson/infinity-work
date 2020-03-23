/******************************************************************************
 *	Title:		Calculator
 *	Authour:	Alistair Hudson
 *	Reviewer:	Shmuel
 *	Version:	19.03.2020.1
 ******************************************************************************/
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
	int positive;
}calc_t;

static char ASCII_TABLE[ASCII_RANGE] = {0};
static void InitASCII();

static calc_status_t SyntaxErrorOperand(calc_t* calc, char* expression);
static calc_status_t SyntaxErrorOperator(calc_t* calc, char* expression, 
																double* result);
static calc_status_t SystemError(double* actor, double* actee);

static calc_status_t(*OperandLUT[ASCII_RANGE])(calc_t* calc, char* expression)
																	= {NULL};
static calc_status_t(*OperatorLUT[ASCII_RANGE])(calc_t* calc, char* operatr, 
													double* result) = {NULL};
                                    
static calc_status_t(*FunctionLUT[ASCII_RANGE])(double* actee, double* actor) 
																	= {NULL};

static void SetOperatorLUT(calc_status_t (*lookup_array[])(calc_t*, char*, 
																	double*));

static void SetOperandLUT(calc_status_t (*lookup_array[])(calc_t*, char*));

static void SetFunctionLUT(calc_status_t (*lookup_array[])
												(double*, double*));

static calc_status_t Add(double* addee, double* adder);

static calc_status_t Subtract(double* subtractee, double* subtracter);

static calc_status_t Multiply(double* multipliee, double* multiplier);

static calc_status_t Division(double* divisee, double* diviser);

static calc_status_t Exponent(double* base, double* index);

static calc_status_t PushOperand(calc_t* calc, char* expression);

static calc_status_t PushOperatorDM(calc_t* calc, char* operatr, 
																double* result);

static calc_status_t PushOperatorAS(calc_t* calc, char* operatr, 
																double* result);

static calc_status_t PushOpenBracket(calc_t* calc, char* expression);

static calc_status_t PushClosedBracket(calc_t* calc, char* operatr, 
																double* result);

static calc_status_t PushExponent(calc_t* calc, char* operatr, double* result);

static calc_status_t PushNegative(calc_t* calc, char* expression);

static calc_status_t PushPositive(calc_t* calc, char* expression);

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

	status = FunctionLUT[*(int*)operatr](actee, actor);

	*result = *actee;
	free(operatr);
	free(actor);

    return status;
    
}

static calc_status_t PushOperand(calc_t* calc, char* expression)
{
    char* buffer = NULL;
    double *operand = malloc(sizeof(double));
	if (NULL == operand)
	{
		return SYSTEM_ERROR;
	}
	*operand = strtod(expression, &buffer);
	*operand *= calc->positive;
	StackPush(calc->operand_stack, operand);
	strcpy(expression, buffer);
	calc->state = WAIT_OPERATOR;
	calc->positive = 1;
	return SUCCESS;
}

static calc_status_t PushOperatorDM(calc_t* calc, char* operatr, double* result)
{
	calc_status_t status = SUCCESS;
	char *optr = malloc(sizeof(char));
	if (NULL == optr)
	{
		return SYSTEM_ERROR;
	}
	while (!StackIsEmpty(calc->operator_stack) && 
			('^' == *(char*)StackPeek(calc->operator_stack)))
	{
		status = Calculate(calc, result);		
	}
	if (!StackIsEmpty(calc->operator_stack) && '/' == *(char*)StackPeek(calc->operator_stack))
	{
		status = Calculate(calc, result);
	}

	*optr = ASCII_TABLE[*(int*)operatr];
    StackPush(calc->operator_stack, optr);
	calc->state = WAIT_OPERAND;
	return status;}

static calc_status_t PushOperatorAS(calc_t* calc, char* operatr, double* result)
{
	calc_status_t status = SUCCESS;
	char *optr = malloc(sizeof(char));
	if (NULL == optr)
	{
		return SYSTEM_ERROR;
	}
	while (!StackIsEmpty(calc->operator_stack) && 
			('*' == *(char*)StackPeek(calc->operator_stack) || 
			'/' == *(char*)StackPeek(calc->operator_stack) ||
			'^' == *(char*)StackPeek(calc->operator_stack)))
	{
		status = Calculate(calc, result);		
	}
	if (!StackIsEmpty(calc->operator_stack) && '-' == *(char*)StackPeek(calc->operator_stack))
	{
		status = Calculate(calc, result);
	}
	*optr = ASCII_TABLE[*(int*)operatr];
    StackPush(calc->operator_stack, optr);
	calc->state = WAIT_OPERAND;
	return status;
}

static calc_status_t PushExponent(calc_t* calc, char* operatr, double* result)
{
	char *optr = malloc(sizeof(char));
	if (NULL == optr)
	{
		return SYSTEM_ERROR;
	}
	ASSERT_NOT_NULL(result);
	*optr = ASCII_TABLE[*(int*)operatr];
    StackPush(calc->operator_stack, optr);
	calc->state = WAIT_OPERAND;
	return SUCCESS;	
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

static calc_status_t Exponent(double* base, double* index)
{
	double result = 1;
	int i = 1;

	if (0 >= *index)
	{
		*index *= -1;
		*base = 1 / *base;
	}

	for (i = 1; i <= *index; ++i)
	{
		result *= *base;
	}
	
	*base = result;
	return SUCCESS;
}
static calc_status_t PushOpenBracket(calc_t* calc, char* expression)
{
	char* buffer = expression;
    char *operatr = malloc(sizeof(char));
	if (NULL == operatr)
	{
		return SYSTEM_ERROR;
	}
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

static calc_status_t PushNegative(calc_t* calc, char* expression)
{
	char* buffer = expression;
	calc->positive *= -1;
	++buffer;
	strcpy(expression, buffer);
	calc->state = WAIT_OPERAND;
	return SUCCESS;	
}

static calc_status_t PushPositive(calc_t* calc, char* expression)
{
	ASSERT_NOT_NULL(expression);
	calc->state = WAIT_OPERAND;
	return SUCCESS;
}

static void SetOperatorLUT(calc_status_t (*lookup_array[])(calc_t*, 
											                   char*, double*))
{
	int index = 0;
	for (index = 0; index < ASCII_RANGE; ++index)
	{
		lookup_array[index] = SyntaxErrorOperator;
	}
	lookup_array[')'] = PushClosedBracket;
	lookup_array['+'] = PushOperatorAS;
	lookup_array['-'] = PushOperatorAS;
	lookup_array['*'] = PushOperatorDM;
	lookup_array['/'] = PushOperatorDM;
	lookup_array['^'] = PushExponent;
}

static void SetOperandLUT(calc_status_t(*lookup_array[])(calc_t*, char*))
{
	int index = 0;
	for (index = 0; index < ASCII_RANGE; ++index)
	{
		lookup_array[index] = SyntaxErrorOperand;
	}
	lookup_array['('] = PushOpenBracket;
	lookup_array['+'] = PushPositive;
	lookup_array['-'] = PushNegative;
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
	int index = 0;
	for (index = 0; index < ASCII_RANGE; ++index)
	{
		lookup_array[index] = SystemError;
	}
	lookup_array['+'] = Add;
	lookup_array['-'] = Subtract;
	lookup_array['*'] = Multiply;
	lookup_array['/'] = Division;
	lookup_array['^'] = Exponent;

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
	calculator->positive = 1;

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
				status = OperatorLUT[(int)operatr](calculator, &operatr, result);
				++eqptr;
				break;
		}

		if(' ' == *eqptr)
		{
			++eqptr;
		}

		if('\0' == *eqptr)
		{
			if ('+' == StackPeek(calculator->operand_stack) || 
				'-' == StackPeek(calculator->operand_stack))
			{
				return SYNTAX_ERROR;
			}
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
