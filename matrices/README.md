# C Matrices
## Overview
This module is for matrix operations in C.<br>
With it, you can create, edit, and do computations with matrices, including but not limited to:
- Matrix multiplication
- Getting the determinant of a square matrix
- Getting the inverse of a square matrix
- Guass elimination into Reduced Row Echelon form
- Solving for vectors, using a transformation and matrix of resulting vectors

## Features
This module was designed with the intention of being embedded-friendly:
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `mx` prefix)

## Quick Start
```c
#include <stdio.h>
#define MX_SIZE 2
#include "matrices.h"

int main() {
  //Create transformation matrix
  matrix transform;
  mxElement_t elements[2][2] = {{1,2},{3,1}};
  mxSet(&transform, 2, 2, elements);

  //Create resultant vector
  matrix result;
  mxSetSize(&result, 2, 1);
  mxElement_t vector[2] = {4,7};
  mxWriteColumn(&result,0,vector);

  //Solve for first element of the (first) input vector
  mxElement_t x = mxSolveCramer(&transform, &result, 0, 0);
  printf("X Coordinate: %f\n", x);

  return 0;
}
```

## Installation & Dependencies
Copy the header and implementation files anywhere where your C-compiler can find it (such as in the same directory as your main file). Then import the module like you would any other module, using `#include`.

This module has the following dependencies:<br>
Standard: `stdbool.h`<br>
This Repository: None

## API Reference
### Macros
#### Matrix Size
You can define a macro called `MX_SIZE` before you `#include` the module, and this will modify the maximum size of the matrices.

#### Matrix Element
You can define a macro called `MX_ELEMENT` before you `#include` the module, and this will modify the data type used in matrices (assigned to the `mxElement_t` type).

### Data Structures
#### Matrix
This is a struct containing a 2-dimensional array of elements (the matrix) as well as the size of the matrix. Create a matrix like you would any other struct:
```c
matrix myMatrix;
```
then `myMatrix` will be a struct representing a matrix.

### Functions
<details>
<summary>Click to view all Writing functions</summary>

`bool mxSet(matrix *write, int rows, int columns, mxElement_t elements[MX_SIZE][MX_SIZE]);`<br>
Sets the given matrix's values to the parameters.<br>
Takes a pointer to the matrix, the number of rows, the number of columns, and a 2D array of the elements.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`void mxCopy(matrix *write, const matrix *read);`<br>
Copies the second matrix's data onto the first.<br>
Takes a pointer to the matrix that is being copied to, and a pointer to the matrix that is being copied from.

`bool mxSetSize(matrix *write, int rows, int columns);`<br>
Sets the number of rows and columns of the given matrix.<br>
Takes a pointer to the matrix, the number of rows, and the number of columns.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxWriteElement(matrix *write, int row, int column, mxElement_t entry);`<br>
Writes an entry into the given row and column of the given matrix.<br>
Takes a pointer to the matrix, the index of the row, the index of the column, and the value of the entry.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxWriteRow_len(matrix *write, int index, const mxElement_t *row, int arrLength);`<br>
Rewrites the content of a row.<br>
Takes a pointer to the matix, the index of the row, an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxWriteRow(matrix *write, int index, const mxElement_t *row);`<br>
Rewrites the content of a row (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, the index of the row, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxWriteColumn_len(matrix *write, int index, const mxElement_t *column, int arrLength);`<br>
Rewrites the content of a column.<br>
Takes a pointer to the matrix, the index of the column, and an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxWriteColumn(matrix *write, int index, const mxElement_t *column);`<br>
Rewrites the content of a column (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, the index of the row, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxInsertRow_len(matrix *write, int index, const mxElement_t *row, int arrLength);`<br>
Inserts a row of entries into the given index.<br>
Takes a pointer to the matix, the index of the row, an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxInsertRow(matrix *write, int index, const mxElement_t *row);`<br>
Inserts a row of entries into the given index (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, the index of the row, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxAppendRow_len(matrix *write, const mxElement_t *row, int arrLength);`<br>
Appends a row of entries to the end of the matrix.<br>
Takes a pointer to the matix, an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxAppendRow(matrix *write, const mxElement_t *row);`<br>
Appends a row of entries to the end of the matrix (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxInsertColumn_len(matrix *write, int index, const mxElement_t *column, int arrLength);`<br>
Inserts a column of entries into the given index.<br>
Takes a pointer to the matix, the index of the column, an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxInsertColumn(matrix *write, int index, const mxElement_t *column);`<br>
Inserts a column of entries into the given index (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, the index of the column, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxAppendColumn_len(matrix *write, const mxElement_t *column, int arrLength);`<br>
Appends a column of entries to the end of the matrix.<br>
Takes a pointer to the matix, an array of entries, and the length of that array.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxAppendColumn(matrix *write, const mxElement_t *column);`<br>
Appends a column of entries to the end of the matrix (assumes the array length is perfectly sized).<br>
Takes a pointer to the matrix, and an array of entries.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxDeleteRow(matrix *write, int index);`<br>
Deletes a row from the matrix.<br>
Takes a pointer to the matrix, and the index of the row.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxDeleteColumn(matrix *write, int index);`<br>
Deletes a column from the matrix.<br>
Takes a pointer to the matrix, and the index of the column.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

</details>

<details>
<summary>Click to view all Reading functions</summary>

`int mxGetNumRows(const matrix *read);`<br>
Takes a pointer to the matrix.<br>
Returns the number of rows.

`int mxGetNumColumns(const matrix *read);`<br>
Takes a pointer to the matrix.<br>
Returns the number of columns.

`mxElement_t mxReadElement(const matrix *read, int row, int column);`<br>
Takes a pointer to the matrix, the index of the row, and the index of the column.<br>
Returns the element in the given row and column, or 0 if the index is out of bounds.

</details>

<details>
<summary>Click to view all Operations functions</summary>

`bool mxEqual(const matrix *read1, const matrix *read2);`<br>
Checks if two matrices are equal.<br>
Takes a pointer to the first matrix, and a pointer to the second matrix.<br>
Returns 1 (true) if the two matrices are equal, otherwise returns 0 (false).

`void mxZero(matrix *write);`<br>
Empties a matrix.<br>
Takes a pointer to the matrix.

`bool mxIdentity(matrix *write, int size);`<br>
Turns a matrix into the identity matrix with a particular size.<br.>
Takes a pointer to the matrix, and the size desired.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxAdd(matrix *write, const matrix *read1, const matrix *read2);`<br>
Adds the second matrix to the first.<br>
Takes a pointer to where the result will be written, a pointer to the first matrix, and a pointer to the second matrix.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`void mxScale(matrix *write, const matrix *read, double factor);`<br>
Scales/Multiplies the given matrix by a factor.<br>
Takes a pointer to where the result will be written, a pointer to the matrix, the value of the factor/scalar.<br>

