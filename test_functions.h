/**
    @author Robert Cromer
    @file test_functions.h

    @brief
    This file defines the test functions that will be used to verify correctness in main.c
*/

#include "matrix_functions.h"

#ifndef test_functions
#define test_functions

#define SQUARE_MATRIX_TEST_SIZE 3 // testing 3X3 matrices for tests
#define SQUARE_MATRIX_TEST_ELEMENT_NUMBER (SQUARE_MATRIX_TEST_SIZE * SQUARE_MATRIX_TEST_SIZE)

void test_printMatrix(void);
void test_zero_threaded_multiplication(void);
void test_multi_threaded_multiplication(void);

#endif