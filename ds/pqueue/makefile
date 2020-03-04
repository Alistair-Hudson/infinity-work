CC=gcc
CFLAGS=-I.
DEPS =pqueue.h sorted_list.h dlist.h 
OBJ =  pqueue_test.c sorted_list.c dlist.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pqueue: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

