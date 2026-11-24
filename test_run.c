/**
*   @author Robert Cromer
*   @file test_run.c
*   @brief This file contains the operational code for the test functions
*/



#include "test_functions.h"

int main(){

    test_printMatrix();
    test_zero_threaded_multiplication();
    test_multi_threaded_multiplication();

    return 0;
}

