/******************************************************************************
 *	Title:		AVL Tree
 *	Authour:	Alistair Hudson
 *	Reviewer:	Yurri
 *	Version:	23.03.2020.1
 ******************************************************************************/
#include <stdlib.h>
#include <assert.h>		/* assert */

#include "hash_table.h"

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define WORD_SIZE				(sizeof(size_t))

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
/*typedef struct htable 
{
	dlist_t **dlist;
	hash_func_t hash_func;
	hash_compare_t comapre;
} htable_t;
*/

/******FUNCTIONS******/

htable_t *HTableCreate(hash_func_t hash_func, size_t table_size, 
														hash_compare_t compare)
{
	htable_t* new_htable = NULL;
	size_t i = 0;

	new_htable = malloc(sizeof(struct htable) + (table_size * WORD_SIZE));
	if (NULL == new_htable)
	{
		return NULL;
	}
	
	new_htable->hash_func = hash_func;
	new_htable->compare = compare;
	new_htable->table_size = table_size;
	new_htable->table = (dlist_t**)new_htable + 
											(sizeof(struct htable) / WORD_SIZE);
	for (i = 0; i < table_size; ++i)
	{
		new_htable->table[i] = DListCreate();
		if (NULL == new_htable->table[i])
		{
			for (i = i; i > 0; --i)
			{
				free(new_htable->table[i]);
				new_htable->table[i] = NULL;
			}
			free(new_htable->table[0]);
			new_htable->table[0] = NULL;
			free(new_htable);
			new_htable = NULL;
			return NULL;
		}
	}

	return new_htable;
}

void HTableDestroy(htable_t *htable)
{
	size_t i = 0;
	
	for (i = 0; i < htable->table_size; ++i)
	{
		DListDestroy(htable->table[i]);
	}
	free(htable);
	htable = NULL;
}

size_t HTableSize(const htable_t *htable)
{
	size_t size = 0;
	size_t i = 0;
	
	for (i = 0; i < htable->table_size; ++i)
	{
		size += DListSize(htable->table[i]);
	}	
	return size;
}

int HTableIsEmpty(const htable_t *htable)
{
	size_t i = 0;
 
	for (i = 0; i < htable->table_size; ++i)
	{
		if (!DListIsEmpty(htable->table[i]))
		{
			return 0;
		}
	}
	return 1;
}

void HTableInsert(htable_t *htable, void *entry)
{
	DListPushBack(htable->table[htable->hash_func(entry)], entry);
}

void HTableRemove(htable_t *htable, void *key)
{
	iter_t to_remove = DListFind(DListBegin(htable->table[htable->hash_func(key)]), 
								DListEnd(htable->table[htable->hash_func(key)]),
								htable->compare, 
								key);

	DListRemove(to_remove);
}

void *HTableFind(const htable_t *htable, void *to_find)
{
	iter_t found = DListFind(DListBegin(htable->table[htable->hash_func(to_find)]), 
							DListEnd(htable->table[htable->hash_func(to_find)]),
							htable->compare, 
							to_find);

	return DListGetData(found);

}

int HTableForEach(htable_t *htable, action_t action, void *param)
{
	size_t i = 0;

	for (i = 0; i < htable->table_size; ++i)
	{
		if (DListForEach(DListBegin(htable->table[i]), 
						DListEnd(htable->table[i]),
						action, 
						param))
		{
			return 1;
		}
	}
	return 0;
}

double HTableLoadFactor(const htable_t *htable)
{
	return 0;
}

double HTableSD(const htable_t *htable)
{
	return 0;
}




