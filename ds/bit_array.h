/*
*	ws10 ArrayBit - header file.
*	by: ol85
* 	date: 04 Feb 2020
*/


#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

typedef size_t bitsarr_t;

/*Sets all bits to 1   */
bitsarr_t BitArrSetAll(bitsarr_t bit_arr);

/*Sets all bits to 0   */
bitsarr_t BitArrResetAll(bitsarr_t bit_arr);

/*Sets specified by position bit to 0
Positions are counted from 1.   */
bitsarr_t BitArrSetOn(bitsarr_t bit_arr, size_t pos);

/*Sets specified by position bit to 1 
Positions are counted from 1.    */
bitsarr_t BitArrSetOff(bitsarr_t bit_arr, size_t pos);

/*Sets specified by position bit to required value (1 or 0) 
Positions are counted from 1. */
bitsarr_t BitArrSetBit(bitsarr_t bit_arr, size_t pos, int value);

/*Converts bitarray to string of chars (0 or 1). Returns pointer to string,
and the user is obliged to free memory pointed at the end of execution the function   */
char * BitArrToString(bitsarr_t bit_arr);

/*Gets value (1 or 0) of a bit specified by position
Positions are counted from 1.  */
int BitArrGetVal (bitsarr_t bit_arr, size_t pos);

/*Reverses the bits and returns mirroed bitarray  */
bitsarr_t BitArrMirror(bitsarr_t bit_arr);

/*Flips all the bits and returns mirroed bitarray  */
bitsarr_t BitArrFlipArrayBits(bitsarr_t bit_arr);

/*Rotates a bitarray to the right by specified number of steps
and returns modified bitarray  */
bitsarr_t BitArrRotR (bitsarr_t bit_arr, size_t step);

/*Rotates bitarray to the left by specified number of steps
and returns modified bitarray  */
bitsarr_t BitArrRotL (bitsarr_t bit_arr, size_t step);

/*Returns number of bits set to 1  */
size_t BitArrCountBitsOn (bitsarr_t bit_arr);

/*Returns number of bits set to 0   */
size_t BitArrCountBitsOff (bitsarr_t bit_arr);



#endif /* __BIT_ARRAY_H__ */
