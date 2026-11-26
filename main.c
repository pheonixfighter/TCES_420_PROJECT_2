/**
    @author Robert Cromer
    @file main.c
    @brief This file contains the operational code for this project. It 
    times the matrix multiplication functions to see how long each version of threading works. 
*/

#include "matrix_functions.h"
#include <bits/time.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define MATRIX_SIZE 2000
#define NUM_THREAD_TESTS 5

void custom_thread_timing(void);

int main(void){
    // regular timing operations

    // initializes matrices for multiplication
    Matrix A, B;

    A = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);
    B = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);
    clock_t initial_time, final_time;

    printf("Timing the zero thread case: \n");

    struct timespec t_init, t_final;
    clock_gettime(CLOCK_MONOTONIC, &t_init);
    multiply(&A, &B);
    clock_gettime(CLOCK_MONOTONIC, &t_final);
    


    printf("Time Elapsed: %.4f seconds\n\n", t_final.tv_sec-t_init.tv_sec + (t_final.tv_nsec - t_init.tv_nsec)/1E9);


    printf("Threads\tElapsed time\n");
    
    for (int i = 0; i < NUM_THREAD_TESTS; i++){
        int thread_test_number = exp2((double)i);
        clock_gettime(CLOCK_MONOTONIC, &t_init);
        multiplyThreaded(&A, &B, thread_test_number);
        clock_gettime(CLOCK_MONOTONIC, &t_final);



        printf("%d \t%.4f \t\n", thread_test_number, (t_final.tv_sec-t_init.tv_sec + (t_final.tv_nsec - t_init.tv_nsec)/1E9));
    }

    printf("\n\n");
    custom_thread_timing();
    return 0;
}

void custom_thread_timing(void){
    printf("CUSTOM THREAD TIMING PROGRAM");
    printf("Enter a custom number of threads, and we will multiply two 2000 X 2000 matrices and time the result. \n");

    int threads;
    do{
        printf("Enter number of threads(0 to quit): ");
        scanf("%d", &threads);

        Matrix a = generateMatrix(MATRIX_SIZE, MATRIX_SIZE), b = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);
        if (threads > 0){
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            multiplyThreaded(&a, &b, threads);
            clock_gettime(CLOCK_MONOTONIC, &end);
            printf("This multiplication took %.4f seconds\n", end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec)/1e9);
        }
    }while(threads);

    printf("Goodbye!\n");
}