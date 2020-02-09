#ifndef __VECTOR_H__
#define __VECTOR_H__

#include<stddef.h> /* size_t */

/* pointer to the structure that represents Vector */
typedef struct vector vector_t;


/* 
 * The function creates the vector_t vector with a given capacity 
 *
 * Return value:
 * pointer to the vector_t structure or NULL in case of creation failed
 * 
 * */
vector_t * VectorCreate(size_t capacity);


/*
 * The function deletes vector_t vector and frees memory
 *
 * */
void VectorDestroy(vector_t *vector);


/*
 * The function pop back one element in the given vector_t vector
 * If vector is empty the behavior is undefined. 
 *
 * */
void VectorPopBack(vector_t *vector);


/*
 * The function push back a void pointer element into the vector_t vector 
 * return 1 when fail to allocate memory and 1 when succeed
 * 
 * */
int VectorPushBack(vector_t *vector, void *element);


/*
 * The function returns pointer that stores the element in the position pos 
 * in the vector_t vector. If pos is greater than the vector capacity, the 
 * behavior is undefined.
 * 
 * Note: NULL can be stored as value as well
 *
 * */
void *VectorGetElement(vector_t *vector, size_t pos);


/*
 * The function accepts pointer to vector_t vector and returns the number
 * of elements in this structure
 * 
 * */
size_t VectorSize(const vector_t *vector);


/*
 * The function accepts pointer to vector_t vector structure and checks if it 
 * empty
 *
 * Return value:
 * 1 - the Vector is empty
 * 0 - the Vector is non-empty
 * 
 * */
int VectorIsEmpty(const vector_t *vector);


/*
 * The function returns the capacity value of the given vector_t vector
 *
 * */
size_t VectorCapacity(const vector_t *vector);


/*
 * The function allocate new_capacity memory space in the vector_t vector on. 
 * If the new_capacity is bigger than the current vector capacity, the behavior
 * is undefined.
 * Return 1 when fail to allocate memory and 1 when succeed.
 * 
 * */
int VectorReserve(vector_t *vector, size_t new_capacity);

/*
 * The function reduce memory space in the vector_t vector until it fit the
 * current size
 *
 * Return value:
 * 0 - success
 * 1 - unsuccessfull
 * */
int VectorShrinkToFit(vector_t *vector);

/*
 * The function set a new value in the position pos of the vector_t vector.
 * If pos is greater than the vector capacity, the behavior is undefined.
 *
 * Note: NULL can be stored as value as well
 *
 * */
void VectorSetElement(vector_t *vector, size_t pos, void *value);

#endif /* __VECTOR_H__ */
