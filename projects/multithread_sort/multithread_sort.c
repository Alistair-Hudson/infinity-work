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
#include <string.h>     /* strlen */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != ptr))
#define DICTIONARY_SIZE         (100000)
#define DICT_LOCAL              ("/usr/share/dict/american-english")
#define THREAD_LIMIT            (2)
#define ARRAY_SIZE              (DICTIONARY_SIZE)
#define MAX_CHAR                (100)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct sort_hand
{
    int* array;
    size_t array_size;
    int min;
    int max;
    size_t array_breakdown;
    int* LUT;
}sort_hand_t;

static size_t thread = 0;
void* ArrayCount(void* arg);

int CountArray(sort_hand_t* handler, size_t tid);
int SortCount(sort_hand_t* handler);
int DictionaryScan(sort_hand_t* handler, size_t tid);

static void CreateLUT(int *lookup_array, size_t range);
static size_t ABSRange(int max, int min);

/******FUNCTIONS******/

int main()
{
    sort_hand_t handler = {0};
    pthread_t threads[THREAD_LIMIT];
    size_t i = 0;
    
    handler.array_size = ARRAY_SIZE;
    handler.min = 0;
    handler.max = MAX_CHAR;
    handler.array_breakdown = ARRAY_SIZE/THREAD_LIMIT;
    handler.array = (int*)malloc(sizeof(int)*ARRAY_SIZE);
    if (NULL == handler.array)
	{
		return 1;
	}
    handler.LUT = (int*)malloc(sizeof(int) *ABSRange(handler.max, handler.min));
	if (NULL == handler.LUT)
	{
        free(handler.array);
		return 1;
	}
    CreateLUT(handler.LUT, ABSRange(handler.max, handler.min));

    for  (i = 0; i < THREAD_LIMIT; ++i)
    {
        while(pthread_create(&threads[i], NULL, ArrayCount, &handler))
        {
        }
    }

    for (i = 0; i < THREAD_LIMIT; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    SortCount(&handler);

    for (i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("%d\n", handler.array[i]);
        /*sleep(1);*/
    }
    
    free(handler.array);   
    free(handler.LUT);
    return 0;
}

void* ArrayCount(void* arg)
{
    size_t tid = __sync_fetch_and_add(&thread, 1);
    DictionaryScan(arg, tid);
    CountArray(arg, tid);
    return NULL;
}

int CountArray(sort_hand_t* handler, size_t tid)
{
	size_t index = handler->array_breakdown * tid;
    size_t lowest_index = index;
	for (index = lowest_index; index < handler->array_size && index < (lowest_index + handler->array_breakdown); ++index)
	{
		handler->LUT[handler->array[index] - handler->min] += 1;
	}
	
	return 0;
}
int SortCount(sort_hand_t* handler)
{
    int insert = 0;
	size_t index = 0;
	for (insert = handler->min; insert <= handler->max; ++insert)
	{
		while (0 < handler->LUT[insert - handler->min])
		{
			handler->array[index] = insert;
			++index;
			handler->LUT[insert - handler->min] -= 1;
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

int DictionaryScan(sort_hand_t* handler, size_t tid)
{
    char buffer[MAX_CHAR] = {0};
    
    size_t index = handler->array_breakdown * tid;
    size_t lowest_index = index;
    FILE* fp = fopen(DICT_LOCAL, "r");
    if (NULL == fp)
    {
        perror("failed to open dictionary");
        sleep(5);
        return 1;
    }
	for (index = lowest_index; index < handler->array_size && index < (lowest_index + handler->array_breakdown); ++index)
	{

        fscanf(fp, "%s", buffer);
		handler->array[index] = strlen(buffer);
        if (feof(fp))
        {
            break;
        }
	}

    if (fclose(fp))
    {
        perror("failed to close dicxtionary");
        sleep(5);
        return 1;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 8deed0c1f641a62cbf36cd38999de7fe9bca6e28
    return 0;
}
