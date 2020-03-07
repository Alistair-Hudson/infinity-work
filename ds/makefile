IDIR = include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)

ODIR= obj
LDIR = lib
TDIR = test

_DEPS = $(wildcard *.h)
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ = $(wildcard *.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

_SRC = $(wildcard *.c)
SRC = $(patsubst %, $(LDIR)/%, $(_SRC))

_TEST = $(wildcard *_test.c)
TEST = $(patsubst %, $(TDIR)/%, $(_TEST))

_OTST = $(wildcard *_test.o)
OTST = $(patsubst %, $(ODIR)/%, $(_OTST))

$(ODIR)/&.o: $(SRC) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ) $(TEST)
	$(CC) -o $@ $< $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
