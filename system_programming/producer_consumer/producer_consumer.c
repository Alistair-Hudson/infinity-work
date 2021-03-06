/******************************************************************************
 *	Title:		Producer Consumer
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	07.05.2020.1
 ******************************************************************************/
#include <stdlib.h>		/* atoi */
#include <assert.h>		/* assert */
#include <stdio.h>		/* printf, fgets*/
#include <errno.h>		/* perror */
#include <pthread.h>	/* pthread functions */
#include <time.h>		/* time */
#include <sys/types.h>	/* Sys V functions */
#include <sys/sem.h>	/* Sys V functions */
#include <string.h>		/* strstr */
#include <ctype.h>		/* isdigit */
#include <semaphore.h>	/* semaphore functions */

#include "slist.h"		/* slist functions */
#include "queue.h"		/* queue functions */

/******MACROS******/
#define ASSERT_NOT_NULL(ptr)	(assert(NULL != (ptr)))
#define BUFFER_LIMIT			(100)
#define READ					(1)
#define WRITE					(2)
#define QUE_SIZE				(10)

/******TYPEDEFS, GLOBAL VARIABLES AND INTERNAL FUNCTIONS******/
typedef struct EX1
{
	int read_or_write;
	char buffer[BUFFER_LIMIT];
}EX1_t;

typedef struct EX21
{
	int list_size;
	pthread_mutex_t in_use_mutex;
	list_t* buffer;
}EX21_t;

typedef struct EX22
{
	sem_t is_empty;
	pthread_mutex_t in_use_mutex;
	list_t* buffer;
}EX22_t;

typedef struct EX31
{
	sem_t free_space;
	sem_t size;
	pthread_mutex_t in_use_mutex;
	queue_t* queue;
}EX31_t;

typedef struct EX32
{
	sem_t free_space;
	sem_t size;
	pthread_mutex_t write_in_use;
	pthread_mutex_t read_in_use;
	queue_t* queue;
}EX32_t;

typedef struct EX41
{
	int read;
	int write;
	pthread_mutex_t in_use_mutex;
	list_t* buffer;
}EX41_t;

typedef struct EX42
{
	int write_index;
	int read_index;
	pthread_mutex_t write_in_use;
	pthread_mutex_t read_in_use;
	int queue[QUE_SIZE];
}EX42_t;

typedef struct EX5
{
	int total_consumers;
	int consumers_needed_to_read;
	pthread_mutex_t in_use_mutex;
	pthread_cond_t barrier;
	int have_read_array;
	char buffer[BUFFER_LIMIT];
}EX5_t;

int SingleProdCon(void);
void* Producer1(void* buffer);
void* Consumer1(void* buffer);

int MultiProdCon1(void);
void* Producer21(void* buffer);
void* Consumer21(void* buffer);

int MultiProdCon2(void);
void* Producer22(void* buffer);
void* Consumer22(void* buffer);

int FSQProdCon1(void);
void* Producer31(void* buffer);
void* Consumer31(void* buffer);

int FSQProdCon2(void);
void* Producer32(void* buffer);
void* Consumer32(void* buffer);

int OverUnderFlow1(void);
void* Producer41(void* buffer);
void* Consumer41(void* buffer);

int OverUnderFlow2(void);
void* Producer42(void* buffer);
void* Consumer42(void* buffer);

int Barrier(void);
void* Producer5(void* buffer);
void* Consumer5(void* buffer);

/******FUNCTIONS******/
int main()
{
	int status = 0;

	status = FSQProdCon2();

	return status;
}

/*==ONE PRODUCER, ONE CONSUMER==*/
int SingleProdCon()
{
	pthread_t tid[2];
	EX1_t buffer = {0, {0}};

	pthread_create(&tid[0], NULL, Producer1, &buffer);
	pthread_create(&tid[1], NULL, Consumer1, &buffer);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}

void* Producer1(void* arg)
{
	EX1_t* buffer = arg; 
	char* message = "This is a mesage\n";
	/*loop if buffer is not write*/
	while (0 != __sync_lock_test_and_set(&buffer->read_or_write, 1))
	{
		sleep(0);
	}
	/*copy message to buffer*/
	printf("Sending Message...\n");
	strncpy(buffer->buffer, message, BUFFER_LIMIT);
	/*releaase buffer*/
	__sync_lock_release(&buffer->read_or_write);

	return NULL; 
}

