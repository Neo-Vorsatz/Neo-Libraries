/*
    Matrices Library, for matrix operations
    Implementation file
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

// IMPORTS ================================

// Internal
#include "matrices.h"

// CONSTANTS ================================

#define __FAIL 0
#define __INF_SOLUTIONS 1

// WRITING ================================

bool mxSet(mxMatrix_t *write, int rows, int columns, mxElement_t elements[MX_SIZE][MX_SIZE]) {
    // If the given rows or columns are too big
    if ((rows > MX_SIZE) || (columns > MX_SIZE)) {return false;}

    // Set the size
    write->rows = rows;
    write->columns = columns;
    // Repeat for each row
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // Repeat for each column
        for (unsigned int c=0; c<MX_SIZE; c++) {
            // Replace the element
            write->elements[r][c] = elements[r][c];
        }
    }

    // Indicate that the process was successful
    return true;
}

void mxCopy(mxMatrix_t *write, const mxMatrix_t *read) {
    // Copy the number of rows and columns
    write->rows = read->rows;
    write->columns = read->columns;
    // For each row
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // For each column
        for (unsigned int c=0; c<MX_SIZE; c++) {
            // Copy the element
            write->elements[r][c] = read->elements[r][c];
        }
    }
}

bool mxSetSize(mxMatrix_t *write, int rows, int columns) {
    // If the given rows or columns are too big
    if ((rows > MX_SIZE) || (columns > MX_SIZE)) {return false;}

    // Setting the size
    write->rows = rows;
    write->columns = columns;

    // Indicate that the process was successful
    return true;
}

bool mxWriteElement(mxMatrix_t *write, int row, int column, mxElement_t entry) {
    // If the index is out of bounds
    if ((row + 1 > MX_SIZE)|| (column + 1 > MX_SIZE)) {return false;}

    // If the row index is beyond the current size
    if (row + 1 > write->rows) {
        // Expand the matrix
        write->rows = row + 1;
    }
    // If the column index is beyond the current size
    if (column + 1 > write->columns) {
        // Expand the matrix
        write->columns = column + 1;
    }
    // Writing the entry
    write->elements[row][column] = entry;

    // Indicate that the process was successful
    return true;
}

bool mxWriteRow_len(mxMatrix_t *write, int index, const mxElement_t *row, int arrLength) {
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is beyond the current size
    if (index + 1 > write->rows) {
        // Expand the matrix
        write->rows = index + 1;
    }
    // Repeat for each element
    for (unsigned int c=0; c<MX_SIZE; c++) {
        // If we've passed the end of the array
        if (c + 1 > arrLength) {
            // Fill the element with 0
            write->elements[index][c] = 0;
        } else {
            // Fill the element with the value from the array
            write->elements[index][c] = row[c];
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxWriteRow(mxMatrix_t *write, int index, const mxElement_t *row) {
    return mxWriteRow_len(write, index, row, write->columns);
}

bool mxWriteColumn_len(mxMatrix_t *write, int index, const mxElement_t *column, int arrLength) {
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is beyond the current size
    if (index + 1 > write->columns) {
        // Expand the matrix
        write->columns = index + 1;
    }
    // Repeat for each element
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // If we've passed the end of the array
        if (r + 1 > arrLength) {
            // Fill the element with 0
            write->elements[r][index] = 0;
        } else {
            // Fill the element with the value from the array
            write->elements[r][index] = column[r];
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxWriteColumn(mxMatrix_t *write, int index, const mxElement_t *column) {
    return mxWriteColumn_len(write, index, column, write->rows);
}

bool mxInsertRow_len(mxMatrix_t *write, int index, const mxElement_t *row, int arrLength) {
    // If the matrix is too large
    if (write->rows == MX_SIZE) {return false;}
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is beyond the current size
    if (index + 1 > write->rows) {
        // Expand the matrix
        write->rows = index + 1;
    } else {
        // Increment the number of rows
        write->rows++;
    }
    // Repeat for each column
    for (unsigned int c=0; c<MX_SIZE; c++) {
        // Repeat for each element below the index, bottom to top
        for (unsigned int r=MX_SIZE; r>index; r--) {
            // Replace the element with the one above it
            write->elements[r][c] = write->elements[r - 1][c];
        }
        // If we've passed the end of the array
        if (c + 1 > arrLength) {
            // Fill the element with 0
            write->elements[index][c] = 0;
        } else {
            // Fill the element with the value from the array
            write->elements[index][c] = row[c];
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxInsertRow(mxMatrix_t *write, int index, const mxElement_t *row) {
    return mxInsertRow_len(write, index, row, write->columns);
}

bool mxAppendRow_len(mxMatrix_t *write, const mxElement_t *row, int arrLength) {
    return mxInsertRow_len(write, write->rows, row, arrLength);
}

bool mxAppendRow(mxMatrix_t *write, const mxElement_t *row) {
    return mxInsertRow_len(write, write->rows, row, write->columns);
}

bool mxInsertColumn_len(mxMatrix_t *write, int index, const mxElement_t *column, int arrLength) {
    // If the matrix is too large
    if (write->columns == MX_SIZE) {return false;}
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is beyond the current size
    if (index + 1 > write->columns) {
        // Expand the matrix
        write->columns = index + 1;
    } else {
        // Increment the number of columns
        write->columns++;
    }
    // Repeat for each column
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // Repeat for each element right of the index, right to left
        for (unsigned int c=MX_SIZE; c>index; c--) {
            // Replace the element with the one left of it
            write->elements[r][c] = write->elements[r][c - 1];
        }
        // If we've passed the end of the array
        if (r + 1 > arrLength) {
            // Fill the element with 0
            write->elements[r][index] = 0;
        } else {
            // Fill the element with the value from the array
            write->elements[r][index] = column[r];
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxInsertColumn(mxMatrix_t *write, int index, const mxElement_t *column) {
    return mxInsertColumn_len(write, index, column, write->rows);
}

bool mxAppendColumn_len(mxMatrix_t *write, const mxElement_t *column, int arrLength) {
    return mxInsertColumn_len(write, write->columns, column, arrLength);
}

bool mxAppendColumn(mxMatrix_t *write, const mxElement_t *column) {
    return mxInsertColumn_len(write, write->columns, column, write->rows);
}

bool mxDeleteRow(mxMatrix_t *write, int index) {
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is within the current size
    if (index < write->rows) {
        // Decrement the number of rows
        write->rows--;
    }
    // Repeat for each column
    for (unsigned int c=0; c<MX_SIZE; c++) {
        // Repeat for each element below (and including) the index, top to bottom
        for (unsigned int r=index; r<MX_SIZE; r++) {
            // Replace the element with the one below it
            write->elements[r][c] = write->elements[r + 1][c];
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxDeleteColumn(mxMatrix_t *write, int index) {
    // If the index is out of bounds
    if (index + 1 > MX_SIZE) {return false;}

    // If the index is within the current size
    if (index < write->columns) {
        // Decrement the number of columns
        write->columns--;
    }
    // Repeat for each row
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // Repeat for each element right of (and including) the index, left to right
        for (unsigned int c=index; c<MX_SIZE; c++) {
            // Replace the element with the one right of it
            write->elements[r][c] = write->elements[r][c + 1];
        }
    }

    // Indicate that the process was successful
    return true;
}

// READING ================================

int mxGetNumRows(const mxMatrix_t *read) {
    return read->rows;
}

int mxGetNumColumns(const mxMatrix_t *read) {
    return read->columns;
}

mxElement_t mxReadElement(const mxMatrix_t *read, int row, int column) {
    // If the index is out of bounds
    if ((read->rows <= row) || (read->columns <= column)) {return __FAIL;}
    // Returning the element
    return read->elements[row][column];
}

// OPERATIONS ================================

bool mxEqual(const mxMatrix_t *read1, const mxMatrix_t *read2) {
    // If the sizes are different
    if (!((read1->rows == read2->rows) && (read1->columns == read2->columns))) {
        // Then the matrices aren't equal
        return false;
    }
    // For each row
    for (unsigned int r=0; r<read1->rows; r++) {
        // For each column
        for (unsigned int c=0; c<read1->columns; c++) {
            // If the entries are not the same
            if (read1->elements[r][c] != read2->elements[r][c]) {
                // Then the matrices aren't equal
                return false;
            }
        }
    }
    // If we've reached this step, the matrices are equal
    return true;
}

void mxZero(mxMatrix_t *write) {
    // Set the sizze to 0
    write->rows = 0;
    write->columns = 0;
    // For each row
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // For each column
        for (unsigned int c=0; c<MX_SIZE; c++) {
            // Replace the entry with 0
            write->elements[r][c] = 0;
        }
    }
}

bool mxIdentity(mxMatrix_t *write, int size) {
    // If the size is too large
    if (size > MX_SIZE) {return false;}

    // Set the size
    write->rows = size;
    write->columns = size;
    // For each row
    for (unsigned int r=0; r<size; r++) {
        // For each column
        for (unsigned int c=0; c<size; c++) {
            // If this entry is on the diagonal
            if (r == c) {
                // Replace the entry with 1
                write->elements[r][c] = 1;
            } else {
                // Replace the entry with 0
                write->elements[r][c] = 0;
            }
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxAdd(mxMatrix_t *write, const mxMatrix_t *read1, const mxMatrix_t *read2) {
    // If the matrices can't be added
    if (!( (read1->rows == read2->rows) && (read1->columns == read2->columns) )) {return false;}

    // Temporarily storing the Read matrices
    mxMatrix_t m1;
    mxCopy(&m1, read1);
    mxMatrix_t m2;
    mxCopy(&m2, read2);

    // Setting the size
    write->rows = m1.rows;
    write->columns = m1.columns;
    // For each row
    for (unsigned int r=0; r<m1.rows; r++) {
        // For each column
        for (unsigned int c=0; c<m1.columns; c++) {
            // Write the sum of the two entries
            write->elements[r][c] = m1.elements[r][c] + m2.elements[r][c];
        }
    }

    // Indicate that the process was successful
    return true;
}

void mxScale(mxMatrix_t *write, const mxMatrix_t *read, double factor) {
    // Setting the size
    write->rows = read->rows;
    write->columns = read->columns;
    // For each row
    for (unsigned int r=0; r<read->rows; r++) {
        // For each column
        for (unsigned int c=0; c<read->columns; c++) {
            write->elements[r][c] = read->elements[r][c] * factor;
        }
    }
}

bool mxMultiply(mxMatrix_t *write, const mxMatrix_t *read1, const mxMatrix_t *read2) {
    // If the matrices can't be multiplied
    if (read1->columns != read2->rows) {return false;}

    // Temporarily storing the Read matrices
    mxMatrix_t m1;
    mxCopy(&m1, read1);
    mxMatrix_t m2;
    mxCopy(&m2, read2);

    // Setting the size
    write->rows = m1.rows;
    write->columns = m2.columns;
    // For each row
    for (unsigned int r=0; r<write->rows; r++) {
        // For each column
        for (unsigned int c=0; c<write->columns; c++) {
            // Set the cumulative sum to 0
            mxElement_t sum = 0;
            // For each term
            for (unsigned int i=0; i<m1.columns; i++) {
                // Increase the sum by the product
                sum += m1.elements[r][i] * m2.elements[i][c];
            }
            // Set the entry as the sum
            write->elements[r][c] = sum;
        }
    }

    // Indicate that the process was successful
    return true;
}

mxElement_t mxDeterminant(const mxMatrix_t *read) {
    // If it's not a square matrix
    if (read->rows != read->columns) {return __FAIL;}
    // If there is only 1 element, return that element
    if (read->rows == 1) {return read->elements[0][0];}

    // Set the determinant to 0 initially
    mxElement_t determinant = 0;
    // Set the sign to positive
    signed int sign = 1;
    // Get memory for the submatrix
    mxMatrix_t submatrix;

    // For each element in the first row
    for (unsigned int c=0; c<read->columns; c++) {
        // Copy the contents to the submatrix
        mxCopy(&submatrix, read);
        // Delete the first row of the submatrix
        mxDeleteRow(&submatrix, 0);
        // Delete the corresponding column of the submatrix
        mxDeleteColumn(&submatrix, c);

        // Add the element multiplied by the cofactor to the determinant
        determinant += (read->elements[0][c]) * sign * mxDeterminant(&submatrix);
        // Change the sign for the next cofactor
        sign *= -1;
    }

    // Return the value of the determinant
    return determinant;
}

void mxTranspose(mxMatrix_t *write, const mxMatrix_t *read) {
    // Temporarily storing the Read matrix
    mxMatrix_t m;
    mxCopy(&m, read);

    // Swap the number of rows and columns
    write->rows = m.columns;
    write->columns = m.rows;
    // For each row
    for (unsigned int r=0; r<MX_SIZE; r++) {
        // For each column
        for (unsigned int c=0; c<MX_SIZE; c++) {
            // Copy the element into the transposed-position
            write->elements[c][r] = m.elements[r][c];
        }
    }
}

bool mxAdjoint(mxMatrix_t *write, const mxMatrix_t *read) {
    // If it's not a square matrix
    if (read->rows!=read->columns) {return false;}

    // Temporarily storing the Read matrix
    mxMatrix_t m;
    mxCopy(&m, read);

    // Setting the size
    write->rows = m.rows;
    write->columns = m.columns;

    // Get memory for the submatrix
    mxMatrix_t submatrix;
    // For each row
    for (unsigned int r=0; r<m.rows; r++) {
        // For each column
        for (unsigned int c=0; c<m.columns; c++) {
            // Copy the contents to the submatrix
            mxCopy(&submatrix, &m);
            // Delete the corresponding row of the submatrix
            mxDeleteRow(&submatrix, r);
            // Delete the corresponding column of the submatrix
            mxDeleteColumn(&submatrix, c);

            // Set the transposed element of the adjoint matrix
            write->elements[c][r] = (((r + c) % 2)? -1:1) * mxDeterminant(&submatrix);
        }
    }

    // Indicate that the process was successful
    return true;
}

bool mxInverse(mxMatrix_t *write, const mxMatrix_t *read) {
    // If it's not a square matrix
    if (read->rows != read->columns) {return false;}
    // Getting the determinant
    mxElement_t det = mxDeterminant(read);
    // If the determinant is zero, the inverse doesn't exist
    if (det == 0) {return false;}

    // Set Write to the adjoint
    mxAdjoint(write, read);
    // Scale Write by dividing by the determinant
    mxScale(write, write, 1 / det);

    // Indicate that the process was successful
    return true;
}

mxElement_t mxSolveCramer(const mxMatrix_t *transform, const mxMatrix_t *result, int vector, int index) {
    // If it's not a square matrix
    if (transform->rows != transform->columns) {return __FAIL;}
    // If the vector number is out of bounds
    if (vector >= result->columns) {return __FAIL;}
    // If the index is out of bounds
    if (index >= result->rows) {return __FAIL;}
    // If the result is impossible from the transform
    if (transform->rows != result->rows) {return __FAIL;}

    // Get the determinant of the transform
    mxElement_t det = mxDeterminant(transform);
    // Copy the transform
    mxMatrix_t m;
    mxCopy(&m, transform);
    // For each index in the resulting vector
    for (unsigned int i=0; i<result->rows; i++) {
        // Copy this entry to the new matrix
        m.elements[i][index] = result->elements[i][vector];
    }
    // Get the determinant of the new matrix
    mxElement_t newDet = mxDeterminant(&m);

    // If there are infinite solutions
    if ((det == 0) && (newDet == 0)) {return __INF_SOLUTIONS;}
    // If there are no solutions
    if ((det == 0) && (newDet != 0)) {return __FAIL;}
    // Otherwise, there is one solution, using Cramer's Rule
    return (newDet / det);
}

bool mxSolveInverse(mxMatrix_t *write, const mxMatrix_t *transform, const mxMatrix_t *result) {
    // Save Write as the inverse of the Transform
    if (!mxInverse(write, transform)) {
        // If this process fails
        return false;
    }
    // Save Write as the multiplication of the inverse and the result
    mxMultiply(write, write, result);

    // Indicate that the process was successful
    return true;
}

void mxReducedEchelon_coll(mxMatrix_t *writeReduce, mxMatrix_t *writeCollateral, const mxMatrix_t *readReduce, const mxMatrix_t *readCollateral) {
    // Copy the matrices
    mxCopy(writeReduce, readReduce);
    mxCopy(writeCollateral, readCollateral);

    /*
        When a column with no non-zero pivot is found, it introduces a free-variable.
        The row of the next pivot will be the same row there should've been a pivot,
        so the row for any pivot we're looking for is columnNum minus numOfFreeVariables
    */
    int numFreeVar = 0;
    // For each index along the diagonal
    for (unsigned int i=0; (i < writeReduce->columns) && (i - numFreeVar < writeReduce->rows); i++) {
        // The starting row to consider for a pivot is on the diagonal, minus the free variables found
        int r = i - numFreeVar;
        // Search for a non-zero pivot
        while ((writeReduce->elements[r][i] == 0) && (r + 1 < writeReduce->rows)) {r++;}

        // If a non-zero was not found
        if (writeReduce->elements[r][i] == 0) {
            // Then we've found a free variable
            numFreeVar++;
        } else {
            /*
                Swap the pivot row and the row with a non-zero pivot
            */
            // For each column after the completed columns, in the matrix we're reducing
            for (unsigned int c=i; c<writeReduce->columns; c++) {
                // Temporarily store the value from the main row
                mxElement_t temp = writeReduce->elements[i - numFreeVar][c];
                // Replace the value in the main row
                writeReduce->elements[i - numFreeVar][c] = writeReduce->elements[r][c];
                // Replace the value in the row that was found
                writeReduce->elements[r][c] = temp;
            }
            // For each column in the collateral matrix
            for (unsigned int c=0; c<writeCollateral->columns; c++) {
                // Temporarily store the value from the main row
                mxElement_t temp = writeCollateral->elements[i - numFreeVar][c];
                // Replace the value in the main row
                writeCollateral->elements[i - numFreeVar][c] = writeCollateral->elements[r][c];
                // Replace the value in the row that was found
                writeCollateral->elements[r][c] = temp;
            }

            /*
                Reduce this column
            */
            // For each row
            for (unsigned int r=0; r<writeReduce->rows; r++) {
                // If this row isn't the pivot
                if (r != i - numFreeVar) {
                    // Set the scalar multiple needed
                    double scalar = writeReduce->elements[r][i] / writeReduce->elements[i - numFreeVar][i];
                    /*
                        Perform the row operation
                    */
                    // For each column after the completed columns, in the matrix we're reducing
                    for (unsigned int c=i; c<writeReduce->columns; c++) {
                        // Decrease each element in the row by the scalar multiple of the pivot row
                        writeReduce->elements[r][c] -= scalar * writeReduce->elements[i - numFreeVar][c];
                    }
                    // For each column in the collateral matrix
                    for (unsigned int c=0; c<writeCollateral->columns; c++) {
                        // Decrease each element in the row by the scalar multiple of the pivot row
                        writeCollateral->elements[r][c] -= scalar * writeCollateral->elements[i - numFreeVar][c];
                    }
                }
            }
        }
    }
}

