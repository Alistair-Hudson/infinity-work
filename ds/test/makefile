IDIR =../include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -I$(IDIR)

ODIR=../obj
LDIR =../lib

_DEPS = $(wildcard *.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(wildcard %.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRC =  *.c
SRC = $(patsubst %,$(LDIR)/%,$(_SRC))

mains = *.c makefile

$(ODIR)/%.o: $(SRC) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: %

.PHONY: clean
.PHONY: debug
.PHONY: all

%: %_test.c $(OBJ) $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ #$(filter-out $(mains), *)

debug: $(CFLAGS) += -g -DDEBUG
debug: *


