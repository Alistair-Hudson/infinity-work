#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/
#include "vector.h"

/*****MACROS*****/
#define ELEMENT_SIZE 	(sizeof(void*))
#define PUSH_ADJST		((VectorSize(vector)+1)*2)
/*****STRUCTURE TO HANDLE THE STACK******/
struct vector
{
	void *base;
	void *max;
	void *top;
};

/******FUNCTION DEFINITIONS********/
vector_t *VectorCreate(size_t capacity)
{
	vector_t *_vector = malloc(sizeof(struct vector) * ELEMENT_SIZE);
	if(NULL == _vector)
	{
		return NULL;
	}
	_vector->base = malloc(capacity * ELEMENT_SIZE);
	if(NULL == _vector->base)
	{
		free(_vector);
		_vector = NULL;
		return NULL;
	}
	_vector->max = (size_t *)_vector->base + capacity;
	_vector->top = _vector->base;

	return _vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->base);
	free(vector->base);
	vector->base = NULL;
	free(vector);
	vector = NULL;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	if(vector->base == vector->top) {return 1;}
	return 0;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	return (((size_t)vector->max - (size_t)vector->base) / ELEMENT_SIZE);
}

int VectorPushBack(vector_t *vector, void *data)
{
	int reserve_check = 0;
	size_t next_top_loc = (size_t)vector->top + ELEMENT_SIZE;

	assert(NULL != vector);
	if ((size_t)vector->max < next_top_loc)
	{
		reserve_check = VectorReserve(vector, PUSH_ADJST);
		if(reserve_check)
		{
			return 1;
		}
	}
	*(size_t**)vector->top = data;
	*(size_t*)&vector->top += ELEMENT_SIZE;
	return 0;
}

void *VectorGetElement(vector_t *vector, size_t pos)
{
	assert(NULL != vector);

	return (void*)((size_t)(vector->base)+(pos * ELEMENT_SIZE));
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	return (((size_t)vector->top - (size_t)vector->base) / ELEMENT_SIZE);
}

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	*(size_t*)&vector->top -= ELEMENT_SIZE;

}

void VectorSetElement(vector_t *vector, size_t pos, void *data)
{
	assert(NULL != vector);
	*(size_t**)((size_t)vector->base + (pos * ELEMENT_SIZE)) = data;
}

int VectorShrinkToFit(vector_t *vector)
{
	size_t size = 0;
	int reserve_check = 0;

	assert(NULL != vector);
	size = VectorSize(vector);

	reserve_check = VectorReserve(vector, size);

	if(reserve_check)
	{
		return 1;
	}

	return 0;
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	size_t size = 0;
	void *buffer = 0;
	
	assert(NULL != vector);
	size = VectorSize(vector);	
	buffer = realloc(vector->base, (new_capacity * ELEMENT_SIZE));
	if(0 == buffer)
	{
		return 1;
	}

	vector->base = buffer;

	vector->max = (size_t *)vector->base + new_capacity;
	vector->top = (size_t *)vector->base + size;

	return 0;
}
