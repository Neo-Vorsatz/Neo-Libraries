/*
    Programme to test the matrices library
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

#include <stdio.h>

// Test was done with a maximum matrix size of 4 by 4, and the elements as type `double`
#define MX_SIZE 4
#define MX_ELEMENT double
#include "matrices.c"

void printMatrix(const mxMatrix_t *read) {
    for (unsigned int r=0; r<mxGetNumRows(read); r++) {
        for (unsigned int c=0; c<mxGetNumColumns(read); c++) {
            printf("%f ", mxReadElement(read, r, c));
        }
        printf("\n");
    }
}

int main() {
    mxMatrix_t m1;
    mxZero(&m1);
    mxSetSize(&m1, 3, 3);

    // Testing a zero matrix
    printf("Zero matrix:\n");
    printMatrix(&m1);

    // Designing an arbitrary matrix
    mxElement_t row[3] = {10, 4, 8};
    mxWriteRow_len(&m1, 0, row, 3);
    row[0] = 16;
    row[1] = 9;
    row[2] = 11;
    mxDeleteRow(&m1, 1);
    mxDeleteRow(&m1, 1);
    mxAppendRow(&m1,row);
    row[0] = 2;
    row[1] = 7;
    row[2] = 13;
    mxInsertRow(&m1, 1, row);
    mxSetSize(&m1, 2, mxGetNumColumns(&m1));
    printf("New matrix:\n");
    printMatrix(&m1);

    // Reduced Row Echelon form
    mxMatrix_t reduced;
    mxReducedEchelon(&reduced, &m1);
    printf("Reduced row echelon form:\n");
    printMatrix(&reduced);

    // Creating vectors
    mxMatrix_t vectors;
    mxElement_t elements[4][4] = {{12,-6,0,0},{0,18,0,0},{4,-11,0,0},{0,0,0,0}};
    mxSet(&vectors, 3, 2, elements);
    printf("Vectors:\n");
    printMatrix(&vectors);

    // Applying m1 to the vectors
    mxMatrix_t result;
    mxMultiply(&result, &m1, &vectors);
    printf("Result:\n");
    printMatrix(&result);

    // Solving for the vectors using m1 and the result
    mxMatrix_t solution;
    mxSolveGauss(&solution, &m1, &result);
    printf("Vectors with same solution:\n");
    printMatrix(&solution);

    // Generating another arbitrary matrix
    mxElement_t column[3] = {5, 5, 5};
    for (unsigned int c=0; c<3; c++) {
        mxWriteColumn_len(&m1, c, column, 3); // note that I can edit 3 values of a column, even though the matrix only has 2 rows
    }
    mxSetSize(&m1,3,3);
    mxMatrix_t scaledIdentity;
    mxIdentity(&scaledIdentity, 3);
    mxScale(&scaledIdentity, &scaledIdentity, -2);
    mxAdd(&m1, &m1, &scaledIdentity);
    mxWriteElement(&m1, 0, 2, 3);
    printf("Another new matrix:\n");
    printMatrix(&m1);
    printf("Determinant = %f\n",mxDeterminant(&m1));

    // Generating new results using the same vectors
    mxMultiply(&result, &m1, &vectors);
    printf("New result, using same vectors:\n");
    printMatrix(&result);

    // Solving for the vectors using Gauss
    mxSolveGauss(&solution, &m1, &result);
    printf("Solving for the vectors using Gauss:\n");
    printMatrix(&solution);

    // Solving for the vectors using inverse
    mxMatrix_t solution2;
    mxSolveInverse(&solution2, &m1, &result);
    printf("Solving for the vectors using the inverse:\n");
    printMatrix(&solution2);

    // Testing if the solutions are the same
    if (mxEqual(&solution, &solution2)) {
        printf("The solutions are the same:)\n");
    } else {
        printf("The solutions are different :(\n");
    }

    // Solving for a single element using Cramer's Rule
    mxElement_t element = mxSolveCramer(&m1, &result, 1, 2);
    printf("Solving for the third element of the second vector, using Cramer's Rule:\n");
    printf("%f\n", element);

    // Testing equality
    mxMatrix_t m2;
    mxCopy(&m2, &m1);
    if (mxEqual(&m1, &m2)) {
        printf("Equality successful\n");
    } else {
        printf("Equality unsuccesful\n");
    }
    
    // Finished
    return 0;
}
