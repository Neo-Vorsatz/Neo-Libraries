/*
    Complex Numbers Library, for complex number operations
    Header file
    Authors: Ambesiwe Sonka and Neo Vorsatz
    Last updated: 4 November 2026
*/

// Header guard
#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

// IMPORTS ================================

//Includes
#include <stdbool.h>

// C++ COMPATIBILITY ================================

#ifdef __cplusplus
	extern "C" {
#endif

// TYPES ================================

// Structure for complex numbers
typedef struct{
	union {
		double real; // real component
		double mod; // modulus or magnitude
	};
	union {
		double imag; // imaginary component
		double arg; // argument or phase
	};
	bool rectForm; // whether the complex number is in rectangular form or not (otherwise in polar form)
} cnComplex_t;

// CREATING ================================

/**
 * @param real The real part of the complex number
 * @param imag The imaginary part of the complex number
 * 
 * @return A complex number in rectangular form
 */
cnComplex_t cnRect(double real, double imag);

/**
 * @param mag The magnitude of the complex number
 * @param phase The phase of the complex number
 * 
 * @return A complex number in polar form
 */
cnComplex_t cnPolar(double mag, double phase);

/**
 * @param real The real part of the complex number
 * 
 * @return A complex number in rectangular form, with only a real component
 */
cnComplex_t cnR(double real);

/**
 * @param imag The imaginary part of the complex number
 * 
 * @return A complex number in rectangular form, with only an imaginary component
 */
cnComplex_t cnI(double imag);

/**
 * @param arg The argument of the complex number
 * 
 * @return A complex number in polar form, with magnitude 1
 */
cnComplex_t cnA(double arg);

// READING ================================

/**
 * @param complexNum A complex number
 * 
 * @return The real component of a complex number
 */
double cnReal(const cnComplex_t *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The imaginary component of a complex number
 */
double cnImag(const cnComplex_t *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The magnitude of a complex number
 */
double cnMag(const cnComplex_t *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The argument of a complex number
 */
double cnArg(const cnComplex_t *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return Whether or not a complex number is in rectangular form
 */
bool cnIsRect(const cnComplex_t *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return Whether or not a complex number is in polar form
 */
bool cnIsPolar(const cnComplex_t *complexNum);

// UPDATING ================================

/**
 * @brief Sets the real component of a complex number
 * 
 * @param complexNum A complex number
 * @param real The new real component of the complex number
 */
void cnSetReal(cnComplex_t *complexNum, double real);

/**
 * @brief Sets the imaginary component of a complex number
 * 
 * @param complexNum A complex number
 * @param imag The new imaginary component of the complex number
 */
void cnSetImag(cnComplex_t *complexNum, double imag);

/**
 * @brief Sets the magnitude of a complex number
 * 
 * @param complexNum A complex number
 * @param mag The new magnitude of the complex number
 */
void cnSetMag(cnComplex_t *complexNum, double mag);

/**
 * @brief Sets the argument of a complex number
 * 
 * @param complexNum A complex number
 * @param arg The new argument of the complex number
 */
void cnSetArg(cnComplex_t *complexNum, double arg);

/**
 * @brief Sets whether or not a complex number is in rectangular form
 * 
 * Warning: This changes the effective-value of the complex number, not just the form
 * 
 * @param complexNum A complex number
 * @param rect Whether or not the complex number is set to rectangular form, else polar form
 */
void cnSetForm(cnComplex_t *complexNum, bool rect);

// OPERATIONS ================================

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * @param tolerance The tolerance to use when comparing floating points
 * 
 * @return Whether or not two complex numbers are equal
 */
bool cnEqual(cnComplex_t complexNum1, cnComplex_t complexNum2, double tolerance);

/**
 * @param complexNum A complex number
 * 
 * @return The complex number in rectangular form
 */
cnComplex_t cnRectForm(cnComplex_t complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The complex number in polar form
 */
cnComplex_t cnPolarForm(cnComplex_t complexNum);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The sum of two complex numbers
 */
cnComplex_t cnAdd(cnComplex_t complexNum1, cnComplex_t complexNum2);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The difference of two complex numbers
 */
cnComplex_t cnSub(cnComplex_t complexNum1, cnComplex_t complexNum2);

/**
 * @param complexNum A complex number
 * @param scalar A real scalar
 * 
 * @return The complex number multiplied by a scalar
 */
cnComplex_t cnScale(cnComplex_t complexNum, double scalar);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The product of two complex numbers
 */
cnComplex_t cnMultiply(cnComplex_t complexNum1, cnComplex_t complexNum2);

/**
 * @brief Calculates the quotient of two complex numbers
 * 
 * @param quotient A pointer to where the result will be written
 * @param numerator A complex number
 * @param denominator Another complex number
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool cnDivide(cnComplex_t *quotient, cnComplex_t numerator, cnComplex_t denominator);

/**
 * @param base A complex number
 * @param power The power to raise the complex number to
 * 
 * @return The complex number raised to a real power
 */
cnComplex_t cnPow(cnComplex_t base, double power);

/**
 * @param base A complex number
 * @param power The power to raise the complex number to
 * 
 * @return The complex number raised to a complex power
 */
cnComplex_t cnPowComplex(cnComplex_t base, cnComplex_t power);

/**
 * @param complexNum A complex number
 * 
 * @return The conjugate of the complex number
 */
cnComplex_t cnConjugate(cnComplex_t complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return e raised to the power of a complex number (Euler's formula)
 */
cnComplex_t cnExp(cnComplex_t complexNum);

/**
 * @brief Calculates the natural logarithm of a complex number
 * 
 * @param result A pointer to where the result will be written
 * @param complexNum A complex number
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool cnLog(cnComplex_t *result, cnComplex_t complexNum);

/**
 * @param angle An angle
 * 
 * @return The principle argument of an angle
 */
double cnPrincipleArg(double angle);

// ================================

#ifdef __cplusplus
	}
#endif

#endif
