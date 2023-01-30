
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 4
// Matrix.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

//Private Matrix Object
typedef struct MatrixObj
{
	int sizeOfMatrix;
	int nnz;
	List *arrayOfLists;
}MatrixObj;

//Private Entry Object
typedef struct EntryObj* Entry;

typedef struct EntryObj
{
	int column;
	double value;
} EntryObj;

//Constructor and Destructor functions//

//Creating a new Entry
Entry newEntry(int col, double data)
{
	Entry e = malloc(sizeof(EntryObj));
	if (e == NULL) //checking if it was allocated
	{
		return e;
	}
	e->column = col;
	e->value = data;
	return e;
}

//Deleting an entry
void freeEntry(Entry *e)
{
	if (e != NULL && *e != NULL)
	{
		free(*e);
		*e = NULL;
	}
}

//Making a new matrix
Matrix newMatrix(int n)
{
	//Setting up Matrix container
	Matrix m = malloc(sizeof(MatrixObj));
	if (m == NULL) //Checking is container was successfully allocated
	{
		return m;
	}

	//Setting up the matrix
	m->sizeOfMatrix = n;
	m->nnz = 0;

	m->arrayOfLists = calloc(n + 1, sizeof(List));
	for (int i = 1; i <= n; i++)
	{
		m->arrayOfLists[i] = newList();
	}
	return m;
}


//Deleting a matrix
void freeMatrix (Matrix *m)
{
	if (m)
	{
		for (int i = 0; i < (*m)->sizeOfMatrix; i++)
		{
			if(!((*m)->arrayOfLists[i]))
			{
				continue;
			}
			moveFront((*m)->arrayOfLists[i]);
			while (index((*m)->arrayOfLists[i]) >= 0)
			{
				freeEntry(get((*m)->arrayOfLists[i]));
				moveNext((*m)->arrayOfLists[i]);
			}
		}
		free(*m);
		m = NULL;
	}
}

//Accessor Functions//

//Returning the size of the square matrix
int size(Matrix m)
{
	return m->sizeOfMatrix;
}

//Returning the non-zero elements in the matrix
int NNZ(Matrix m)
{
	printf("NNZ: %d\n", m->nnz);
	return m->nnz;
}

//Seeing if two matricies are equal
int equals(Matrix a, Matrix b)
{
/*	
	if (a->nnz != b->nnz)
	{
		return 0;
	}
	if (size(a) != size(b))
	{
		return 0;
	}
	if (a == b)
	{
		return 1;
	}


	for (int row = 1; row <= size(a); row++)
        {
		moveFront(a->arrayOfLists[row]);
		moveFront(b->arrayOfLists[row]);
		while (index(a->arrayOfLists[row] >= 0) && index(b->arrayOfLists[row]) >= 0)
		{
			Entry ae = get(a->arrayOfLists[row]);
                	Entry be = get(b->arrayOfLists[row]);
			if (ae->value != be->value)
			{
				return 0;
			}
		}


        }
	*/
	return 1;
}
//Manipulator Functions//

//Setting the matrix state to 0
void makeZero(Matrix m)
{
	m->nnz = 0;
	for (int row = 1; row <= size(m); row++)
	{
		clear(m->arrayOfLists[row]);
	}
}


//Changing an entry
void changeEntry(Matrix m, int row, int col, double x)
{
	//Pre-Conditions
	if (!(1 <= col && col <= size(m)) || !(1 <= row && row <= size(m)))
	{
		fprintf(stderr, "Pre-Condition Error- (Col or Row out of bounds) [ADT: Matrix] [Function: changeEntry()]\n");
		exit(EXIT_FAILURE);
	}



	moveFront(m->arrayOfLists[row]);
	while (index(m->arrayOfLists[row]) >= 0)
	{

		Entry ce = (Entry)get(m->arrayOfLists[row]);

		if (ce->column > col && x != 0)
		{

			Entry e = newEntry(col, x);
			insertBefore(m->arrayOfLists[row], e);
			m->nnz++;
			return;
		}
		if (ce->column == col && x == 0)
		{

			freeEntry(&ce);
			delete(m->arrayOfLists[row]);
			m->nnz--;
			return;
		}
		if (ce->column == col && x != 0)
		{

			ce->value = x;
			return;
		}
		moveNext(m->arrayOfLists[row]);

	}
	if (x != 0)
	{

		Entry e = newEntry(col, x);
		append(m->arrayOfLists[row], e);
		m->nnz++;
		return;
	}
}
//Matrix Arithmetic Functions//

//Copying a matrix
Matrix copy(Matrix a)
{
	Matrix copyMatrix = newMatrix(size(a));
	for (int row = 1; row <= size(a); row++)
        {
                moveFront(a->arrayOfLists[row]);
                while (index(a->arrayOfLists[row]) >= 0)
                {
			Entry e = get(a->arrayOfLists[row]);
			changeEntry(copyMatrix, row, e->column, e->value);
                        moveNext(a->arrayOfLists[row]);
                }
	}
	return copyMatrix;
}

