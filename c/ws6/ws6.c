#include <stdlib.h> /*Standard Library for operational functions*/
#include <stdio.h> /* standard IOs for program interaction*/

long Power2(unsigned int x, unsigned int y)
{
	long result = x;
	result = result << y;
	return result;
}

size_t BitCountLoop(unsigned int x)
{
	int i = 1;
	int count = 0;
	while (8 >= i)
	{
		count += x & 1;
		x >>= 1;
		++i;
	}
	return count;
}

int IsPow2Loop(unsigned int n)
{
	if(1 == BitCountLoop(n))
	{
		return 1;
	}
	return 0;
}

int Is2and6(unsigned char x)
{
	int result = x ^ 255;
	result &= 34; 
	return result;
}

int Is2or6(unsigned char x)
{
	int result = x & 34;
	return result;
}

unsigned int IsDivisable16(unsigned int x)
{
	int result = 0xF0 & x;
	return result;
}

void Print3Bits(unsigned int *array, size_t size)
{
	unsigned int index = 0;
	for(; index <= size; ++index)
	{
		if(3 == BitCountLoop(array[index]))
		{
			printf("%d\n", array[index]);
		}
	}
}

void BitSwap3and5(unsigned char x)
{
	int bit3 = x & 8;
	int bit5 = x & 32;
	bit3 <<= 2;
	bit5 >>= 2;
	x &= (128+64+16+4+2+1);
	x |= bit3;
	x |= bit5;

	printf("%d\n", x);
	
}

int IntAdd1(int x)
{
	int result = x;
	int i = 1;
	while(1)
	{
		if(!(x & i))
		{
			result |= i;
			return result;
		}
		result ^= i; 
		i <<= 1;
	} 
	return 0;
}

unsigned char byte_mirrorLoop(unsigned char x)
{
	unsigned char bitl = 128;
	unsigned char bitr = 1;
	int bitl_pos = 7;
	int bitr_pos = 0;
	int move;
	unsigned char swapl;
	unsigned char swapr;
	unsigned char result = 0;
	
	while(bitl >= bitr)
	{
		move = bitl_pos - bitr_pos;
		swapl = x & bitl;
		swapr = x & bitr;
		swapr <<= move;
		swapl >>= move;
		result |= swapl;
		result |= swapr;
			
		bitl >>=1;
		bitr <<= 1;
		--bitl_pos;
		++bitr_pos;
	}
	return result;
}

void Swap(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

unsigned char byte_mirror(unsigned char x)
{
	unsigned char result = 0;
	unsigned char swapl = x & 0xF0;
	unsigned char swapr = x & 0x0F;
	unsigned char buffer;
	
	swapr <<= 4;
	swapl >>= 4;
	result |= swapr;
	result |= swapl;
	buffer = result;
	
	result = 0;
	swapl = buffer & 0xCC;
	swapr = buffer & 0x33;
	swapr <<= 2;
	swapl >>= 2;
	result |= swapr;
	result |= swapl;
	buffer = result;
	
	result = 0;
	swapl = buffer & 0xAA;
	swapr = buffer & 0x55;
	swapr <<= 1;
	swapl >>= 1;
	result |= swapr;
	result |= swapl;
	return result;
}

void PrintBitsOfFloat(float x)
{
	int size = sizeof(float) * 8;
	int i = 1;
	unsigned int *bit_cast = &x;
	for(; size >= 0; --size)
	{
		if(*bit_cast & i)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
		i <<= 1;
	}
	printf("\n");
}

size_t BitCount(int x)
{
	x = x - ((x >> 1) & 0x55);
	x = (x & 0x33) + ((x >> 2) & 0x33);
	x = (x + (x >> 4)) & 0x0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x3F;
}

int IsPow2(unsigned int n)
{
	if(1 == BitCount(n))
	{
		return 1;
	}
	return 0;
}

int main()
{
	PrintBitsOfFloat(0.15625);
/*	printf("%d\n", BitCount(0xA0));*/
	return 0;
}
