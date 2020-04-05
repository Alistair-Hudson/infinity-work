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
	int start_location = 0;
	size_t visitation_map = 0;
	/*ensure path meets dimension requirements*/

	/*convert corrdinates into location on board*/
	start_location = start_row + (start_col * BOARD_DIMENSIONS);
	/*begin solving*/
	if(SUCCESS == KTSolve(visitation_map, start_location, path, 
											MAX_POSITIONS(BOARD_DIMENSIONS)))
	{	
		/*print result*/
		KTPrint(path);
	}
	else
	{
		printf("No Solution found");
	}
}

static int KTSolve(size_t visitation_map, 
					int location, 
					int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES], 
					size_t step)
{
	size_t move = 0;

	/*if visited (bit = 1)
		return fail*/
	if (KTHasBeenVisited(visitation_map, location))
	{
		return FAIL;
	}
	/*if steps = 0
		return success*/
	if (0 == step)
	{
		path[step][0] = location % BOARD_DIMENSIONS;
		path[step][1] = location / BOARD_DIMENSIONS;
		return SUCCESS;
	}

	/*Set location in visitation_map to visited*/
	visitation_map |= BIT_MASK << location;
	/*for moves 0 until 8
		if NextMove > ILLEGAL_MOVE
			if success == KTSolve(visitation_map, NextMove, path + 1, step - 1)
				record step
				return success
	*/
	for (move = 0; move < MAX_MOVES; ++move)
	{
		if (KTNextMove(location, move) > ILLEGAL_MOVE)
		{
			if (SUCCESS == KTSolve(visitation_map, KTNextMove(location, move),
																path, step - 1))
			{
				path[step][0] = location % BOARD_DIMENSIONS;
				path[step][1] = location / BOARD_DIMENSIONS;				
				return SUCCESS;
			}
		}
	}
	/*Reset location to not visited*/
	visitation_map ^= BIT_MASK << location;
	/*return fail*/
	return FAIL;
}

static void KTPrint(int path[MAX_POSITIONS(BOARD_DIMENSIONS)][COORDINATES])
{
	size_t index = 0;
	for (index = 0; index < MAX_POSITIONS(BOARD_DIMENSIONS); ++index)
	{
		printf("%d, %d", path[index][0], path[index][1]);
	}
}

static int KTHasBeenVisited(size_t visitation_map, int location)
{
		return visitation_map & (BIT_MASK << location);	
}

static int KTNextMove(int location, size_t move)
{
	int x = 0;
	int y = 0;
	/*internal LUT for moves 8*2*/
	int move_LUT[2][MAX_MOVES] = {{1, 2,  2,  1, -1, -2, -2, -1}, 
						 		  {2, 1, -1, -2, -2, -1,  1,  2}};
	/*convert location into x, y coordinates*/
	x = location % BOARD_DIMENSIONS;
	y = location / BOARD_DIMENSIONS;
		/*if x outside bounds
			return ILLEGAL_MOVE*/
	if ((0 > (x + move_LUT[0][move])) || (7 < (x + move_LUT[0][move])))
	{
		return ILLEGAL_MOVE;
	}
		/*if y outside bounds
			return ILLEGAL_MOVE*/
	if ((0 > (y + move_LUT[1][move])) || (7 < (y + move_LUT[1][move])))
	{
		return ILLEGAL_MOVE;
	}
	
	/*return location + LUT[x][move] + 8*LUT[y][move]*/
	return location + move_LUT[0][move] + (BOARD_DIMENSIONS * move_LUT[1][move]);
}





