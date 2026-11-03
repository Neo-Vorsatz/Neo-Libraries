// Complex Numbers Library, for complex number operations
// Header file
// by Ambesiwe Sonka and Neo Vorsatz
// Last updated: 25 December 2025

//Header guard
#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

//Includes
#include <stdbool.h>

//C++ compatibility
#ifdef __cplusplus
  extern "C" {
#endif

/* TYPE DEFINITIONS ================================*/

//Structure for complex numbers
typedef struct{
  union {
    double real; //real component
    double mod; //modulus or magnitude
  };
  union {
    double imag; //imaginary component
    double arg; //argument or phase
  };
  bool rect_form; //whether the complex number is in rectangular form or not (otherwise in polar form)
} complex;

/*================================*/
/* CREATING ================================*/

/**
 * @param real The real part of the complex number
 * @param imag The imaginary part of the complex number
 * 
 * @return A complex number in rectangular form
 */
complex cnRect(double real, double imag);

/**
 * @param mag The magnitude of the complex number
 * @param phase The phase of the complex number
 * 
 * @return A complex number in polar form
 */
complex cnPolar(double mag, double phase);

/**
 * @param real The real part of the complex number
 * 
 * @return A complex number in rectangular form, with only a real component
 */
complex cnR(double real);

/**
 * @param imag The imaginary part of the complex number
 * 
 * @return A complex number in rectangular form, with only an imaginary component
 */
complex cnI(double imag);

/**
 * @param arg The argument of the complex number
 * 
 * @return A complex number in polar form, with magnitude 1
 */
complex cnA(double arg);

/*================================*/
/* READING ================================*/

/**
 * @param complexNum A complex number
 * 
 * @return The real component of a complex number
 */
double cnReal(const complex *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The imaginary component of a complex number
 */
double cnImag(const complex *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The magnitude of a complex number
 */
double cnMag(const complex *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The argument of a complex number
 */
double cnArg(const complex *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return Whether or not a complex number is in rectangular form
 */
bool cnIsRect(const complex *complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return Whether or not a complex number is in polar form
 */
bool cnIsPolar(const complex *complexNum);

/*================================*/
/* UPDATING ================================*/

/**
 * @brief Sets the real component of a complex number
 * 
 * @param complexNum A complex number
 * @param real The new real component of the complex number
 */
void cnSetReal(complex *complexNum, double real);

/**
 * @brief Sets the imaginary component of a complex number
 * 
 * @param complexNum A complex number
 * @param imag The new imaginary component of the complex number
 */
void cnSetImag(complex *complexNum, double imag);

/**
 * @brief Sets the magnitude of a complex number
 * 
 * @param complexNum A complex number
 * @param mag The new magnitude of the complex number
 */
void cnSetMag(complex *complexNum, double mag);

/**
 * @brief Sets the argument of a complex number
 * 
 * @param complexNum A complex number
 * @param arg The new argument of the complex number
 */
void cnSetArg(complex *complexNum, double arg);

/**
 * @brief Sets whether or not a complex number is in rectangular form
 * 
 * Warning: This changes the effective-value of the complex number, not just the form
 * 
 * @param complexNum A complex number
 * @param rect Whether or not the complex number is set to rectangular form, else polar form
 */
void cnSetForm(complex *complexNum, bool rect);

/*================================*/
/* OPERATIONS ================================*/

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * @param tolerance The tolerance to use when comparing floating points
 * 
 * @return Whether or not two complex numbers are equal
 */
bool cnEqual(complex complexNum1, complex complexNum2, double tolerance);

/**
 * @param complexNum A complex number
 * 
 * @return The complex number in rectangular form
 */
complex cnRectForm(complex complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return The complex number in polar form
 */
complex cnPolarForm(complex complexNum);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The sum of two complex numbers
 */
complex cnAdd(complex complexNum1, complex complexNum2);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The difference of two complex numbers
 */
complex cnSub(complex complexNum1, complex complexNum2);

/**
 * @param complexNum A complex number
 * @param scalar A real scalar
 * 
 * @return The complex number multiplied by a scalar
 */
complex cnScale(complex complexNum, double scalar);

/**
 * @param complexNum1 A complex number
 * @param complexNum2 Another complex number
 * 
 * @return The product of two complex numbers
 */
complex cnMultiply(complex complexNum1, complex complexNum2);

/**
 * @brief Calculates the quotient of two complex numbers
 * 
 * @param quotient A pointer to where the result will be written
 * @param numerator A complex number
 * @param denominator Another complex number
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool cnDivide(complex *quotient, complex numerator, complex denominator);

/**
 * @param base A complex number
 * @param power The power to raise the complex number to
 * 
 * @return The complex number raised to a real power
 */
complex cnPow(complex base, double power);

/**
 * @param base A complex number
 * @param power The power to raise the complex number to
 * 
 * @return The complex number raised to a complex power
 */
complex cnPowComplex(complex base, complex power);

/**
 * @param complexNum A complex number
 * 
 * @return The conjugate of the complex number
 */
complex cnConjugate(complex complexNum);

/**
 * @param complexNum A complex number
 * 
 * @return e raised to the power of a complex number (Euler's formula)
 */
complex cnExp(complex complexNum);

/**
 * @brief Calculates the natural logarithm of a complex number
 * 
 * @param result A pointer to where the result will be written
 * @param complexNum A complex number
 * 
 * @return 1 (true) if the process was successful, otherwise returns 0 (false)
 */
bool cnLog(complex *result, complex complexNum);

/**
 * @param angle An angle
 * 
 * @return The principle argument of an angle
 */
double cnPrincipleArg(double angle);

/*================================*/

#ifdef __cplusplus
  }
#endif

#endif