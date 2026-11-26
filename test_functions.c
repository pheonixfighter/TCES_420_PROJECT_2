/**
    @author Robert Cromer
    @file test_functions.c

    @brief
    This file comtains the implementation code for 
 */


#include "test_functions.h"
#include "matrix_functions.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



void test_printMatrix(){


    Matrix a;
    a.rows = SQUARE_MATRIX_TEST_SIZE;
    a.columns = SQUARE_MATRIX_TEST_SIZE;
    a.data = calloc(SQUARE_MATRIX_TEST_SIZE * SQUARE_MATRIX_TEST_SIZE, sizeof(int)); 

    for (int i = 1; i <= SQUARE_MATRIX_TEST_SIZE * SQUARE_MATRIX_TEST_SIZE; i++){
            a.data[i - 1] = i;
    }

    printMatrix(a);
}

void test_transpose(){
    Matrix a = generateMatrix(SQUARE_MATRIX_TEST_SIZE, SQUARE_MATRIX_TEST_SIZE);
    
    printf("Matrix Transpose test:\n\n");
    printMatrix(a);

    transpose(&a);

    printf("Transposed matrix: \n\n");
    printMatrix(a);
    printf("\n");
    
}

void test_zero_threaded_multiplication(){

    printf("Single threaded multplication test: \n\n");
    // Creates matrices 
    Matrix a, b; 
    a = generateMatrix(SQUARE_MATRIX_TEST_SIZE, SQUARE_MATRIX_TEST_SIZE);

    printf("A:\n\n");
    printMatrix(a);

    // Makes B the identity matrix with the same dimesnions as a
    b = a;
    b.data = calloc(b.rows * b.columns, sizeof(int));
    for(int i = 0; i < SQUARE_MATRIX_TEST_SIZE; i++){
        for(int j = 0; j < SQUARE_MATRIX_TEST_SIZE; j++){
            b.data[i * SQUARE_MATRIX_TEST_SIZE + j] = (i == j);
        }
    }
    printf("B:\n\n");
    printMatrix(b);

    Matrix product = multiply(&a, &b);

    printf("The resulting product:\n\n");
    printMatrix(product);

    if(*(product.data) == *(a.data)){
        printf("Single-threaded multiplication test passed\n");
    } else printf("Single-threaded multplication test failed\n");
    

    free(a.data);
    free(b.data);
    free(product.data);
}

void test_multi_threaded_multiplication(){
    printf("Single threaded multplication test: \n\n\n");
    // Creates matrices 
    Matrix a, b; 
    a = generateMatrix(SQUARE_MATRIX_TEST_SIZE, SQUARE_MATRIX_TEST_SIZE);

    printf("A:\n\n");
    printMatrix(a);

    // Makes B the identity matrix with the same dimesnions as a
    b = a;
    b.data = calloc(b.rows * b.columns, sizeof(int));
    for(int i = 0; i < SQUARE_MATRIX_TEST_SIZE; i++){
        for(int j = 0; j < SQUARE_MATRIX_TEST_SIZE; j++){
            b.data[i * SQUARE_MATRIX_TEST_SIZE + j] = (i == j);
        }
    }
    printf("B:\n\n");
    printMatrix(b);

    Matrix product = multiplyThreaded(&a, &b, 2);

    printf("The resulting product:\n\n");
    printMatrix(product);

    if(*(product.data) == *(a.data)){
        printf("Multi-threaded multiplication test passed\n");
    } else printf("Multi-threaded multplication test failed\n");

    free(a.data);
    free(b.data);
    free(product.data);
}