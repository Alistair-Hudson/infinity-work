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
#define DICTIONARY_SIZE         (100000)
#define DICT_LOCAL              ("/usr/share/dict/american-english")
#define THREAD_LIMIT            (4)
#define ARRAY_SIZE              (DICTIONARY_SIZE)
#define MAX_CHAR                (100)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct handler
{
    char array[DICTIONARY_SIZE][MAX_CHAR];
    char swap_buffer[MAX_CHAR];
    size_t array_size;
    size_t threads;
    size_t array_breakdown;
}sort_hand_t;

static size_t threadID = 0;
void* ArrayCount(void* arg);

int DictionaryScan(sort_hand_t* handler);

/******FUNCTIONS******/

int main ()
{
    handler_t handler = {0};

    handler.array_size = ARRAY_SIZE;
    handler.threads = THREAD_LIMIT;
    handler.array_breakdown = ARRAY_SIZE/THREAD_LIMIT;

    if (ScanDictionary(handler))
    {
        return 1;
    }
    ThreadBreakDown(handler);
    return 0;
}

int DictionaryScan(sort_hand_t* handler)
{   
    size_t index = 0;

    FILE* fp = fopen(DICT_LOCAL, "r");
    if (NULL == fp)
    {
        perror("failed to open dictionary");
        return 1;
    }
	for (index = 0; index < handler->array_size ; ++index)
	{

        fscanf(fp, "%s", handler->array[index]);
        if (feof(fp))
        {
            break;
        }
	}

    if (fclose(fp)) 
    {
        perror("failed to close dicxtionary");
        return 1;
    }
    
    return 0;
}

int Shuffle(const void* word1, const void* word2)
{
    return 0;
}

int CompareWords(const void* word1, const void* word2)
{
    return strcmp((char*)word1, (char*)word2);
}

void ThreadBreakDown(sort_hand_t* handler)
{
    int i = 0;
    pthread_t thread[THREAD_LIMIT];
    if (0 >= handler->threads)
    {
        return;
    }

    for (i = 0; i < handler->threads; ++i)
    {
        while(pthread_create(&thread[i], NULL, QSort, &handler))
        {
        }
    }
    
    for (i = 0; i < handler->threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    handler->threads /= 2;
    handler->array_breakdown = handler->array_size / handler->threads;
    ThreadBreakDown(handler);

}

void* QSort(void* arg)
{
    sort_hand_t* handler = arg;
    int tid = _sync_fetch_and_add(threadID, 1);
    QSortImp(handler->array_breakdown*tid, 
            handler->array_breakdown*(tid+1), 
            handler);
    return NULL;
}

static void QSortImp(size_t begin, size_t end, sort_hand_t* handler)
{	
    end = end <= handler->array_size ? end : handler->array_size;
	if (begin == end)
	{
		return;
	}
	/*if low is before high*/
	if (0 >= strcmp(handler->array[begin], handler->array[end]))
	{
		/*create a partition index*/
		size_t part_index = QSPartion(begin, end, handler);

		/*recursion on lower partition*/
		QSortImp(begin, part_index, handler);
		/*recursion on upper partition*/
		QSortImp(part_index, end, handler);
	}
}
static size_t QSPartion(size_t begin, size_t end, sort_hand_t* handler)
{
	size_t pivot = end <= handler->array_size ? end : handler->array_size;
	size_t swap = begin;

	/*for index from low to high*/
	for (begin; begin <= end; ++begin)
	{
		/*if index is before pivot*/
		if (0 >= strcmp(handler->array[begin], handler->array[pivot]))
		{
			/*increase low*/
			++swap;
			/*swap*/
			QSSwap(swap, begin, handler);
		}
	}
	/*swap low and high*/
	QSSwap(swap, end, handler);
	/*return low +1*/
	return swap;
}

static void QSSwap(size_t item1, size_t item2, sort_hand_t* handler)
{
	/*put index1 into a temporary variable*/
	strcpy(handler->swap_buffer, handler->array[item1]);
	/*put index2 into index1*/
	strcpy(handler->array[item1], handler->array[item2]);
	/*put the temporary varible into index2*/
	strcpy(handler->array[item2], handler->swap_buffer);
}