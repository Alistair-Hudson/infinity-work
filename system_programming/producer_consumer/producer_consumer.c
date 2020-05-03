/***ONE PRODUCER, ONE CONSUMER***/
typedef struct sempahore
{
	int read_or_write;
	char* buffer[BUFFER_LIMIT];
}semaphore_t;

int Producer(semaphore_t *semaphore, const char* message)
{
	/*check if semaphore is free*/
		/*set semaphore to write*/
		semaphore.read_or_write = WRITE;
		/*copy message to buffer*/
		strncpy(semaphore.buffer, message, BUFFER_LIMIT);
		/*set semaphore to free*/
		semaphore.read_or_write = FREE;
	return 0; 
}

int Consumer(semaphore_t *semaphore, char* receiver)
{
	/*check if semaphore is free*/
		/*set semaphore to read*/
		semaphore.read_or_write = READ;
		/*copy message from buffer*/
		strcpy(receiver, semaphore.buffer, BUFFER_LIMIT);
		/*set semaphore to free*/
		semaphore.read_or_write = FREE;
	return 0;
}


/***MULTIPLE PRODUCERS, MULTIPLE CONSUMERS***/
typedef struct lock
{
	int read_or_write;
	int in_use_mutex;
	linked_list_t *buffer;
}lock_t;

int Producer(lock_t *lock, void* data)
{
	/*check if lock is set to write*/
		/*check if lock is in use*/
			/*set lock to in use*/
			/*write to buffer*/
			/*set lock to read*/
			/*free lock*/
	return 0;
}

int Consumer(lock_t *lock, void* receiver)
{
	/*check if lock is set to read*/
		/*check if lock is in use*/
			/*set lock to in use*/
			/*read from buffer*/
			/*set lock to write*/
			/*free lock*/
	return 0;
}

/***FIXED SIZE QUEUE***/
typedef struct lock
{
	int read_or_write;
	int in_use;
	queue_t *queue;
}lock_t;

int Producer(lock_t *lock, void* data)
{
	/*check if lock is set to write*/
		/*check if lock is in use*/
			/*set lock to in use*/
			/*write to buffer*/
			/*set lock to read*/
			/*free lock*/
	return 0;
}

int Consumer(lock_t *lock, void* receiver)
{
	/*check if lock is set to read*/
		/*check if lock is in use*/
			/*set lock to in use*/
			/*read from buffer*/
			/*set lock to write*/
			/*free lock*/
	return 0;
}

/***OVERFLOW, UNDERFLOW***/

/***BARRIER***/
