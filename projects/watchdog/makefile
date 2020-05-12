IDIR =../../ds/include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR) -pthread

ODIR=../../ds/obj
LDIR =../../ds/lib

_DEPS = scheduler.h dlist.h pqueue.h task.h uid.h heap.h vector.h watchdog.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = scheduler.o dlist.o pqueue.o task.o uid.o heap.o vector.o watchdog.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(LDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: watchdog_test.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

dog: dog.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
