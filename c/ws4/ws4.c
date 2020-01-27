#include <stdio.h> /*printf, getchar*/
#include <stdlib.h>
#include "ws4.h"

/*Defined constant variables*/
#define ESC_key (27)
#define ASCII_range (256)

static int PrintKeyPressed(char key)
{
	printf("%c pressed\n", key);
	return 1;
}

static int EscPressed(char key)
{
	key = 0;
	printf("Treminating\n");
	return key;
}

static int OtherPressed(char key)
{
	key = 1;
	return key;
}

static void CreateASCIILookup(int (*lookup_array[])(char), size_t size_of_lut)
{
	unsigned int lut_index = 0;
	while(lut_index <= size_of_lut) 
	{
		lookup_array[lut_index] = OtherPressed;
		++lut_index;
	}
	lookup_array['a'] = PrintKeyPressed;
	lookup_array['A'] = PrintKeyPressed;
	lookup_array['t'] = PrintKeyPressed;
	lookup_array['T'] = PrintKeyPressed;
	lookup_array[ESC_key] = EscPressed;
	
}

void IfElseButton()
{
	char key_pressed;
	int is_active = 1;
	printf("If/Else begins\n\n");
	while(is_active)
	{
		
		printf("Press a key:\n");
		key_pressed = getchar();
		key_pressed = tolower(key_pressed);
		if('a' == key_pressed)
		{
			is_active = PrintKeyPressed('A');
		}else if('t' == key_pressed)
		{
			is_active = PrintKeyPressed('T');
		}else if(ESC_key == key_pressed)
		{
			is_active = EscPressed(0);
		}else
		{
			is_active = OtherPressed(1);
		}
	}
}

void SwitchButton()
{
	char key_pressed;
	int is_active = 1;
	printf("Switch begins\n\n");
	while(is_active)
	{

		printf("Press a key:\n");
		key_pressed = getchar();
		key_pressed = tolower(key_pressed);
		switch(key_pressed)
		{
			case ('a'):
				is_active = PrintKeyPressed('A');
				break;
			case ('t'):
				is_active = PrintKeyPressed('T');
				break;
			case ESC_key:
				is_active = EscPressed(0);
				break;
			default:
				is_active = OtherPressed(1);
				break;
		}
	}
}

void LUTButton()
{
	char key_pressed;
	unsigned int pass;
	int is_active = 1;
	int (*KeyLookup[ASCII_range])(char key);
	CreateASCIILookup(KeyLookup, ASCII_range);
	printf("LUT begins\n\n");
	while(is_active)
	{	
		printf("Press a key:\n");
		key_pressed = getchar();
		pass = (unsigned int)key_pressed;
		is_active = KeyLookup[pass](key_pressed);
	}
}

