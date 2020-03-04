CC=gcc -ansi -pedantic-errors -Wall -Wextra -g
CFLAGS=-I.
DEPS = vsa.h
OBJ =  vsa_test.c vsa.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vsa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
		rm vsa
