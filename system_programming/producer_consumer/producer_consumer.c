/******************************************************************************
 *	Title:		Producer Consumer
 *	Authour:	Alistair Hudson
 *	Reviewer:	
 *	Version:	04.05.2020.0
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
	char* buffer[BUFFER_LIMIT];
}EX1_t;

typedef struct EX21
{
	int is_empty;
	pthread_mutex_t in_use_mutex;
	int buffer;
}EX21_t;

typedef struct EX22
{
	sem_t is_empty;
	pthread_mutex_t in_use_mutex;
	int buffer;
}EX22_t;

typedef struct EX31
{
	sem_t written;
	sem_t read;
	pthread_mutex_t in_use_mutex;
	int queue[QUE_SIZE];
}EX31_t;

typedef struct EX32
{
	sem_t written;
	sem_t read;
	pthread_mutex_t write_in_use;
	pthread_mutex_t read_in_use;
	int queue[QUE_SIZE];
}EX32_t;

typedef struct EX41
{
	int read;
	int Write;
	int in_use_mutex;
	int *buffer;
}EX41_t;

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

/******FUNCTIONS******/


/*==ONE PRODUCER, ONE CONSUMER==*/
int SingleProddCon()
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
	/*loop if buffer is not write*/
	while (WRITE != __sync_lock_test_and_set(&buffer->read_or_write, WRITE))
	{
		sleep(0);
	}
	/*copy message to buffer*/
	printf("Sending Message...\n");
	strncpy(*buffer->buffer, "This is a mesage\n", BUFFER_LIMIT);
	/*releaase buffer*/
	__sync_lock_release(&buffer->read_or_write);

	return NULL; 
}

void* Consumer1(void* arg)
{
	EX1_t* buffer = arg;
	/*loop if buffer is not read*/
	while (READ != __sync_lock_test_and_set(&buffer->read_or_write, READ))
	{
		sleep(0);
	}
	/*copy message from buffer*/
	printf("Message: %s\n", *buffer->buffer);
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
	
	pthread_create(&tid[0], NULL, Producer21, &buffer);
	pthread_create(&tid[1], NULL, Consumer21, &buffer);

	pthread_create(&tid[2], NULL, Producer21, &buffer);
	pthread_create(&tid[3], NULL, Consumer21, &buffer);


	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	return 0;
}

