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

	/*Warnsdorff soln*/
/*-----------------------------------------------------------------------------
		for move 0 until 8
			find how many possible moves are avaliable at this next location
			sort moves from lowest next possible to highest
----------------------------------------------------------------------------*/
	/*for warnsdorff_move index 0 until 8
			if 8 == warnsdorff[index]
				return fail
			if success == KTSolve(visitation_map, warnsdorff_move[index], path + 1, step - 1)
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

static void WarnsdorffSoln(int location, int *warnsdorff_moves, size_t visitation_map)
{	/*8 Signals that there are no more possible moves as the maximum possible
		moves is 7*/
	/*for move 0 until 8
		if move ILLEGAL_MOVE
			moves_after[move] = 8
		if move visited
			moves_after[move] = 8
		for next_move 0 until 8
			if NextMove is not ILLEGAL_MOVE
				if NextMove not visited
					++moves_after[move]
	*/
	/*for move 0 until 8
		if move has smallest after
			*warnsdirff_moves = move
			++warnsdorff_moves
			move_after = 8
	*/		
}



