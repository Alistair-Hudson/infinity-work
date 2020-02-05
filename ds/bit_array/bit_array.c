/**************************************************************************	*/
/*							bit_array.c										*/
/*							Author: Alistair Hudson							*/
/*							Date: 04/02/2020								*/
/*	Copyright falls undert the standard GNU license and creative commons	*/
/*																			*/
/**************************************************************************	*/
#include <stdio.h>/*for standard ios ie printf*/
#include <stdlib.h>/*for standard library functions ie malloc*/
#include <string.h>/*string functions*/
#include <assert.h>/*for asserts*/
#include "bit_array.h"

/**********MACROS***********/
#define ARRAY_SIZE 				(64)
#define MAX_POSS_COMBINATIONS 	(256)
#define _0101MASK 				(0x55555555)
#define _0011MASK 				(0x33333333)
#define _0FMASK					(0x0f0f0f0f)
#define _BYTEMASK 				(0x3f)
#define _MASKR					(0xff)
#define _MASKL					(0xFF00000000000000)
#define _MASKMSB				(0x8000000000000000)

/*******TYPEDEFS AND STATIC FUNCTIONS*********/
static int BytesOnCreator(unsigned int byte_value)
{
	byte_value = byte_value - ((byte_value >> 1) & _0101MASK);
	byte_value = (byte_value & _0011MASK) + ((byte_value >> 2) & _0011MASK);
	byte_value = (byte_value + (byte_value >> 4)) & _0FMASK;
	byte_value = byte_value + (byte_value >> 8);
	byte_value = byte_value + (byte_value >> 16);
	return (byte_value & _BYTEMASK);
}

static int BytesMirrorCreator(unsigned int byte_value)
{
	unsigned char output = 0;
	unsigned char swapl = byte_value & 0xF0;
	unsigned char swapr = byte_value & 0x0F;
	unsigned char buffer = 0;
	
	swapr <<= 4;
	swapl >>= 4;
	output = swapr | swapl;
	buffer = output;
	
	output = 0;
	swapl = buffer & 0xCC;
	swapr = buffer & 0x33;
	swapr <<= 2;
	swapl >>= 2;
	output = swapr | swapl;
	buffer = output;
	
	output = 0;
	swapl = buffer & 0xAA;
	swapr = buffer & 0x55;
	swapr <<= 1;
	swapl >>= 1;
	output = swapr | swapl;
	return output;
} 
static void CreateBytesOnLookup(int *lookup_array, size_t size_of_lut)
{
	unsigned int lut_index = 0;
	while(lut_index < size_of_lut) 
	{
		lookup_array[lut_index] = BytesOnCreator(lut_index);
		++lut_index;
	}
}

static void CreateBytesMirrorLookup(int *lookup_array, size_t size_of_lut)
{
	unsigned int lut_index = 0;
	while(lut_index < size_of_lut) 
	{
		lookup_array[lut_index] = BytesMirrorCreator(lut_index);
		++lut_index;
	}
}

/*******USER FUNCTIONS******/
bitsarr_t BitArrSetAll(bitsarr_t bit_arr)
{
	return ~0x0;
}

bitsarr_t BitArrResetAll(bitsarr_t bit_arr)
{
	return 0x0;
}

bitsarr_t BitArrSetOn(bitsarr_t bit_arr, size_t pos)
{
	size_t set = 1;
	assert(ARRAY_SIZE > pos);
	assert(0 <= pos);
	set <<= pos;
	return (bit_arr |= set);
	
}

bitsarr_t BitArrSetOff(bitsarr_t bit_arr, size_t pos)
{
	size_t set = 1;
	assert(0 != bit_arr);
	assert(ARRAY_SIZE > pos);
	assert(ARRAY_SIZE > pos);
	assert(0 <= pos);
	set <<= pos;
	set = ~set;
	return (bit_arr &= set);
	
}

bitsarr_t BitArrSetBit(bitsarr_t bit_arr, size_t pos, int set_to)
{
	assert(ARRAY_SIZE > pos);
	assert(0 <= pos);
	if(0 == set_to)
	{
		bit_arr = BitArrSetOff(bit_arr, pos);
	}
	else
	{
		bit_arr = BitArrSetOn(bit_arr, pos);
	}
	return bit_arr;
	
}

bitsarr_t BitArrFlipArrayBits(bitsarr_t bit_arr)
{
	return ~bit_arr;
}

int BitArrGetVal(bitsarr_t bit_arr, size_t pos)
{
	assert(ARRAY_SIZE > pos);
	assert(0 <= pos);
	return ((bit_arr >> pos) & 1);
}

bitsarr_t BitArrRotR(bitsarr_t bit_arr, size_t steps)
{
	bitsarr_t temp = bit_arr;
	assert(0 <= steps);
	bit_arr >>= steps;
	temp <<= (ARRAY_SIZE - steps);
	return (bit_arr |= temp);
	
}

bitsarr_t BitArrRotL(bitsarr_t bit_arr, size_t steps)
{
	bitsarr_t temp = bit_arr;;
	assert(0 <= steps);
	bit_arr <<= steps;
	temp >>= (ARRAY_SIZE - steps);
	return (bit_arr |= temp);
	
}

bitsarr_t BitArrCountBitsOn(bitsarr_t bit_arr)
{
	size_t count = 0;
	unsigned int bytes_remain = 8;
	int byte = 0;
	int ByteLookup[MAX_POSS_COMBINATIONS];
	CreateBytesOnLookup(ByteLookup, MAX_POSS_COMBINATIONS);
	while(0 < bytes_remain)
	{
		byte = bit_arr & 0xFF;
		count += ByteLookup[byte];
		bit_arr >>= 8;
		--bytes_remain;
	}
	return count;
}

bitsarr_t BitArrCountBitsOff(bitsarr_t bit_arr)
{
	assert(0 != bit_arr);
	return (ARRAY_SIZE - BitArrCountBitsOn(bit_arr));
}

bitsarr_t BitArrMirror(bitsarr_t bit_arr)
{
	unsigned int left_byte = 7;
	unsigned int right_byte = 0;
	size_t byter = 0;
	size_t bytel = 0;
	size_t output = 0;
	int ByteLookup[MAX_POSS_COMBINATIONS];;
	CreateBytesMirrorLookup(ByteLookup, MAX_POSS_COMBINATIONS);
	while(right_byte < left_byte)
	{
		byter = (bit_arr >> (right_byte*8));
		bytel = (bit_arr << (right_byte*8));
		byter &= _MASKR;
		bytel &= _MASKL;
		bytel >>= 56;
		byter = ByteLookup[(int)byter];
		bytel = ByteLookup[(int)bytel];
		bytel <<= (right_byte*8);
		byter <<= (left_byte*8);
		output |= (bytel | byter);
		++right_byte;
		--left_byte;
	}
	return output;
}

char *BitArrToString(bitsarr_t bit_arr)
{
	char *output = (char*)malloc ((ARRAY_SIZE)+1);
	char *output_start = output;
	size_t str_index = _MASKMSB;
	assert(NULL != output);
	while(str_index)
	{
		if(bit_arr & str_index)
		{
			*output = '1';
		}
		else
		{
			*output = '0';
		}
		str_index >>= 1;
		++output;
	}
	*output = '\0';
	return output_start;
}
