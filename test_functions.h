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

void test_printMatrix(void);
void test_single_threaded_multiplication(void);

#endif