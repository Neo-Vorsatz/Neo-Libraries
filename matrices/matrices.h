// Matrices Library, for matrix operations
// Header file
// by Neo Vorsatz
// Last updated: 27 December 2025

//Header guard
#ifndef MATRICES_H
#define MATRICES_H

//Includes
#include <stdbool.h>

//C++ compatibility
#ifdef __cplusplus
  extern "C" {
#endif

/* EDIT WITH MACROS ================================*/

#ifndef MX_SIZE
  #define MX_SIZE 4 //This value determines the maximum size of the matrices
#endif

#ifdef MX_ELEMENT
  typedef MX_ELEMENT mxElement_t;
#else
  typedef double mxElement_t; //This type determines the numerical data type of the matrices
#endif

/*================================*/
/* TYPE DEFINITIONS ================================*/

//Structure for matrices
typedef struct {
  unsigned int rows;
  unsigned int columns;
  mxElement_t elements[MX_SIZE][MX_SIZE];
} matrix;

/*================================*/
/* WRITING ================================*/

/**
 * @brief Sets the given matrix's values to the parameters
 * 
 * @param write A pointer to the matrix
 * @param rows The number of rows
 * @param columns The number of columns
 * @param elements A 2D array of the elements
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxSet(matrix *write, int rows, int columns, mxElement_t elements[MX_SIZE][MX_SIZE]);

/**
 * @brief Copies the second matrix's data onto the first
 * 
 * @param write A pointer to the matrix that is being copied to
 * @param read A pointer to the matrix that is being copied from
 */
void mxCopy(matrix *write, const matrix *read);

/**
 * @brief Sets the number of rows and columns of the given matrix
 * 
 * @param write A pointer to the matrix
 * @param rows The number of rows
 * @param columns The number of columns
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxSetSize(matrix *write, int rows, int columns);

/**
 * @brief Writes an entry into the given row and column of the given matrix
 * 
 * @param write A pointer to the matrix
 * @param row The index of the row
 * @param column The index of the column
 * @param entry The value of the entry
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxWriteElement(matrix *write, int row, int column, mxElement_t entry);

/**
 * @brief Rewrites the content of a row
 * 
 * @param write A pointer to the matrix
 * @param index The index of the row
 * @param row An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxWriteRow_len(matrix *write, int index, const mxElement_t *row, int arrLength);

/**
 * @brief Rewrites the content of a row (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param index The index of the row
 * @param row An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxWriteRow(matrix *write, int index, const mxElement_t *row);

/**
 * @brief Rewrites the content of a column
 * 
 * @param write A pointer to the matrix
 * @param index The index of the column
 * @param column An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxWriteColumn_len(matrix *write, int index, const mxElement_t *column, int arrLength);

/**
 * @brief Rewrites the content of a column (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param index The index of the column
 * @param column An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxWriteColumn(matrix *write, int index, const mxElement_t *column);

/**
 * @brief Inserts a row of entries into the given index
 * 
 * @param write A pointer to the matrix
 * @param index The index of the row
 * @param row An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxInsertRow_len(matrix *write, int index, const mxElement_t *row, int arrLength);

/**
 * @brief Inserts a row of entries into the given index (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param index The index of the row
 * @param row An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxInsertRow(matrix *write, int index, const mxElement_t *row);

/**
 * @brief Appends a row of entries to the end of the matrix
 * 
 * @param write A pointer to the matrix
 * @param row An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAppendRow_len(matrix *write, const mxElement_t *row, int arrLength);

/**
 * @brief Appends a row of entries to the end of the matrix (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param row An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAppendRow(matrix *write, const mxElement_t *row);

/**
 * @brief Inserts a column of entries into the given index
 * 
 * @param write A pointer to the matrix
 * @param index The index of the column
 * @param column An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxInsertColumn_len(matrix *write, int index, const mxElement_t *column, int arrLength);

/**
 * @brief Inserts a column of entries into the given index (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param index The index of the column
 * @param column An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxInsertColumn(matrix *write, int index, const mxElement_t *column);

/**
 * @brief Appends a column of entries to the end of the matrix
 * 
 * @param write A pointer to the matrix
 * @param column An array of entries
 * @param arrLength The length of that array
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAppendColumn_len(matrix *write, const mxElement_t *column, int arrLength);

/**
 * @brief Appends a column of entries to the end of the matrix (assumes the array length is perfectly sized)
 * 
 * @param write A pointer to the matrix
 * @param column An array of entries
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAppendColumn(matrix *write, const mxElement_t *column);

/**
 * @brief Deletes a row from the matrix
 * 
 * @param write A pointer to the matrix
 * @param index The index of the row
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxDeleteRow(matrix *write, int index);

/**
 * @brief Deletes a column from the matrix
 * 
 * @param write A pointer to the matrix
 * @param index The index of the column
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxDeleteColumn(matrix *write, int index);

/*================================*/
/* READING ================================*/

/**
 * @param read A pointer to the matrix
 * 
 * @return The number of rows
 */
int mxGetNumRows(const matrix *read);

/**
 * @param read A pointer to the matrix
 * 
 * @return The number of columns
 */
int mxGetNumColumns(const matrix *read);

/**
 * @param read A pointer to the matrix
 * @param row The index of the row
 * @param column The index of the column
 * 
 * @return The value of the element,
 * or 0 if the index is out of bounds
 */
mxElement_t mxReadElement(const matrix *read, int row, int column);

/*================================*/
/* OPERATIONS ================================*/

/**
 * @brief Checks if two matrices are equal
 * 
 * @param read1 A pointer to the first matrix
 * @param read2 A pointer to the second matrix
 * 
 * @return 1 (true) if the two matrices are equal, otherwise returns 0 (false)
 */
bool mxEqual(const matrix *read1, const matrix *read2);

/**
 * @brief Empties a matrix
 * 
 * @param write A pointer to the matrix
 */
void mxZero(matrix *write);

/**
 * @brief Turns a matrix into the identity matrix with a particular size
 * 
 * @param write A pointer to the matrix
 * @param size The size desired
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxIdentity(matrix *write, int size);

/**
 * @brief Adds the second matrix to the first
 * 
 * @param write A pointer to where the result will be written
 * @param read1 A pointer to the first matrix
 * @param read2 A pointer to the second matrix
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAdd(matrix *write, const matrix *read1, const matrix *read2);

/**
 * @brief Scales/Multiplies the given matrix by a factor
 * 
 * @param write A pointer to where the result will be written
 * @param read A pointer to the matrix
 * @param factor The value of the factor/scalar
 */
void mxScale(matrix *write, const matrix *read, double factor);

/**
 * @brief Multiplies two matrices
 * 
 * @param write A pointer to where the result will be written
 * @param read1 A pointer to the first matrix (transformation)
 * @param read2 A pointer to the second matrix (vector)
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxMultiply(matrix *write, const matrix *read1, const matrix *read2);

/**
 * @param read A pointer to the matrix
 * 
 * @return The determinant of the given matrix,
 * or 0 if the matrix is not square
 */
mxElement_t mxDeterminant(const matrix *read);

/**
 * @brief Transposes the given matrix
 * 
 * @param write A pointer to where the result will be written
 * @param read A pointer to the matrix
 */
void mxTranspose(matrix *write, const matrix *read);

/**
 * @brief Gets the adjoint of the given matrix
 * 
 * @param write A pointer to where the result will be written
 * @param read A pointer to the matrix
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxAdjoint(matrix *write, const matrix *read);

/**
 * @brief Inverts the given matrix
 * 
 * @param write A pointer to where the result will be written
 * @param read A pointer to the matrix
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxInverse(matrix *write, const matrix *read);

/**
 * @brief Solves for a particular element within a particular vector using Cramer's rule
 * 
 * @param transform A pointer to the transformation matrix
 * @param result A pointer to the resultant matrix
 * @param vector The index of the vector being solved for
 * @param index The index of the element of that vector
 * 
 * @return The value of the particular element in the particular vector,
 * or 0 if there's no solution with Cramer's,
 * or 1 if there's infinite solutions
 */
mxElement_t mxSolveCramer(const matrix *transform, const matrix *result, int vector, int index);

/**
 * @brief Solves for all vectors using the inverse of the transformation
 * 
 * @param write A pointer to where the result will be written
 * @param transform A pointer to the transformation matrix
 * @param result A pointer to the resultant matrix
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxSolveInverse(matrix *write, const matrix *transform, const matrix *result);

/**
 * @brief Turns a matrix into Reduced Row Echelon Form, and edits 1 additional matrix as collateral
 * 
 * @param writeReduce A pointer to where the result will be written
 * @param writeCollateral A pointer to where the collateral result will be written
 * @param readReduce A pointer to the matrix
 * @param readCollateral A pointer to the collateral matrix
 */
void mxReducedEchelon_coll(matrix *writeReduce, matrix *writeCollateral, const matrix *readReduce, const matrix *readCollateral);

/**
 * @brief Turns a matrix into Reduced Row Echelon Form
 * 
 * @param write A pointer to where the result will be written
 * @param read A pointer to the matrix
 */
void mxReducedEchelon(matrix *write, const matrix *read);

/**
 * @brief Solves for all vectors where possible, using Guass reduction
 * 
 * All vectors that could not be solved for are written as zero-vectors
 * 
 * @param write A pointer to where the result will be written
 * @param transform A pointer to the transformation matrix
 * @param result A pointer to the resultant matrix
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool mxSolveGauss(matrix *write, const matrix *transform, const matrix *result);

/*================================*/

#ifdef __cplusplus
  }
#endif

#endif