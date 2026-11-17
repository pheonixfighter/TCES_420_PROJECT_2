/**
    @author Robert Cromer
    @file main.c

    @brief 
    This file contains the operational code for this project. It runs tests to ensure correctness and 
    times the matrix multiplication functions if the testing variable is defined during compile time
*/

#include "matrix_functions.h"
#include "test_functions.h"
#include <stdio.h>


int main(void){
    #ifdef TEST_MODE
        test_printMatrix();
        test_single_threaded_multiplication();
        test_multi_threaded_multiplication();
    #endif

    
    return 0;
}