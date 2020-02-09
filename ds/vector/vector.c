#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include "vector.h"

/*****MACROS*****/
#define ELEMENT_SIZE (sizeof(void*))

/*****STRUCTURE TO HANDLE THE STACK******/
struct vector
{
	void *base;
	void *max;
	void *top;
};

/******FUNCTION DECLARATIONS********/
vector_t *VectorCreate(size_t capacity);
void VectorDestroy(vector_t *vector);

void VectorPopBack(vector_t *vector);
int VectorPushBack(vector_t *vector, void *data);

size_t VectorSize(const vector_t *vector);
int VectorIsEmpty(const vector_t *vector);
size_t VectorCapacity(const vector_t *vector);

void VectorSetElement(vector_t *vector, size_t pos, void *data);
void *VectorGetElement(vector_t *vector, size_t pos);

int VectorReserve(vector_t *vector, size_t new_capacity);
int VectorShrinkToFit(vector_t *vector);

/******FUNCTION DEFINITIONS********/
vector_t *VectorCreate(size_t capacity)
{
	vector_t *_vector = malloc(sizeof(struct vector) * ELEMENT_SIZE);
	assert(0 != _vector);
	_vector->base = malloc(capacity * ELEMENT_SIZE);
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
	size_t next_top_loc = (size_t)vector->top + ELEMENT_SIZE;
	assert(NULL != vector);
	if ((size_t)vector->max <= next_top_loc)
	{
		return 0;
	}
	*(size_t**)vector->top = data;
	*(size_t*)&vector->top += ELEMENT_SIZE;
	return 1;
}

void *VectorGetValue(vector_t *vector, size_t pos)
{
	assert(NULL != vector);
	if(VectorIsEmpty(vector))
	{
		return 0;
	}
	return (size_t*)((size_t)(vector->base)+(pos * ELEMENT_SIZE));
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
