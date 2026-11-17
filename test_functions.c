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

   for (int i = 1; i < SQUARE_MATRIX_TEST_SIZE * SQUARE_MATRIX_TEST_SIZE; i++){
        a.data[i - 1] = i;
   }

   printMatrix(a);
}

void test_single_threaded_multiplication(){
    // Creates matrices 
    Matrix a, b; 
    a = generateMatrix(SQUARE_MATRIX_TEST_SIZE, SQUARE_MATRIX_TEST_SIZE);

}