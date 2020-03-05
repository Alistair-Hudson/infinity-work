#include <stdlib.h>
#include <stdio.h>

#include "uid.h"

int main()
{
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();

	if(UIDIsSame(uid1, uid1))
	{
		printf("IsSame passed\n");
	}
	else
	{
		printf("IsSame failed\n");
	}



	if(UIDIsSame(uid1, uid2))
	{
		printf("both are the same\n");
		printf("Create failed\n");
	}
	else
	{
		printf("both are not the same\n");
		printf("Create passed\n");
	}


	return 0;
}
