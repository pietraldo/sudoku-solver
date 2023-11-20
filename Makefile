override CFLAGS=-Wall -Wextra -fanalyzer -g -O0 -fsanitize=address,undefined

ifdef CI
override CFLAGS=-Wall -Wextra -Werror
endif

.PHONY: clean all

all: prog

prog: sudoku.o board_correctness.o array_possibilities.o solving.o stack.o
	gcc $(CFLAGS) -o prog sudoku.o board_correctness.o array_possibilities.o solving.o stack.o

board_correctness.o: src/board_correctness.c headers/board_correctness.h
	gcc -o board_correctness.o -c src/board_correctness.c

array_possibilities.o: src/array_possibilities.c headers/board_correctness.h
	gcc -o array_possibilities.o -c src/array_possibilities.c

solving.o: src/solving.c headers/solving.h 
	gcc -o solving.o -c src/solving.c

stack.o: src/stack.c headers/stack.h 
	gcc -o stack.o -c src/stack.c

sudoku.o: sudoku.c headers/board_correctness.h headers/array_possibilities.h headers/solving.h headers/stack.h
	gcc -o sudoku.o -c sudoku.c

clean:
	rm prog board_correctness.o sudoku.o solving.o array_possibilities.o stack.o