void* Consumer1(void* arg)
{
	EX1_t* buffer = arg;
	/*loop if buffer is not read*/
	while (0 != __sync_lock_test_and_set(&buffer->read_or_write, 1))
	{
		sleep(0);
	}
	/*copy message from buffer*/
	printf("Message: %s\n", buffer->buffer);
	/*release buffer*/
	__sync_lock_release(&buffer->read_or_write);

	return NULL;
}


/*==MULTIPLE PRODUCERS, MULTIPLE CONSUMERS==*/
/*1*/
int MultiProdCon1()
{
	pthread_t tid[4];
	EX21_t buffer = {0, 0, 0};

	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	buffer.buffer = SListCreate();
	if (NULL == buffer.buffer)
	{
		printf("List creation failed\n");
		return 1;
	}	

	pthread_create(&tid[0], NULL, Producer21, &buffer);
	pthread_create(&tid[1], NULL, Consumer21, &buffer);

	pthread_create(&tid[2], NULL, Producer21, &buffer);
	pthread_create(&tid[3], NULL, Consumer21, &buffer);


	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	
	SListDestroy(buffer.buffer);

	return 0;
}

void* Producer21(void* arg)
{
	EX21_t* buffer = arg;
	char message[] =  "This is a message\n";
	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Sending message...\n");
	SListInsertBefore(buffer->buffer, SListEnd(buffer->buffer), &message);	
		/*set not empty*/
	buffer->list_size += 1;
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer21(void* arg)
{
	EX21_t* buffer = arg;

	/*loop if lock is not empty*/
	while (0 != buffer->list_size)
	{
		/*check if lock is in use*/
			/*set lock to in use*/
		pthread_mutex_lock(&buffer->in_use_mutex);

			/*read from buffer*/
		printf("Message: %s\n", (char*)SListGetData(SListBegin(buffer->buffer)));
		SListRemove(SListBegin(buffer->buffer));
			/*decrease read_or_write*/
		buffer->list_size -= 1;
		if (0 > buffer->list_size)
		{
			buffer->list_size = 0;
		}
			/*free lock*/
		pthread_mutex_unlock(&buffer->in_use_mutex);
	}

	return NULL;
}

/*2*/
int MultiProdCon2()
{
	pthread_t tid[4];
	EX22_t buffer = {0, 0, 0};

	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	buffer.buffer = SListCreate();
	if (NULL == buffer.buffer)
	{
		printf("List creation failed\n");
		return 1;
	}	

	pthread_create(&tid[0], NULL, Producer22, &buffer);
	pthread_create(&tid[1], NULL, Consumer22, &buffer);

	pthread_create(&tid[2], NULL, Producer22, &buffer);
	pthread_create(&tid[3], NULL, Consumer22, &buffer);


	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	SListDestroy(buffer.buffer);

	return 0;
}

void* Producer22(void* arg)
{
	EX22_t* buffer = arg;
	char message[] =  "This is a message\n";

	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Sending message...\n");
	SListInsertBefore(buffer->buffer, SListEnd(buffer->buffer), &message);	
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);
		/*increase semaphore*/
	sem_post(&buffer->is_empty);
	return NULL;
}

void* Consumer22(void* arg)
{
	EX22_t* buffer = arg;

		/*if semaphore is availble*/
	sem_wait(&buffer->is_empty);
			/*check if lock is in use*/
				/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);
				/*read from buffer*/
	printf("Message: %s\n", (char*)SListGetData(SListBegin(buffer->buffer)));
	SListRemove(SListBegin(buffer->buffer));
				/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

