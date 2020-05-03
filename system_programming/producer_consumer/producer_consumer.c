/***ONE PRODUCER, ONE CONSUMER***/
typedef struct sempahore
{
	int read_or_write;
	char* buffer[BUFFER_LIMIT];
}semaphore_t;

int Producer(semaphore_t *semaphore, const char* message)
{
	/*loop if semaphore is not write*/

	/*copy message to buffer*/
	/*set semaphore to read*/

	return 0; 
}

int Consumer(semaphore_t *semaphore, char* receiver)
{
	/*loop if semaphore is not read*/

	/*copy message from buffer*/
	/*set semaphore to write*/
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
	/*check if lock is in use*/
		/*set lock to in use*/
		/*write to buffer*/
		/*increase read_or_write*/
		/*free lock*/
	return 0;
}

int Consumer(lock_t *lock, void* receiver)
{
	/*loop if lock is empty*/
	/*check if lock is in use*/
		/*set lock to in use*/
		/*read from buffer*/
		/*decrease read_or_write*/
		/*free lock*/
	return 0;
}

/***FIXED SIZE QUEUE***/
typedef struct lock
{
	int written;
	int read;
	int write_in_use;
	int read_in_use;
	queue_t *queue;
}lock_t;

int Producer(lock_t *lock, void* data)
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

int Consumer(lock_t *lock, void* receiver)
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

/***OVERFLOW, UNDERFLOW***/

/***BARRIER***/