void* Producer21(void* arg)
{
	EX21_t* buffer = arg;
	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Writer\n");
		
		/*set not empty*/
	buffer->is_empty += 1;
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer21(void* arg)
{
	EX21_t* buffer = arg;
	/*loop if lock is not empty*/
	while (0 != buffer->is_empty)
	{
		/*check if lock is in use*/
			/*set lock to in use*/
		pthread_mutex_lock(&buffer->in_use_mutex);

			/*read from buffer*/
		printf("Reader\n");
			/*decrease read_or_write*/
		buffer->is_empty -= 1;
		if (0 > buffer->is_empty)
		{
			buffer->is_empty = 0;
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

	pthread_create(&tid[0], NULL, Producer22, &buffer);
	pthread_create(&tid[1], NULL, Consumer22, &buffer);

	pthread_create(&tid[2], NULL, Producer22, &buffer);
	pthread_create(&tid[3], NULL, Consumer22, &buffer);


	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	return 0;
}

void* Producer22(void* arg)
{
	EX22_t* buffer = arg;
	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/
	printf("Writer\n");
		/*increase semaphore*/
	sem_post(&buffer->is_empty);
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);
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
	printf("Reader\n");
				/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

/*==FIXED SIZE QUEUE==*/
/*1*/
int FSQProdCon1()
{
	pthread_t tid[20];
	EX31_t buffer = {0, 0, 0, {0}};
	int i = 0;

	if (pthread_mutex_init(&buffer.in_use_mutex, NULL))
	{
		perror("Mutex init failed");
		return 1;
	}

	sem_init(&buffer.written, 0, QUE_SIZE);

	for (i = 0; i < 10; ++i)
	{
		pthread_create(&tid[i], NULL, Producer31, &buffer);
		pthread_create(&tid[i+10], NULL, Consumer31, &buffer);
	}
	for (i = 0; i < 20; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

void* Producer31(void* arg)
{
	EX31_t* buffer = arg;

	/*check if not in_use*/
		/*set in_use*/
	sem_wait(&buffer->written);
	pthread_mutex_lock(&buffer->in_use_mutex);
		/*write to queue*/
	printf("Writer\n");
	sem_post(&buffer->read);
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer31(void* arg)
{
	EX31_t* buffer = arg;

	/*loop if read is equal to written*/
	sem_wait(&buffer->read);
	/*check if not in_use*/
		/*set in_use*/
	pthread_mutex_lock(&buffer->in_use_mutex);
		/*read from buffer*/
	printf("Reader\n");

	sem_post(&buffer->written);
		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

/*2*/
int FSQProdCon2()
{
	pthread_t tid[20];
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

	sem_init(&buffer.written, 0, QUE_SIZE);

	for (i = 0; i < 10; ++i)
	{
		pthread_create(&tid[i], NULL, Producer32, &buffer);
		pthread_create(&tid[i+10], NULL, Consumer32, &buffer);
	}
	for (i = 0; i < 20; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}

void* Producer32(void* arg)
{
	EX32_t* buffer = arg;

	/*check if not in_use*/
		/*set in_use*/
	sem_wait(&buffer->written);
	pthread_mutex_lock(&buffer->write_in_use);
		/*write to queue*/
	printf("Writer\n");
	sem_post(&buffer->read);
		/*free lock*/
	pthread_mutex_unlock(&buffer->write_in_use);

	return NULL;
}

void* Consumer32(void* arg)
{
	EX32_t* buffer = arg;

	/*loop if read is equal to written*/
	sem_wait(&buffer->read);
	/*check if not in_use*/
		/*set in_use*/
	pthread_mutex_lock(&buffer->read_in_use);
		/*read from buffer*/
	printf("Reader\n");

	sem_post(&buffer->written);
		/*free lock*/
	pthread_mutex_unlock(&buffer->read_in_use);

	return NULL;
}

/*==OVERFLOW, UNDERFLOW==*/
/*1*/

void* Producer41(void* arg)
{
	EX41_t* buffer = arg;

	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/

		/*increase counter*/
	__sync_fetch_and_add(&buffer->write, 1);

		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

void* Consumer41(void* arg)
{
	EX41_t* buffer = arg;

	/*check if lock is in use*/
		/*set lock to in use*/
	pthread_mutex_lock(&buffer->in_use_mutex);

		/*write to buffer*/

		/*decrease counter*/
	__sync_fetch_and_add(&buffer->read, 1);


		/*free lock*/
	pthread_mutex_unlock(&buffer->in_use_mutex);

	return NULL;
}

/*2*/
typedef struct lock42
{
	int write_index;
	int read_index;
	int write_in_use;
	int read_in_use;
	int *queue;
}lock42_t;

int Producer42(void)
{
	/*loop if lock has no writable space*/
	/*check if not write_in_use*/
		/*set write_in_use*/
		/*write to queue*/
		/*increase written*/
		/*if written equals max queue space*/
			/*set written back to 0*/
		/*free lock*/
	return 0;
}

int Consumer42(void)
{
	/*loop if read is equal to written*/
	/*check if not read_in_use*/
		/*set read_in_use*/
		/*read from buffer*/
		/*increase read*/
		/*if read equals max queue space*/
			/*set read back to zero*/
		/*free lock*/
	return 0;
}

/*==BARRIER==*/
typedef struct lock5
{
	int total_consumers;
	int consumers_needed_to_read;
	int in_use;
	int have_read_array;
	int buffer;
}lock5_t;

int Producer5(void)
{
	/*Loop until consumers need to read is zero*/
	/*check if not in use*/
		/*set in use*/
		/*write to buffer*/
		/*set conumers needed to read to the total number of consumers*/
		/*set read array to zero*/
		/*free lock*/
	return 0;
}

int Consumer5(void)
{
	/*loop infinately*/
		/*if not read bit */
			/*check if in use*/
				/*set lock*/
				/*read from buffer*/
				/*decrease consumers need to read*/
				/*if consumers need to read equals zero*/
					/*decrease written*/
				/*free lock*/
	return 0;
}
