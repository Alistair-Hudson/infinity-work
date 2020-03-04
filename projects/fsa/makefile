CC=gcc
CFLAGS=-I.
DEPS = fsa.h
OBJ =  fsa_test.c fsa.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fsa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
		rm fsa
