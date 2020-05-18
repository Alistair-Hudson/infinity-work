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
#define DICTIONARY_SIZE         ()
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
int DictionaryScan(sort_hand_t* handler, size_t tid)

static void CreateLUT(int *lookup_array, size_t range);
static size_t ABSRange(int max, int min);

/******FUNCTIONS******/