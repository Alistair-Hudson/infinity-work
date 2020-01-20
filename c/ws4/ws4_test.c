#include <stdio.h>
#include <stdlib.h>
#include "ws4.c"



int main ()
{
	system("stty -icanon -echo");
	LUTButton();
	IfElseButton();
	SwitchButton();
	system("stty icanon echo");
	return 0;
}
