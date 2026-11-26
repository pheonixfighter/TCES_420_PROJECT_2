/**
    @author Robert Cromer
    @file main.c
    @brief This file contains the operational code for this project. It 
    times the matrix multiplication functions to see how long each version of threading works. 
*/

#include "matrix_functions.h"
#include <stdio.h>
#include <time.h>

#define MATRIX_SIZE 2000
#define NUM_THREAD_TESTS 5

int main(void){
    // regular timing operations

    // initializes matrices for multiplication
    Matrix A, B;

    A = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);
    B = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);
    clock_t initial_time, final_time;

    printf("Timing the zero thread case: \n");

    initial_time = clock();

    multiply(&A, &B);

    final_time = clock();

    printf("Time Elapsed: %ld seconds", final_time - initial_time);

    int threads[] = {1, 2, 4, 8, 16};

    printf("Threads \t Start time \t End time \t Elapsed time\n");
    
    for (int i = 0; i < NUM_THREAD_TESTS; i++){
        initial_time = clock();

        multiplyThreaded(A, B, threads[i]);

        final_time = clock();

        printf("%d \t %ld \t %ld \t %ld \t", threads[i], initial_time, final_time, final_time - initial_time);
    }

    return 0;
}