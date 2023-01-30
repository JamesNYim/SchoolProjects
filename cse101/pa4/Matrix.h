
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 4
// Matrix.h
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#pragma once

#include <stdio.h>
#include <stdlib.h>

//Struct Definitions
typedef struct MatrixObj* Matrix;

//Constructor and Destructor functions//

//Making a new matrix
/* Creates a new reference to a new n x n Matrix object in the zero state */
Matrix newMatrix(int n);

//Deleting a matrix
/* Frees the heap memory associated with the pointer. It then sets the pointer to NULL */
void freeMatrix (Matrix *m);

//Accessor Functions//

//Returning the size of the square matrix
int size(Matrix m);

//Returning the non-zero elements in the matrix
int NNZ(Matrix m);

//Seeing if two matricies are equal
/* Returns true (1) if matricies A and B are equal, false (0) otherwise. */
int equals(Matrix a, Matrix b);

//Manipulator Functions//

//Setting the matrix state to 0
void makeZero(Matrix m);

//Changing an entry
/* Changed the ith row, jth column of m to the value x */
/* Pre-Conditions: 1 <= i <= size(m), 1 <= j <= size(m) */
void changeEntry(Matrix m, int i, int j, double x);

//Matrix Arithmetic Functions//

//Copying a matrix
/* Returns a new reference to a new Matrix object having the same entries as A */
Matrix copy(Matrix a);

//Transposing a matrix
/* Returns a reference to a new Matrix object representing the transpose of A */
Matrix transpose(Matrix a);

//Scalar multiplying a matrix
/* Returns a reference to a new matrix object represneting scalar * a */
Matrix scalarMult(double scalar, Matrix a);

//Adding two matricies
/* Returns a reference to a new matrix representing A + B */
Matrix sum(Matrix a, Matrix b);

//Subtracting two matricies
/* Returns a regerence to a new matrix representing A - B */
Matrix diff(Matrix a, Matrix b);

//Multiplying two matricies
/* Returns a reference to a new matric representing A * B */
/* Pre-Conditions: size(a) == size(b) */
Matrix product(Matrix a, Matrix b);

//Other Functions//

//Printing a matrix
/* Prints a string representation of matrix m to the filestream out. Zero rows are not printed. Each non-zero row is represented as one line consisting of the row number, followed by a colon, a space, then a space seperated list of pairs "(cols, val)" giving the column numbers and non-zero values in that row. The double val will be rounded to 1 decimal point. */
void printMatrix(FILE *outFile, Matrix m);



