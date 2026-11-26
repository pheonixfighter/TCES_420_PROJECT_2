all: TIMING_PROGRAM test_run

TIMING_PROGRAM: main.o matrix_functions.o
	gcc  -g main.o matrix_functions.o -o TIMING_PROGRAM

test_run: test_run.o matrix_functions.o test_functions.o
	gcc -g test_run.o test_functions.o matrix_functions.o  -o test_run

test_run.o: main.c matrix_functions.h 
	gcc -c -g test_run.c 

test_functions.o: test_functions.c
	gcc -c -g test_functions.c 

matrix_functions.o: matrix_functions.c
	gcc -c -g matrix_functions.c 

main.o: main.c matrix_functions.h
	gcc -c -g main.c matrix_functions.h