void mxReducedEchelon(mxMatrix_t *write, const mxMatrix_t *read) {
    // Creating a zero matrix
    mxMatrix_t zero;
    mxZero(&zero);

    // Turning the matrix into Reduced Row Echelon Form
    mxReducedEchelon_coll(write, &zero, read, &zero);
}

bool mxSolveGauss(mxMatrix_t *write, const mxMatrix_t *transform, const mxMatrix_t *result) {
    // If the result is impossible from the transform
    if (transform->rows != result->rows) {return false;}

    // Set the size
    write->rows = transform->columns;
    write->columns = result->columns;

    // Creating new matrices to do row operations on
    mxMatrix_t transform0;
    mxMatrix_t result0;

    // Gauss Reduction
    mxReducedEchelon_coll(&transform0, &result0, transform, result);

    /*
        To solve for the vectors, we're going to make all free variables equal 0,
        and only pivots will have a non-zero value
    */
    // Whether a variable has been solved for or not
    bool solved[transform0.columns];
    // Note that none of the variables have been solved for
    for (unsigned int i=0; i<transform0.columns; i++) {solved[i] = 0;}
    // For each row in the transformation
    for (unsigned int r=0; r<transform0.rows; r++) {
        // Start with the first column
        int c = 0;
        // Search for the pivot, left to right
        while ((transform0.elements[r][c] == 0) && (c + 1 < transform0.columns)) {c++;}
        // For each output vector
        for (unsigned int v=0; v<result0.columns; v++) {
            // If no pivot was found
            if (transform0.elements[r][c] == 0) {
                // If the result is non-zero
                if (result0.elements[r][v] != 0) {
                    // Then there is no possible solution
                    return false;
                }
            } else {
                // Solve for the pivot-variable
                write->elements[c][v] = result0.elements[r][v] / transform0.elements[r][c];
                // Note that the variable has been solved for
                solved[c] = 1;
            }
        }
    }
    // For each variable
    for (unsigned int i=0; i<transform0.columns; i++) {
        // If this variable was not solved for
        if (!solved[i]) {
            // For each vector
            for (unsigned int v=0; v<result0.columns; v++) {
                // Set the solution to 0
                write->elements[i][v] = 0;
            }
        }
    }

    // Indicate that the process was successful
    return true;
}

// ================================

#undef __FAIL
#undef __INF_SOLUTIONS
