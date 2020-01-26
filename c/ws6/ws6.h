#ifndef _WS_6__FUNCTIONS_INCLUDED
#define _WS_6__FUNCTIONS_INCLUDED

/*Takes to ints x and y														*/ 
/*Performs a bit shift of x by y positions									*/
/*Returns the long x*(2^y)													*/
long Power2(unsigned int x, unsigned int y);
/*Two methods of counting the number of bits set to 1 in unsigned int x		*/
/*Returns the number of size_t active bits									*/
size_t BitCountLoop(unsigned int x);
size_t BitCount(unsigned int x);
/*Takes the unsigned int n and finds out if it is a power of 2.				*/
/*Returns 1 if true 0 if false												*/
int IsPow2Loop(unsigned int n);
int IsPow2(unsigned int n);
/*Finds if bits 2 and 6 are set to 1 in unsigned char x						*/
/*Returns 0 if true !0 if flase												*/
int Is2and6(unsigned char x);
/*Finds if bits 2 or 6 are set to 1	in unsigned char x						*/
/*Returns !0 if true 0 if flase												*/
int Is2or6(unsigned char x);
/*Takes a int x 															*/
/*Using bitwise operations													*/
/*Returns the highest multiple of 16 of that number	as unsinged int			*/
unsigned int IsDivisable16(unsigned int x);
/*Receives an array of ints and size_t of its size							*/ 
/*Prints which the value of the elements that have exactly 3 bits set to 1	*/
void Print3Bits(unsigned int *array, size_t size);
/*Recieves an int x															*/
/*Swaps the bits 3 and 5													*/
/*Prints the new number														*/
void BitSwap3and5(unsigned char x);
/*Adds 1 to an int x using bitwise operations								*/
/*Returns the new int value													*/
int IntAdd1(int x);
/*Two mewthods of taking an unsigned char and reversing the bits			*/
/*Returns the new char values												*/
unsigned char byte_mirrorLoop(unsigned char x);
unsigned char byte_mirror(unsigned char x);
/*Swaps the addressed values x and y using only bitwise operations			*/
void Swap(int *x, int *y);
/*Takes a Float value and represents it in binary form						*/
/* Note that the value printed has the signed bit at the end				*/
void PrintBitsOfFloat(float x);

#endif
