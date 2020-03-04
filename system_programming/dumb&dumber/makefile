CC=gcc -ansi -pedantic-errors -Wall -Wextra -g
CFLAGS=-I.
DEPS = vsa.h
OBJ =  dumb.c dumber.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
		rm out
