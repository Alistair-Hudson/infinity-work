IDIR =../ds/pqueue
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR=obj
LDIR =../lib

_DEPS = scheduler.h dlist.h pqueue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = scheduler.o dlist.o pqueue.o



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scheduler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
