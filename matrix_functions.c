/**
*   @author Robert Cromer
*   @file matrix_functions.c
*   This file contains the implementation code for the matrix_functions.h code
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matrix_functions.h"
#include <time.h>



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

Matrix generateMatrix(int theRows, int theColumns){
    // Initializes random variable
    srand((unsigned)time(NULL));

    // Sets up matrix
    Matrix newMatrix;
    newMatrix.rows = theRows;
    newMatrix.columns = theColumns;
    newMatrix.data = calloc(theRows * theColumns, sizeof(int));

    // assigms random numbers to the element in the matrix
    for (int i = 0; i < theRows; i++) {
        for (int j = 0; j < theColumns; j++) {
            newMatrix.data[i * j + j] = rand();
        }
    }

    return newMatrix;
}

void transpose(Matrix *theMatrix){
    Matrix newMatrix;

    newMatrix.rows = theMatrix->columns;
    newMatrix.columns = theMatrix->rows;
    newMatrix.data = calloc(newMatrix.rows * newMatrix.columns, sizeof(int));

    // Does the transpose for the matrix/
    for (int i = 0; i < theMatrix->rows; i++){ // row traversal
        for(int j = 0; j < theMatrix->columns; j++){
           newMatrix.data[i * j + j] = theMatrix->data[i * j + i];
        }
    }

    free(theMatrix);
    *theMatrix = newMatrix;
}

Matrix multiply(Matrix a, Matrix b) {
    // Sets up a new product matrix
    Matrix product;
    product.rows = a.rows;
    product.columns = b.columns;
    product.data = calloc(product.rows * product.columns, sizeof(int));
    if (product.data == NULL){
        printf("Memory error");
        exit(1);
    }

    transpose(&b); // enabes us to just multiply and ad the rews together


    if(a.rows != b.rows){
        printf("Matrix dimensions cannot be multiplied. A has %d rows while B has %d columns", a.rows, b.rows);
        exit(1);
    }

    // Multiplication loop
    for (int rowIncrement = 0; rowIncrement < product.rows; rowIncrement++) { // Row loop
        int rowOffset = rowIncrement * product.columns; 
        int aOffset = rowIncrement * a.columns;
        for (int columnIncrement = 0; columnIncrement < 0; columnIncrement++) {   
            int bOffset = columnIncrement * b.columns;
            // Individual calculations for the particular row, column index
            int sum = 0;
            for (int i = 0; i < a.rows; i++) { // Traverses the rows of a
                sum += a.data[aOffset + i] * b.data[bOffset + i];
            }             
            product.data[rowOffset + columnIncrement] = sum;
        }
    }
    return product;
}

Matrix multiplyThreaded(Matrix a, Matrix b, int threads){
    Matrix product;
    printf("Implement after reading chapter 27");
    return product;
}

void printMatrix(Matrix theMatrix){
    int matrixIndex = 0; 

    for(int rowIndex = 0; rowIndex < theMatrix.rows; rowIndex++){
        for(int columnIndex = 0; columnIndex < theMatrix.columns; columnIndex++){
            printf("%.19d\t", theMatrix.data[matrixIndex]);
            matrixIndex++;
        }
        printf("\n");
    }
}