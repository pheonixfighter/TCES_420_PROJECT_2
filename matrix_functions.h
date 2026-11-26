/**
*   @author Robert Cromer
*   @file matrix_functions.h
*   TCES 420
*   Project 2
*   This file contains the prototypes for all functions related to matrix multiplication
*/

#ifndef matrix_functions
#define matrix_functions
/**
*   The base dimensions for the matrix. Since we are only dealing with square matrices we only need one variable
*/
#define BASE_MATRIX_DIMENSION 2000

typedef struct{
    int rows, columns;
    int *data; 
} Matrix;

/**
*   Creates an empty matrix
*
*
*   @param theRows The number of rows this matrix will have
*   @param theColumns The number of columns this matrix will have
*   @returns a new matrix object 
*/
Matrix createMatrix(int, int);

/**
*   Creates a matrix with random values
*   @param theRows The number of rows this matrix will have
*   @param theColumns The number of columns this matrix will have
*/
Matrix generateMatrix(int, int);

/**
*   Transposes a matrix for faster multiplication by reducing the amount of time the cache is missed
*   @param theMatrix The matrix to be transposed
*/
void transpose(Matrix*);

/**
*   Multiplies two matrices a * b on a single thread
*   @param a The first matrix in the multiplication
*   @param b The second matrix in the multiplication
*/
Matrix multiply(Matrix*, Matrix*);

/**
*   Multiplies the matrix with multiple threads.
*   @param a The first matrix in the multiplication
*   @param b The second matrix in the multiplication.
*   @param threads The number of threads that 
*/
Matrix multiplyThreaded(Matrix, Matrix, int);

/**
*   Prints the values of a matrix
*   @param theMatrix The matrix to be printed
*/
void printMatrix(Matrix);

#endif