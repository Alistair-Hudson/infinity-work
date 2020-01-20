#include <stdio.h>
#include <stdlib.h>
#include "ws4.h"

int APressed()
{
	printf("A pressed\n");
	return 1;
}

int TPressed()
{
	printf("T pressed\n");
	return 1;
}

int EscPressed()
{
	printf("Treminating\n");
	return 0;
}

int OtherPressed()
{
	return 1;
}
void IfElseButton()
{
	int i = 1;
	char key;
	printf("If/Else begins\n\n");
	while(i)
	{
		
		printf("Press a key:\n");
		key = getchar();
		if((key == 'A') || (key == 'a'))
		{
			i = APressed();
		}else if((key == 'T') || (key == 't'))
		{
			i = TPressed();
		}else if(key == 27) /*The value of 27 is used as Esc cannot be represented*/
		{
			i = EscPressed();
		}else
		{
			i = OtherPressed();
		}
	}
}

void SwitchButton()
{

	char key;
	int i = 1;
	printf("Switch begins\n\n");
	while(i)
	{

		printf("Press a key:\n");
		key = getchar();
		switch(key)
		{
			case ('A'):
				i = APressed();
				break;
			case ('T'):
				i = TPressed();
				break;
			case ('a'):
				i = APressed();
				break;
			case ('t'):
				i = TPressed();
				break;
			case 27:
				i = EscPressed();
				break;
			default:
				i = OtherPressed();
		}
	}
}

void LUTButton()
{
	char key;
	unsigned int pass;
	int i = 0;
	int (*KeyLookup[256])();
	while(i <= 255) 
	{
		KeyLookup[i] = OtherPressed;
		++i;
	}
	KeyLookup['a'] = APressed;
	KeyLookup['A'] = APressed;
	KeyLookup['t'] = TPressed;
	KeyLookup['T'] = TPressed;
	KeyLookup[27] = EscPressed;
	printf("LUT begins\n\n");
	i = 1;
	while(i)
	{	
		printf("Press a key:\n");
		key = getchar();
		pass = (unsigned int)key;
		i = KeyLookup[pass]();
	}
}

