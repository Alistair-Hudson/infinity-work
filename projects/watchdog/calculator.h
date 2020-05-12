#ifndef __OL85_CALCULATOR_H__
#define __OL85_CALCULATOR_H__

/*******************************************************************************
                                * OL85 API FOR CALCULATOR
                                * version 16.03.2020.0
******************************************************************************/
typedef enum status
{
	SUCCESS,
SYSTEM_ERROR,
MATH_ERROR,
SYNTAX_ERROR
} calc_status_t;

/*
* Input: pointer to the string expression, pointer to double answer
* Process: perform mathematical expression and store result in answer
* Returns: calc_status_t enum status SUCCESS(0) if successful / other statuses
*    			  if failed
*/
calc_status_t Calculator(const char *expression, double *_answer);

#endif /* __OL85_CALCULATOR_H__ */

