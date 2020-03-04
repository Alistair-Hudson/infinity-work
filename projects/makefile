IDIR =../ds/include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR=obj
LDIR =../lib

_DEPS = scheduler.h dlist.h pqueue.h task.h uid.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = scheduler_test.o scheduler.o dlist.o pqueue.o task.o uid.o



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scheduler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