/*==FIXED SIZE QUEUE==*/
/*1*/
int FSQProdCon1()
{
	pthread_t tid[30];
	EX31_t buffer = {0, 0, 0, {0}};
	int i = 0;
	
	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	buffer.queue = QCreate();
	if (NULL == buffer.queue)
	{
		printf("Queue creation failed\n");
		return 1;
	}	

	sem_init(&buffer.free_space, 0, QUE_SIZE);

	for (i = 0; i < 15; ++i)
	{
		pthread_create(&tid[i], NULL, Producer31, &buffer);
		pthread_create(&tid[i+15], NULL, Consumer31, &buffer);
	}
	for (i = 0; i < 30; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	QDestroy(buffer.queue);

	return 0;
}

void* Producer31(void* arg)
{
	EX31_t* buffer = arg;
	char message[] = "This is a message\n";

	/*check if not in_use*/
		/*set in_use*/
	sem_wait(&buffer->free_space);
	pthread_mutex_lock(&buffer->in_use_mutex);
		/*write to queue*/
	printf("Sending message...\n");
	QEnqueue(buffer->queue, &message);

		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);
	sem_post(&buffer->size);

	return NULL;
}

void* Consumer31(void* arg)
{
	EX31_t* buffer = arg;

	/*loop if read is equal to written*/
	sem_wait(&buffer->size);
	/*check if not in_use*/
		/*set in_use*/
	pthread_mutex_lock(&buffer->in_use_mutex);
		/*read from buffer*/
	printf("Message: %s\n", QPeek(buffer->queue));
	QDequeue(buffer->queue);


		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);
	sem_post(&buffer->free_space);

	return NULL;
}

