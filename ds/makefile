IDIR = include
CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Wextra -I$(IDIR)
#ifeq ($(DBG), debug)
#	CFLAGS= -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)
#else ifeq ($(DBG), release)
#	CFLAGS= -ansi -pedantic-errors -Wall -Wextra -O3 -I$(IDIR)
#else ifeq ($(DBG), all)
#	CFLAGS= -ansi -pedantic-errors -Wall -Wextra -O3 -I$(IDIR)
#else ifeq ($(DBG), test)
#	CFLAGS= -ansi -pedantic-errors -Wall -Wextra -O3 -I$(IDIR)
#endif

ODIR= obj
LDIR = lib
BDIR = bin
TDIR = test

_DEPS = $(wildcard *.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(wildcard %.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRC =  *.c
SRC = $(patsubst %,$(LDIR)/%,$(_SRC))

_TEST = %_test.c
TEST = $(patsubst %,$(TDIR)/%,$(_TEST))

$(ODIR)/%.o: $(SRC) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean debug release all test

%: $(TEST) $(OBJ) $(SRC)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o $(BDIR)/* *~ core $(IDIR)/*~

debug: CFLAGS += -g
debug: $(BDIR)/debug/%

$(BDIR)/debug/%: $(TEST) $(OBJ) $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)
