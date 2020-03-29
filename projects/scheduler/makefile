IDIR =../../ds/include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR=../../ds/obj
LDIR =../../ds/lib

_DEPS = scheduler.h dlist.h pqueue.h task.h uid.h heap.h vector.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = scheduler.o dlist.o pqueue.o task.o uid.o heap.o vector.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(LDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

scheduler: scheduler_test.c $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
