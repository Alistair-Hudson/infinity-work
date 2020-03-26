IDIR =../../ds/include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR=../../ds/obj
LDIR =../../ds/lib

_DEPS = hash_table.h dlist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hash_table.o dlist.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/hash_table.o: $(LDIR)/hash_table.c $(LDIR)/dlist.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spell_check: spell_check.c $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
