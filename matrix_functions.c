/**
*   @author Robert Cromer
*   @file matrix_functions.c
*   This file contains the implementation code for the matrix_functions.h code
*/

#include <pthread.h>
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

/**
*   Struct used for threaded matrix multiplication. If a * b is a valid matrix product, then it is 
*   assumed that b is already transposed
*/
typedef struct{
    Matrix* a, *b, *product;
    int lower_row_index, upper_row_index;
} Matrix_Row_Multiplier_t;

/**
    A function that is used to multiply two matrices into a row of the resulting product. 
    Because it's used inside the multiplyThreaded function, it takes a single struct argument that 
    is unloaded into three different arguments.
*/
void *rowMultiply(void *arguments){
    Matrix_Row_Multiplier_t *args = (Matrix_Row_Multiplier_t *) arguments;
    // General loop for the process
    // <= used for termination condition instead of the usual < so that the for loop will always have at least one interation
    for (int current_row_index = args->lower_row_index; current_row_index <= args->upper_row_index; current_row_index++){ 
        int row_offset = current_row_index * args->a->columns; // for memory offset in a

        for (int i = 0; i < args->product->columns; i++){
            int sum = 0;
            int column_offset = i * args->b->columns;
            for(int j = 0; j < args->a->rows; j++){
                sum += args->a->data[row_offset + i] * args->b->data[column_offset * i];
            }
            args->product->data[current_row_index * args->product->columns + i] = sum;
        }
    }
    return NULL;
}

Matrix multiplyThreaded(Matrix a, Matrix b, int threadCount){
    Matrix product;


    pthread_t threads[threadCount];
    int row_range = a.rows / threadCount;
    int max_lower_row_bound = a.rows - row_range - a.rows % threadCount;
    for (int i = 0; i < threadCount; i+= row_range){
        Matrix_Row_Multiplier_t * rowMult_args;
        rowMult_args->a = &a;
        rowMult_args->b = &b;
        rowMult_args->product = &product;
        rowMult_args->lower_row_index = i * row_range;
        rowMult_args->upper_row_index = (i + 1) * row_range - 1;
        pthread_create(&threads[i], NULL, &rowMultiply, &rowMult_args);
    }

    // Adds an extra thread for the purpose of including the modulo threads
    Matrix_Row_Multiplier_t * rowMult_args;
    rowMult_args->a = &a;
    rowMult_args->b = &b;
    rowMult_args->product = &product;
    rowMult_args->lower_row_index =  max_lower_row_bound;
    rowMult_args->upper_row_index = a.rows - 1;
    
    pthread_create(&threads[threadCount - 1], NULL, &rowMultiply, &rowMult_args);

    // waits for all of hte threads to finish
    for(int i = 0; i < threadCount; i++){
        pthread_join(threads[i], NULL);
    }


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