/******************************************************************************
*   Filename: htable.c
*
*   Description: Implementation a Hash Table as a array of double linked list
*
*   Date: 24.03.2020
*
*   Author: Korotkova Daria
*******************************************************************************/

#include <stdlib.h> /* malloc */
#include <stdio.h> /* FILE */
#include <assert.h> /* assert */
#include "hash_table.h"/*TODO separate from the above*/
#include "dlist.h"

htable_t *HTableCreate(hash_func_t hash_func, size_t table_size, hash_compare_t hash_compare)
{/*TODO line length*/
  size_t i = 0;
  htable_t *h_table = malloc(sizeof(htable_t));

  assert(NULL != hash_func);/*TODO assert before allocation*/
  assert(NULL != hash_compare);

  if (NULL == h_table)
  {
    return(NULL);
  }
  h_table->hash_func  = hash_func;
  h_table->hash_compare = hash_compare;
  h_table->table_size = table_size;

  h_table->table = (dlist_t**)calloc(sizeof(dlist_t*), table_size);
  if(NULL == h_table->table)
  {
    free(h_table);
    h_table = NULL;
    return(NULL);
  }

  for(i = 0; i < table_size; ++i)
  {
    h_table->table[i] = DListCreate();
    if(NULL == h_table->table[i])
    {
      return(NULL);
      HTableDestroy(h_table);
    }
  }
  return(h_table);
}


int HTableIsEmpty(const htable_t *htable)
{
  size_t i = 0;
  int result = 0;

  assert(NULL != htable);
  for (i = 0; i<htable->table_size; ++i)
  {
    if (NULL != htable->table[i])
    {
      result = DListIsEmpty(htable->table[i]);
	/*TODO if my first list is empty but my second isn't?*/
    }
  }
  return (result);
}

void HTableDestroy(htable_t *htable)
{
  size_t i = 0;

  assert (NULL != htable);
  for (i = 0; i<htable->table_size; ++i)
  {
    if (NULL != htable->table[i])
    {
      DListDestroy(htable->table[i]);
    }
  }
  free (htable->table);
  htable->table = NULL;

  free (htable);
  htable = NULL;
}

size_t HTableSize(const htable_t *htable)
{
  size_t i = 0;
  size_t counter = 0;
  size_t size = 0;

  assert (NULL != htable);
  for (i = 0; i<htable->table_size; ++i)
  {
    if (NULL != htable->table[i])
    {
      size = DListSize(htable->table[i]);
      counter += size;
/*TODO can be changed to one line*/
    }
  }
  return(counter);
}

int HTableInsert(htable_t *htable, void *entry)
{
  size_t to_insert = htable->hash_func(entry);
  iter_t result = DListPushBack(htable->table[to_insert], entry);

  assert (NULL != htable);/*TODO I have already used htable, need to assert before*/
  if(NULL != result)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void *HTableFind(const htable_t *htable, void *to_find)
{
  size_t index = htable->hash_func(to_find);
  iter_t from = DListBegin(htable->table[index]);
  iter_t to = DListEnd(htable->table[index]);
  iter_t find = NULL;

  assert (NULL != htable);/*TODO I have already used htable, need to assert before*/
  find = DListFind(from, to, htable->hash_compare, to_find);
  return(DListGetData(find));
}


int HTableForEach(htable_t *htable, hash_action_t action, void *param)
{
  size_t i = 0;
  int status = 0;
  dlist_t *current_list = {0};

  assert (NULL != htable);
  assert (NULL != action);
  for(i = 0; i < htable->table_size; ++i)
  {
    if (!DListIsEmpty(htable->table[i]))
    {
      current_list = htable->table[i];
      status = DListForEach(DListBegin(current_list), DListEnd(current_list), action, param);
    }
  }
  return(0 == status);
}
