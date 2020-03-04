#include <stdlib.h>
#include <assert.h>		/* assert */

#include "uid.h"

/******MACRO******/

/*****TYPEDEFS, INTERNAL GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
ilrd_uid_t bad_uid = {0,0,0};
static size_t UIDCounter();

/*****FUNCTIONS******/

ilrd_uid_t UIDCreate()
{
	ilrd_uid_t new_uid = {0,0,0};
	
	new_uid.timestamp = time(NULL);
	
	if(0 >= new_uid.timestamp)
	{
		new_uid.timestamp = 0;
		return new_uid;
	}
	new_uid.pid = getpid();
	new_uid.counter = UIDCounter();

	return new_uid;
}

int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	int same = 1;

	if(uid1.timestamp != uid2.timestamp)
	{
		same *= 0;
	}
	if(uid1.pid != uid2.pid)
	{
		same *= 0;
	}
	if(uid1.counter != uid2.counter)
	{
		same *= 0;
	}
	
	return same;
}

static size_t UIDCounter()
{
	static size_t count = 0;
	return ++count;
}