`bool mxMultiply(matrix *write, const matrix *read1, const matrix *read2);`<br>
Multiplies two matrices.<br>
Takes a pointer to where the result will be written, a pointer to the first matrix (transformation), and a pointer to the second matrix (vector).<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`mxElement_t mxDeterminant(const matrix *read);`<br>
Takes a pointer to the matrix.<br>
Returns the determinant of the given matrix, or 0 if the matrix is not square.

`void mxTranspose(matrix *write, const matrix *read);`<br>
Transposes the given matrix.<br>
Takes a pointer to where the result will be written, and a pointer to the matrix.

`bool mxAdjoint(matrix *write, const matrix *read);`<br>
Gets the adjoint of the given matrix.<br>
Takes a pointer to where the result will be written, and a pointer to the matrix.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`bool mxInverse(matrix *write, const matrix *read);`<br>
Inverts the given matrix.<br>
Takes a pointer to where the result will be written, and a pointer to the matrix.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`mxElement_t mxSolveCramer(const matrix *transform, const matrix *result, int vector, int index);`<br>
Solves for a particular element within a particular vector using Cramer's rule.<br>
Takes a pointer to the transformation matrix, a pointer to the resultant matrix, the index of the vector being solved for, and the index of the element of that vector.<br>
Returns the value of the particular element in the particular vector, or 0 if there's no solution with Cramer's, or 1 if there's infinite solutions.

`bool mxSolveInverse(matrix *write, const matrix *transform, const matrix *result);`<br>
Solves for all vectors using the inverse of the transformation.<br>
Takes a pointer to where the result will be written, a pointer to the transformation matrix, and a pointer to the resultant matrix.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`void mxReducedEchelon_coll(matrix *writeReduce, matrix *writeCollateral, const matrix *readReduce, const matrix *readCollateral);`<br>
Turns a matrix into Reduced Row Echelon Form, and edits 1 additional matrix as collateral.<br>
Takes a pointer to where the result will be written, a pointer to where the collateral result will be written, a pointer to the matrix, and a pointer to the collateral matrix.

`void mxReducedEchelon(matrix *write, const matrix *read);`<br>
Turns a matrix into Reduced Row Echelon Form.<br>
Takes a pointer to where the result will be written, and a pointer to the matrix.

`bool mxSolveGauss(matrix *write, const matrix *transform, const matrix *result);`<br>
Solves for all vectors where possible, using Guass reduction. All vectors that could not be solved for are written as zero-vectors.<br>
Takes a pointer to where the result will be written, a pointer to the transformation matrix, and a pointer to the resultant matrix.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

</details>