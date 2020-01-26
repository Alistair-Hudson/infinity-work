#include "ws6.c"

void Power2Test()
{
	int pass = 0;
	if (32 == Power2(1, 5))
	{
		++pass;
	}
	if (0xFF0 == Power2(0xFF, 4))
	{
		++pass;
	}
	if (0xABC12300 == Power2(0xABC123, 8))
	{
		++pass;
	}
	if(3 == pass)
	{
		printf("Power2 test passed\n");
	}
	else
	{
		printf("Power2 test failed\n");
	}
}

void IsPower2Test()
{
	int pass = 0;
	if (IsPow2Loop(32))
	{
		++pass;
	}
	if (IsPow2Loop(256))
	{
		++pass;
	}
	if (!IsPow2Loop(0xF0))
	{
		++pass;
	}
	if (!IsPow2Loop(0x33))
	{
		++pass;
	}
	if (IsPow2(32))
	{
		++pass;
	}
	if (IsPow2(256))
	{
		++pass;
	}
	if (!IsPow2(0xF0))
	{
		++pass;
	}
	if (!IsPow2(0x33))
	{
		++pass;
	}
	if(8 == pass)
	{
		printf("Power2 test passed\n");
	}
	else
	{
		printf("IsPower2 test failed\n");
	}
}

void BitCountTest()
{
	int pass = 0;
	if (1 == BitCountLoop(32))
	{
		++pass;
	}
	if (1 == BitCountLoop(256))
	{
		++pass;
	}
	if (4 == BitCountLoop(0xF0))
	{
		++pass;
	}
	if (4 == BitCountLoop(0x33))
	{
		++pass;
	}
	if (1 == BitCount(32))
	{
		++pass;
	}
	if (1 == BitCount(256))
	{
		++pass;
	}
	if (4 == BitCount(0xF0))
	{
		++pass;
	}
	if (4 == BitCount(0x33))
	{
		++pass;
	}
	if(8 == pass)
	{
		printf("Bit Count test passed\n");
	}
	else
	{
		printf("Bit Count test failed\n");
	}

}

void Is26Test()
{
	int pass = 0;
	if (Is2and6(32))
	{
		++pass;
	}
	if (!Is2and6(34))
	{
		++pass;
	}
	if (!Is2and6(0xFF))
	{
		++pass;
	}
	if (Is2and6(0x2))
	{
		++pass;
	}
	if (Is2and6(0x4))
	{
		++pass;
	}
	if (Is2or6(32))
	{
		++pass;
	}
	if (Is2or6(34))
	{
		++pass;
	}
	if (Is2or6(0xFF))
	{
		++pass;
	}
	if (Is2or6(0x2))
	{
		++pass;
	}	
	if (!Is2or6(0x4))
	{
		++pass;
	}
	if(10 == pass)
	{
		printf("Is 2/6 test passed\n");
	}
	else
	{
		printf("is 2/6 test failed\n");
	}			
	
}

void Divisable16Test()
{
	int pass = 0;
	if (32 == IsDivisable16(32))
	{
		++pass;
	}
	if (48 == IsDivisable16(48))
	{
		++pass;
	}
	if (0 == IsDivisable16(15))
	{
		++pass;
	}
	if (0x3FFF0 == IsDivisable16(0x3FFF8))
	{
		++pass;
	}
	if(4 == pass)
	{
		printf("Divisable 16 test passed\n");
	}
	else
	{
		printf("Divisable 16 test failed\n");
	}			
}

void PrintBitsTest()
{
	unsigned int array[] = {7, 8, 13, 20, 28, 30, 14};
	Print3Bits(array, 7);
}

void BitSwapTest()
{
	BitSwap3and5(0xF0);
}

void IntAddTest()
{
	int x = IntAdd1(1);
	if(2 == x)
	{
		x = IntAdd1(x);
	}
	if(3 == x)
	{
		x = IntAdd1(x);
	}
	if(4 == x)
	{
		x = IntAdd1(x);
	}
	if(5 == x)
	{
		x = IntAdd1(x);
	}
	if(6 == x)
	{
		x = IntAdd1(x);
	}
	if(7 == x)
	{
		printf("Int Add test passed\n");
	}
	else
	{
		printf("Int Add test failed\n");
	}			
}

void ByteMirrorTest()
{
	int pass = 0;
	if (0xF0 == byte_mirrorLoop(0x0F))
	{
		++pass;
	}
	if (0xCF == byte_mirrorLoop(0xF3))
	{
		++pass;
	}
	if (0x82 == byte_mirrorLoop(0x41))
	{
		++pass;
	}
	if (0x13 == byte_mirrorLoop(0xC8))
	{
		++pass;
	}
	if (0xFF == byte_mirrorLoop(0xFF))
	{
		++pass;
	}
	if (0xF0 == byte_mirror(0x0F))
	{
		++pass;
	}
	if (0xCF == byte_mirror(0xF3))
	{
		++pass;
	}
	if (0x82 == byte_mirror(0x41))
	{
		++pass;
	}
	if (0x13 == byte_mirror(0xC8))
	{
		++pass;
	}
	if (0xFF == byte_mirror(0xFF))
	{
		++pass;
	}
	if(10 == pass)
	{
		printf("BYte Mirror test passed\n");
	}
	else
	{
		printf("Byte Mirror test failed\n");
	}			
}

void SwapTest()
{
	int x = 5;
	int y = 9;
	int *ptrx = &x;
	int *ptry = &y;
	Swap(ptrx, ptry);
	printf("x = %d, y = %d\n", x , y); 
}

void FloatPrintTest()
{
	PrintBitsOfFloat(3);
	PrintBitsOfFloat(2);
	PrintBitsOfFloat(2.5);
	PrintBitsOfFloat(-3);
	
}
int main()
{

	Power2Test();
	IsPower2Test();
	BitCountTest();
	Is26Test();
	Divisable16Test();
	PrintBitsTest();
	BitSwapTest();	
	IntAddTest();
	ByteMirrorTest();
	SwapTest();
	FloatPrintTest();
	return 0;
}