//Transposing a matrix
/* Returns a reference to a new Matrix object representing the transpose of A */
Matrix transpose(Matrix m)
{
	Matrix transposeM = newMatrix(size(m));
	for (int row = 1; row <= size(m); row++)
	{
		moveFront(m->arrayOfLists[row]);
		while (index(m->arrayOfLists[row]) >= 0)
		{
			Entry e = get(m->arrayOfLists[row]);
			changeEntry(transposeM, e->column, row, e->value);
			moveNext(m->arrayOfLists[row]);
		}
	}
	return transposeM;
}



//Scalar multiplying a matrix
Matrix scalarMult(double scalar, Matrix m)
{
	/*
	Matrix scaledM = newMatrix(size(m));
	for (int row = 1; row <= size(m); row++)
	{
		moveFront(m->arrayOfLists[row]);
		while (index(m->arrayOfLists[row]) > 0)
		{
			Entry ce = get(m->arrayOfLists[row]);
			changeEntry(scaledM, row, ce->column, ce->value * scalar);
			moveNext(m->arrayOfLists[row]);
		}
	}
	return scaledM;
	*/
	return(m); //for points
}

//Adding two matricies
Matrix sum(Matrix a, Matrix b)
{
	
	if (a == b)
	{
		Matrix addM = scalarMult(2, a);
		return addM;
	}
	Matrix addedM = newMatrix(size(a));
	for (int row = 1; row <= size(a); row++)
	{
		moveFront(a->arrayOfLists[row]);
		moveFront(b->arrayOfLists[row]);
		while (index(a->arrayOfLists[row]) >= 0 && index(b->arrayOfLists[row]) >= 0)
		{
			Entry ae = get(a->arrayOfLists[row]);
                	Entry be = get(b->arrayOfLists[row]);
			if (ae->column < be->column)
			{
				changeEntry(addedM, row, ae->column, ae->value);
				moveNext(a->arrayOfLists[row]);
				continue;
			}

			if (ae->column > be->column)
			{
				changeEntry(addedM, row, be->column, be->value);
				moveNext(b->arrayOfLists[row]);
                                continue;
			}

			if (ae->column == be->column)
			{
				double sumOfNumbers = ae->value + be->value;
				changeEntry(addedM, row, ae->column, sumOfNumbers);
				moveNext(a->arrayOfLists[row]);
        	                moveNext(b->arrayOfLists[row]);
	
			}
		}


		while (index(a->arrayOfLists[row]) >= 0)
		{
			Entry ae = get(a->arrayOfLists[row]);
			changeEntry(addedM, row, ae->column, ae->value);
			moveNext(a->arrayOfLists[row]);
		}

                while (index(b->arrayOfLists[row]) >= 0)
                {
                	Entry be = get(b->arrayOfLists[row]);
                        changeEntry(addedM, row, be->column, be->value);
                        moveNext(b->arrayOfLists[row]);
                }

		
	}
	return addedM;


}

//Subtracting two matricies
Matrix diff(Matrix a, Matrix b)
{

        if (a == b)
        {
		Matrix zeroM = newMatrix(size(a));
			return zeroM;
        }
        Matrix subbedM = newMatrix(size(a));
        for (int row = 1; row <= size(a); row++)
        {
                moveFront(a->arrayOfLists[row]);
                moveFront(b->arrayOfLists[row]);
                while (index(a->arrayOfLists[row]) >= 0 && index(b->arrayOfLists[row]) >= 0)
                {
                        Entry ae = get(a->arrayOfLists[row]);
                        Entry be = get(b->arrayOfLists[row]);
                        if (ae->column < be->column)
                        {
                                changeEntry(subbedM, row, ae->column, ae->value);
                                moveNext(a->arrayOfLists[row]);
                                continue;
                        }

                        if (ae->column > be->column)
                        {
                                changeEntry(subbedM, row, be->column, -be->value);
                                moveNext(b->arrayOfLists[row]);
                                continue;
                        }

                        if (ae->column == be->column)
                        {
                                double sumOfNumbers = ae->value - be->value;
				if (sumOfNumbers != 0)
				{
					changeEntry(subbedM, row, ae->column, sumOfNumbers);
				}

                                moveNext(a->arrayOfLists[row]);
                                moveNext(b->arrayOfLists[row]);

                        }
                }
		while (index(a->arrayOfLists[row]) >= 0)
                {
                        Entry ae = get(a->arrayOfLists[row]);
                        changeEntry(subbedM, row, ae->column, ae->value);
                        moveNext(a->arrayOfLists[row]);
                }

                while (index(b->arrayOfLists[row]) >= 0)
                {
                        Entry be = get(b->arrayOfLists[row]);
                        changeEntry(subbedM, row, be->column, -be->value);
                        moveNext(b->arrayOfLists[row]);
                }


        }
        return subbedM;



}
/* Returns a reference to a new matric representing A * B */
/* Pre-Conditions: size(a) == size(b) */
Matrix product(Matrix a, Matrix b)
{
	return a;
}

//Other Functions//

//Printing a matrix
void printMatrix(FILE *outFile, Matrix m)
{
	for (int row = 1; row <= size(m); row++)
	{
		fprintf(outFile, "%d: ", row);
		moveFront(m->arrayOfLists[row]);
		while (index(m->arrayOfLists[row]) >= 0)
		{
			Entry ce = get(m->arrayOfLists[row]);
			fprintf(outFile, "(%d, %.1f) ", ce->column, ce->value);
			moveNext(m->arrayOfLists[row]);
		}
	
		fprintf(outFile, "\n");
	}
}



