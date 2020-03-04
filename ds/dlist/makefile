IDIR =../include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR=../obj
LDIR =../lib

_DEPS = dlist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = dlist.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(LDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dlist: $(OBJ) dlist_test.c
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
