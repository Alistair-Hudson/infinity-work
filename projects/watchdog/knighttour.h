#ifndef __OL85_KNIGHTTOUR_H__
#define __OL85_KNIGHTTOUR_H__
/*******************************************************************************
                                * OL85 API FOR KnightTour
                                * version 02.04.2020.0
******************************************************************************/

/*******************************************************************************
Input: The function receives a 2D of 64 x 2 int array where the path will be
recorded.
The function receives an starting position of row and column described by int
row and int col.
Process:  There will be 64 movements and each one is described by two coordinate
points, row in index 0 and column in index 1.
The coordinates will go from 0 to 7. Smallest point of the table will be 0x0
and the biggest 7x7.
******************************************************************************/
void KnightTour(int path[64][2], int row, int col);

#endif /* __OL85_KNIGHTTOUR_H__ */
