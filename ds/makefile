IDIR = include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR= obj
LDIR = lib
TDIR = test

_DEPS = $(wildcard *.h)
DEPS = $(patsubst %, $(IDIR)/%.h, $(_DEPS))

_OBJ = $(wildcard *.o)
OBJ = $(patsubst %, $(ODIR)/%.o, $(_OBJ))

_SRC = $(wildcard *.c)
SRC = $(patsubst %, $(LDIR)/%.c, $(_SRC))

_TEST = $(wildcard *_test.c)
TEST = $(patsubst %, $(TDIR)/%_test.c, $(_TEST))

_OTST = $(wildcard *_test.o)
OTST = $(patsubst %, $(ODIR)/%_test.o, $(_OTST))

all: $(OTST)
	$(CC) -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(LDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%_test.o: $(TDIR)/%_test.c $(OBJ)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
