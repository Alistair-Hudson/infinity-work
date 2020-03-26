#include <stdlib.h>		/*malloc*/
#include <assert.h>		/*assert*/
#include "vector.h"

/*****MACROS*****/
#define ELEMENT_SIZE 	(sizeof(void*))
#define PUSH_ADJST		((VectorSize(vector)+1)*2)
/*****STRUCTURE TO HANDLE THE STACK******/
struct vector
{
	size_t capacity;
	size_t top;
	void** elements;
};

/******FUNCTION DEFINITIONS********/
vector_t *VectorCreate(size_t capacity)
{
	vector_t *_vector = malloc(sizeof(struct vector) + capacity * ELEMENT_SIZE);
	if(NULL == _vector)
	{
		return NULL;
	}
	_vector->capacity = capacity;
	_vector->top = 0;
	_vector->elements = (void**)malloc(capacity * ELEMENT_SIZE);

	return _vector;
}

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	assert(NULL != vector->elements);
	free(vector->elements);
	vector->elements = NULL;
	free(vector);
	vector = NULL;
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(NULL != vector);
	if(0 == vector->top) {return 1;}
	return 0;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

int VectorPushBack(vector_t *vector, void *data)
{
	int reserve_check = 0;

	assert(NULL != vector);
	if (VectorSize(vector) == VectorCapacity(vector))
	{
		reserve_check = VectorReserve(vector, PUSH_ADJST);
		if(reserve_check)
		{
			return 1;
		}
	}
	vector->elements[vector->top] = data;
	++vector->top;
	return 0;
}

void *VectorGetElement(vector_t *vector, size_t pos)
{
	assert(NULL != vector);

	return vector->elements[pos];
}

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	return vector->top;
}

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	--vector->top;

}

void VectorSetElement(vector_t *vector, size_t pos, void *data)
{
	assert(NULL != vector);
	vector->elements[pos] = data;
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
	void** buffer = 0;
	
	assert(NULL != vector);
	size = VectorSize(vector);	
	buffer = (void**)realloc(vector->elements, (new_capacity * ELEMENT_SIZE));
	if(0 == buffer)
	{
		return 1;
	}

	vector->elements = buffer;

	vector->capacity = new_capacity;
	return 0;
}
