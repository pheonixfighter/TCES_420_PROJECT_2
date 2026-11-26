all: TIMING_PROGRAM test_run

TIMING_PROGRAM: main.o matrix_functions.o
	gcc main.o matrix_functions.o -o TIMING_PROGRAM

test_run: test_run.o matrix_functions.o test_functions.o
	gcc test_run.o test_functions.o matrix_functions.o  -o test_run

test_run.o: main.c matrix_functions.h 
	gcc -c test_run.c 

test_functions.o: test_functions.c
	gcc -c test_functions.c 

matrix_functions.o: matrix_functions.c
	gcc -c matrix_functions.c 

main.o: main.c matrix_functions.h
	gcc -c main.c matrix_functions.h
