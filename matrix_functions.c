/**
*   @author Robert Cromer
*   @file matrix_functions.c
*   This file contains the implementation code for the matrix_functions.h code
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matrix_functions.h"



Matrix createMatrix(int theRows, int theColumns){
    Matrix newMatrix;
    newMatrix.columns = theColumns;
    newMatrix.rows = theRows;

    newMatrix.data = calloc(theRows * theColumns, sizeof(int));
    if (newMatrix.data == NULL) {
        printf("Error with initializing matrix pointer. ");
        exit(1);
    }
    return newMatrix;
}

void transpose(Matrix *theMatrix){
    Matrix newMatrix;

    newMatrix.rows = theMatrix->columns;
    newMatrix.columns = theMatrix->rows;
    int index_byte_increment = sizeof(int);
    newMatrix.data = calloc(newMatrix.rows * newMatrix.columns, index_byte_increment);

    // Does the transpose for the matrix/
    for (int i = 0; i < theMatrix->rows; i++){ // row traversal
        for(int j = 0; j < theMatrix->columns; j++){
           newMatrix.data[i * j + j] = theMatrix->data[i * j + i];
        }
    }

    free(theMatrix);
    *theMatrix = newMatrix;
}
