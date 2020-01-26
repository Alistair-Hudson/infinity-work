#include <stdio.h>
#include <stdlib.h>
#include "ws4.c"



int main ()
{
	system("stty -icanon -echo");
	IfElseButton();
	SwitchButton();
	LUTButton();
	system("stty icanon echo");
	return 0;
}
