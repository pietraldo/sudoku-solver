override CFLAGS=-Wall -Wextra -fanalyzer -g -O0 -fsanitize=address,undefined

ifdef CI
override CFLAGS=-Wall -Wextra -Werror
endif

.PHONY: clean all

all: prog

prog: sudoku.o board_correctness.o array_possibilities.o solving.o stack.o
	gcc $(CFLAGS) -o prog sudoku.o board_correctness.o array_possibilities.o solving.o stack.o

board_correctness.o: board_correctness.c board_correctness.h
	gcc -o board_correctness.o -c board_correctness.c

array_possibilities.o: array_possibilities.c board_correctness.h
	gcc -o array_possibilities.o -c array_possibilities.c

solving.o: solving.c solving.h 
	gcc -o solving.o -c solving.c

stack.o: stack.c stack.h 
	gcc -o stack.o -c stack.c

sudoku.o: sudoku.c board_correctness.h array_possibilities.h solving.h stack.h
	gcc -o sudoku.o -c sudoku.c

clean:
	rm prog board_correctness.o sudoku.o solving.o array_possibilities.o stack.o