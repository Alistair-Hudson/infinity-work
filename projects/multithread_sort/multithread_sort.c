/******************************************************************************
 *	Title:		Multi - Thread sorerting
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	18.05.2020.0
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>      /* printf */
#include <assert.h>		/* assert */
#include <pthread.h>    /* thread functions */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define THREAD_LIMIT            (1)
#define ARRAY_SIZE              (10)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sort_hand
{
    int* array;
    size_t array_size;
    int min;
    int max;
    int* LUT;
}sort_hand_t;

int CountingSort(int *array, size_t array_size, int min, int max);

static void CreateLUT(int *lookup_array, size_t range);
static size_t ABSRange(int max, int min);

/******FUNCTIONS******/

int main()
{
    sort_hand_t handler = {0};
    pthread_t threads[THREAD_LIMIT];
    size_t i = 0;
    int array[ARRAY_SIZE] = {5, 7, 9, 1, 3, 8, 2, 6, 4, 0};

    handler.array = array;
    handler.array_size = ARRAY_SIZE;
    handler.min = 0;
    handler.max = 9;
    handler.LUT = (int*)malloc(sizeof(int) *ABSRange(handler.max, handler.min));
	if (NULL == handler.LUT)
	{
		return 1;
	}
    CreateLUT(handler.LUT, ABSRange(handler.max, handler.min));

    for  (i = 0; i < THREAD_LIMIT; ++i)
    {
        pthread_create(&threads, NULL, ArrayCount, &handler);
    }

    for (i = 0; i < THREAD_LIMIT; ++i)
    {
        pthread_join(threads[i], NULL);
    }
    
    SortCount(hadler->array, handler->array_size, handler->min, handler->max, handler->LUT);

    for (i = 0; i < ARRAY_SIZE, ++i)
    {
        printf("%d\n", array[i]);
    }

    free(handler.LUT);
    return 0;
}

void* ArrayCount(void* arg)
{
    sort_hand_t* handler = arg;
    CountArray(hadler->array, handler->array_size, handler->min, handler->max, handler->LUT);
    return NULL;
}

int CountArray(int *array, size_t array_size, int min, int max, int* LUT)
{
	size_t index = 0;

	for (index = 0; index < array_size; ++index)
	{
		LUT[array[index] - min] += 1;
	}
	

	return 0;
}
int SortCount(int *array, size_t array_size, int min, int max, int* LUT)
{
    int insert = 0;
	size_t index = 0;
	for (insert = min; insert <= max; ++insert)
	{
		while (0 < LUT[insert - min])
		{
			array[index] = insert;
			++index;
			LUT[insert - min] -= 1;
		}
	}
	return 0;
}

static void CreateLUT(int *lookup_array, size_t range)
{
	size_t lut_index = 0;
	
	for (lut_index = 0; lut_index <= range; ++lut_index)
	{
		lookup_array[lut_index] = 0;
	}
}

static size_t ABSRange(int max, int min)
{
	if (max < min)
	{
		int temp = 0;
		temp = max;
		max = min;
		min = temp;
	}

	return max - min;
}