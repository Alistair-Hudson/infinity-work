#include <stdio.h>
#include <stdlib.h>

#include "knighttour.h"
int main()
{
	int path[64][2] = {0};

	KnightTour(path, 0, 0);
	return 0;
}

