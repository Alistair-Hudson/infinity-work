/******************************************************************************
 *	Title:		Knight's Tour
 *	Authour:	Alistair Hudson
 *	Reviewer:	Daria
 *	Version:	02.04.2020.1
 ******************************************************************************/
#include <stdio.h>		/* printf */
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "knighttour.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define MAX_POSITIONS(x)			(x * x)
#define BOARD_DIMENSIONS		(8)
#define BIT_MASK				(1)
#define ILLEGAL_MOVE			(-1)
#define MAX_MOVES				(8)
#define COORDINATES				(2)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef enum status 
{
	SUCCESS = 0, 
	FAIL
};
 
static int KTSolve(size_t visitation_map, 
					int location, 
					int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES], 
					size_t step);

static void KTPrint(int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES]);

static int KTHasBeenVisited(size_t visitaion_map, int location);

static int KTNextMove(int location, size_t move);

/******FUNCTIONS******/
void KnightTour(int path[64][2], int start_row, int start_col)
{
	/*ensure path meets dimension requirements*/

	/*convert corrdinates into location on board*/
	
	/*begin solving*/
	/*if successfull*/	
		/*print result*/
}

static int KTSolve(size_t visitation_map, 
					int location, 
					int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES], 
					size_t step)
{
	/*if visited (bit = 1)
		return fail*/

	/*if steps = 0
		return success*/

	/*Set location in visitation_map to visited*/

	/*for moves 0 until 8
		if NextMove not ILLEGAL_MOVE
			if success == KTSolve(visitation_map, NextMove, path + 1, step - 1)
				record step
				return success
	*/

	/*Reset location to not visited*/

	/*return fail*/
}

static void KTPrint(int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES])
{
	/*print all indecies*/
}

static int KTHasBeenVisited(size_t visitation_map, int location)
{
	/*return true if visited false if not*/
}

static int KTNextMove(int location, size_t move)
{
	/*internal LUT for moves 8*2*/

	/*convert location into x, y coordinates*/

	/*if x outside bounds
		return ILLEGAL_MOVE*/

	/*if y outside bounds
		return ILLEGAL_MOVE*/
	
	/*return location + LUT[x][move] + 8*LUT[y][move]*/
}





