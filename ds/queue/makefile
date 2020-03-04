CC=gcc
CFLAGS=-I.
DEPS =queue.h slist.h 
OBJ = queue.c  queue_test.c slist.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

queue: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