/*2*/
int FSQProdCon2()
{
	pthread_t tid[30];
	EX32_t buffer = {0, 0, 0, 0, {0}};
	int i = 0;

	if (pthread_mutex_init(&buffer.write_in_use, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	if (pthread_mutex_init(&buffer.read_in_use, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	buffer.queue = QCreate();
	if (NULL == buffer.queue)
	{
		printf("Queue creation failed\n");
		return 1;
	}

	sem_init(&buffer.free_space, 0, QUE_SIZE);

	for (i = 0; i < 15; ++i)
	{
		pthread_create(&tid[i], NULL, Producer32, &buffer);
		pthread_create(&tid[i+15], NULL, Consumer32, &buffer);
	}
	for (i = 0; i < 30; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	QDestroy(buffer.queue);

	return 0;
}

void* Producer32(void* arg)
{
	EX32_t* buffer = arg;
	char message[] = "This is a message\n";

	/*check if not in_use*/
		/*set in_use*/
	sem_wait(&buffer->free_space);
	pthread_mutex_lock(&buffer->write_in_use);

		/*write to queue*/
	printf("Sending message...\n");
	QEnqueue(buffer->queue, &message);

		/*free lock*/
	pthread_mutex_unlock(&buffer->write_in_use);
	sem_post(&buffer->size);

	return NULL;
}

void* Consumer32(void* arg)
{
	EX32_t* buffer = arg;

	/*check if not in_use*/
		/*set in_use*/
	sem_wait(&buffer->size);
	pthread_mutex_lock(&buffer->read_in_use);

		/*read from buffer*/
	printf("Message: %s\n", QPeek(buffer->queue));
	QDequeue(buffer->queue);

		/*free lock*/
	pthread_mutex_unlock(&buffer->read_in_use);
	sem_post(&buffer->free_space);

	return NULL;
}

/*==OVERFLOW, UNDERFLOW==*/
/*1*/
int OverUnderFlow1()
{
	pthread_t tid[30];
	EX41_t buffer = {0, 0, 0, 0, {0}};
	int i = 0;

	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	buffer.buffer = SListCreate();
	if (NULL == buffer.buffer)
	{
		printf("List creation failed\n");
		return 1;
	}	

	for (i = 0; i < 15; ++i)
	{
		pthread_create(&tid[i], NULL, Producer41, &buffer);
		pthread_create(&tid[i+15], NULL, Consumer41, &buffer);
	}
	for (i = 0; i < 30; ++i)
	{
		pthread_join(tid[i], NULL);
	}
	
	SListDestroy(buffer.buffer);

	return 0;
}

void* Producer41(void* arg)
{
	EX41_t* buffer = arg;

	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Writer\n");

		/*increase counter*/
	__sync_fetch_and_add(&buffer->write, 1);
	__sync_val_compare_and_swap(&buffer->write, QUE_SIZE, 0);
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer41(void* arg)
{
	EX41_t* buffer = arg;

	/*check reader is not equal to writer*/
	while (buffer->write == buffer->read)
	{
	}
	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Reader\n");

		/*decrease counter*/
	__sync_fetch_and_add(&buffer->read, 1);
	__sync_val_compare_and_swap(&buffer->read, QUE_SIZE, 0);

		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

/*2*/
int OverUnderFlow2()
{
	pthread_t tid[30];
	EX42_t buffer = {0, 0, 0, 0, {0}};
	int i = 0;

	if (pthread_mutex_init(&buffer.write_in_use, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	if (pthread_mutex_init(&buffer.read_in_use, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}

	for (i = 0; i < 15; ++i)
	{
		pthread_create(&tid[i], NULL, Producer42, &buffer);
		pthread_create(&tid[i+15], NULL, Consumer42, &buffer);
	}
	for (i = 0; i < 30; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

void* Producer42(void* arg)
{
	EX42_t* buffer = arg;

	/*check if not write_in_use*/
		/*set write_in_use*/
	pthread_mutex_lock(&buffer->write_in_use);
	if (buffer->read_index == buffer->write_index)
	{
		pthread_mutex_lock(&buffer->write_in_use);
	}
		/*write to queue*/
	printf("Sending message...\n");
	buffer->queue[buffer->write_index] = 13;

	if (buffer->read_index == buffer->write_index)
	{
		pthread_mutex_unlock(&buffer->write_in_use);
	}
		/*increase written*/
	__sync_fetch_and_add(&buffer->write_index, 1);
	__sync_val_compare_and_swap(&buffer->write_index, QUE_SIZE, 0);
		/*free lock*/
	pthread_mutex_unlock(&buffer->write_in_use);

	return NULL;
}

void* Consumer42(void* arg)
{
	EX42_t* buffer = arg;

	/*check if not read_in_use*/
		/*set read_in_use*/
	pthread_mutex_lock(&buffer->read_in_use);
	
	while (buffer->write_index == buffer->read_index)
	{
	}
		/*read from buffer*/
	printf("Message: %d\n", buffer->queue[buffer->read_index]);
		/*increase read*/
	__sync_fetch_and_add(&buffer->read_index, 1);
	__sync_val_compare_and_swap(&buffer->read_index, QUE_SIZE, 0);
		/*free lock*/
	pthread_mutex_unlock(&buffer->read_in_use);

	return NULL;
}

/*==BARRIER==*/
int Barrier()
{
	pthread_t tid[10];
	EX5_t buffer = {0, 0, 0, 0, 0, {0}};
	int i = 0;

	buffer.total_consumers = 10;

	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}
	if (pthread_cond_init(&buffer.barrier, NULL))
	{
		perror("cond init failed");
		return 1;
	}

	for (i = 0; i < 10; ++i)
	{
		pthread_create(&tid[i], NULL, Consumer5, &buffer);
	}
	sleep(1);
	Producer5(&buffer);

	for (i = 0; i < 20; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

void* Producer5(void* arg)
{
	EX5_t* buffer = arg;
	char message[] = "This is a message\n";

	/*check if not in use*/
		/*set in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);
	while (buffer->consumers_needed_to_read)
	{
		pthread_cond_wait(&buffer->barrier, &buffer->in_use_mutex);
	}
		/*write to buffer*/
	printf("Sending message...\n");
	strncpy(buffer->buffer, message, BUFFER_LIMIT);

		/*set conumers needed to read to the total number of consumers*/
	buffer->consumers_needed_to_read = buffer->total_consumers;
		/*set read array to zero*/
	
		/*free lock*/
	pthread_cond_signal(&buffer->barrier);
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer5(void* arg)
{
	EX5_t* buffer = arg;

			/*check if in use*/
				/*set lock*/
	pthread_mutex_lock(&buffer->in_use_mutex);
	while (!buffer->consumers_needed_to_read /*&& thread has not read*/)
	{
		pthread_cond_wait(&buffer->barrier, &buffer->in_use_mutex);
	}
				/*read from buffer*/
	printf("Message: %s\n", buffer->buffer);
				/*decrease consumers need to read*/
	buffer->consumers_needed_to_read -= 1;
				/*if consumers need to read equals zero*/
					/*decrease written*/
	if (0 > buffer->consumers_needed_to_read)
	{
		buffer->consumers_needed_to_read = 0;
	}
				/*free lock*/
	pthread_cond_signal(&buffer->barrier);
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}
