#include "bit_array.c"

void SetAllTest()
{
	bitsarr_t test_arr = 0x0;
	if (~0x0ul == BitArrSetAll(test_arr))
	{
		printf("SetAll pased\n");
	}
	else
	{
		printf("SetAll failed\n");
	}
}

void ResetAllTest()
{
	bitsarr_t test_arr = ~0x0;
	if (0x0 == BitArrResetAll(test_arr))
	{
		printf("ResetAll pased\n");
	}
	else
	{
		printf("ResetAll failed\n");
	}
}

void SetOnTest()
{
	bitsarr_t test_arr = 0x0;
	size_t set = 1;
	int count = 0;
	int pos = 0;
	while (set)
	{
		if ((test_arr ^ set) == BitArrSetOn(test_arr, pos))
		{
			++count;
		}
		else
		{
			printf("SetOn failed\n");
		}
		set <<= 1;
		++pos;
	}
	if(64 == count)
	{
		printf("SetOn Passed\n");
	}
	else
	{
		printf("SetOn failed\n");
	}
}

void SetOffTest()
{
	bitsarr_t test_arr = ~0x0;
	size_t set = 1;
	int count = 0;
	int pos = 0;
	while (set)
	{
		if ((test_arr ^ set) == BitArrSetOff(test_arr, pos))
		{
			++count;
		}
		else
		{
			printf("SetOff failed\n");
		}
		set <<= 1;
		++pos;
	}
	if(64 == count)
	{
		printf("SetOff Passed\n");
	}
	else
	{
		printf("SetOff failed\n");
	}
}

void SetBitTest()
{
	bitsarr_t test_arr = 0x0;
	size_t set = 1;
	int count = 0;
	int pos = 0;
	while (set)
	{
		if ((test_arr ^ set) == BitArrSetBit(test_arr, pos, 1))
		{
			++count;
		}
		else
		{
			printf("SetBit failed\n");
		}
		set <<= 1;
		++pos;
	}
	if(64 == count)
	{
		printf("SetBit Passed\n");
	}
	else
	{
		printf("SetBit failed\n");
	}
}

void FlipTest()
{
	bitsarr_t test_arr = 0xFEDCBA9876543210;
	size_t expected = 0x123456789ABCDEF;
	if (expected == BitArrFlipAllBits(test_arr))
	{
		printf("Flip passed\n");
	}
	else
	{
		printf("Flip failed\n");
	}
}

void GetValTest()
{
	bitsarr_t test_arr = 0xFEDCBA9876543210;
	size_t set = 1;
	int count = 0;
	int pos = 0;
	while (set)
	{
		if (((test_arr & set)>>pos) == BitArrGetVal(test_arr, pos))
		{
			++count;
		}
		else
		{
			printf("GetVal failed\n");
		}
		set <<= 1;
		++pos;
	}
	if(64 == count)
	{
		printf("GetVal Passed\n");
	}
	else
	{
		printf("GetVal failed\n");
	}
}

void RotRTest()
{
	bitsarr_t test_arr = 0xFEDCBA9876543210;
	size_t expected = 0x6543210FEDCBA987;
	if (expected == BitArrRotR(test_arr, 28))
	{
		printf("RotR passed\n");
	}
	else
	{
		printf("RotR failed\n");
	}
}

void RotLTest()
{
	bitsarr_t test_arr = 0xFEDCBA9876543210;
	size_t expected = 0x876543210FEDCBA9;
	if (expected == BitArrRotL(test_arr, 28))
	{
		printf("RotL passed\n");
	}
	else
	{
		printf("RotL failed\n");
	}
}

void CountOnTest()
{
	bitsarr_t test_arr = 0x8421842184218421;
	if (16 == BitArrCountBitsOn(test_arr))
	{
		printf("CountOn passed\n");
	}
	else
	{
		printf("CountOn failed\n");
	}
}

void CountOffTest()
{
	bitsarr_t test_arr = 0x7777777777777777;
	if ( 16 == BitArrCountBitsOff(test_arr))
	{
		printf("CountOff passed\n");
	}
	else
	{
		printf("CountOff failed\n");
	}
}

void MirrorTest()
{
	bitsarr_t test_arr = 	0xFF08040300000000;
	size_t expected = 		0xC02010FF;
	if (expected == BitArrMirror(test_arr))
	{
		printf("Mirror passed\n");
	}
	else
	{
		printf("Mirror failed\n");
	}
}

void ToStringTest()
{
	bitsarr_t test_arr = 0xFEDCBA9876543210;
	char exp_str[] = 
			"1111111011011100101110101001100001110110010101000011001000010000";
	char *test_str = BitArrToString(test_arr);
	if (!strcmp(exp_str,test_str ))
	{
		printf("ToString passed\n");
	}
	else
	{
		printf("ToString failed\n");
	}
	free(test_str);
	test_str = NULL;
}

int main()
{
	SetAllTest();
	ResetAllTest();
	SetOnTest();
	SetOffTest();
	SetBitTest();
	FlipTest();
	GetValTest();
	RotRTest();
	RotLTest();
	CountOnTest();
	CountOffTest();
	MirrorTest();
	ToStringTest();
	return 0;
}
