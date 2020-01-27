#include <stdio.h>
#include <stdlib.h>

int main()
{

	char str1[20];
	char *str3 = "whatever";
	char str4[] = "whatever";

	str3[1] = 'a';
	printf("%d", str3[1]);
	return 0;
}
