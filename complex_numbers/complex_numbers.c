/*
    Complex Numbers Library, for complex number operations
    Implementation file
    Authors: Ambesiwe Sonka and Neo Vorsatz
    Last updated: 4 November 2026
*/

// IMPORTS ================================

// External
#include <math.h>

// Internal
#include "complex_numbers.h"

// EDITABLE MACROS ================================

#ifndef PI
    #define PI 3.14159265358979323846 // same value in math.h, but defined locally
    #define __PI_WAS_UNDEFINED_BY_USER // note that PI was not defined by the user
#endif

// CREATING ================================

cnComplex_t cnRect(double real, double imag) {
    cnComplex_t complexNum = {real, imag, true};
    return complexNum;
}

cnComplex_t cnPolar(double mag, double arg) {
    if (mag<0) { // if the magnitude is negative
        mag = -mag; // correct the magnitude
        arg += PI; // rotate the phase
    }
    cnComplex_t complexNum = {mag, cnPrincipleArg(arg), false};
    return complexNum;
}

cnComplex_t cnR(double real) {
    cnComplex_t complexNum = {real, 0.0, true};
    return complexNum;
}

cnComplex_t cnI(double imag) {
    cnComplex_t complexNum = {0.0, imag, true};
    return complexNum;
}

cnComplex_t cnA(double arg) {
    cnComplex_t complexNum = {1.0, cnPrincipleArg(arg), false};
    return complexNum;
}

// READING ================================

double cnReal(const cnComplex_t *complexNum) {
    // If the complex number is in rectangular form
    if (complexNum->rectForm) {
        return complexNum->real;
    }
    return complexNum->mod * cos(complexNum->arg);
}

double cnImag(const cnComplex_t *complexNum) {
    // If the complex number is in rectangular form
    if (complexNum->rectForm) {
        return complexNum->imag;
    }
    return complexNum->mod * sin(complexNum->arg);
}

double cnMag(const cnComplex_t *complexNum){
    // If the complex number is in rectangular form
    if (complexNum->rectForm) {
        // Use Pythagorean formula
        return sqrt((complexNum->real * complexNum->real) + (complexNum->imag * complexNum->imag));
    }
    return complexNum->mod;
}

double cnArg(const cnComplex_t *complexNum){
    // If the complex number is in rectangular form
    if (complexNum->rectForm) {
        return cnPrincipleArg(atan2(complexNum->imag, complexNum->real));
    }
    return complexNum->arg;
}

bool cnIsRect(const cnComplex_t *complexNum){
    return complexNum->rectForm;
}

bool cnIsPolar(const cnComplex_t *complexNum){
    return !complexNum->rectForm;
}

// UPDATING ================================

void cnSetReal(cnComplex_t *complexNum, double real){
    bool rectForm = complexNum->rectForm; // save the current form
    *complexNum = cnRectForm(*complexNum); // convert to rectangular form
    complexNum->real = real;
    if (!rectForm) {
        *complexNum = cnPolarForm(*complexNum); // convert back to polar form
    }
}

void cnSetImag(cnComplex_t *complexNum, double imag){
    bool rectForm = complexNum->rectForm; // save the current form
    *complexNum = cnRectForm(*complexNum); // convert to rectangular form
    complexNum->imag = imag;
    if (!rectForm) {
        *complexNum = cnPolarForm(*complexNum); // convert back to polar form
    }
}

void cnSetMag(cnComplex_t *complexNum, double mag){
    // Converting to polar form
    bool rectForm = complexNum->rectForm; // save the current form
    *complexNum = cnPolarForm(*complexNum); // convert to polar form

    // Assigning new magnitude
    if (mag<0) { // if the magnitude is negative
        complexNum->mod = -mag;
    } else { // the magnitude is positive
        complexNum->mod = mag;
    }

    // Converting back to rectangular form if necessary
    if (rectForm) {
        *complexNum = cnRectForm(*complexNum); // convert back to polar form
    }
}

void cnSetArg(cnComplex_t *complexNum, double arg){
    bool rectForm = complexNum->rectForm; // save the current form
    *complexNum = cnPolarForm(*complexNum); // convert to polar form
    complexNum->arg = cnPrincipleArg(arg);
    if (rectForm) {
        *complexNum = cnRectForm(*complexNum); // convert back to polar form
    }
}

void cnSetForm(cnComplex_t *complexNum, bool rect){
    complexNum->rectForm = rect;
}

// OPERATIONS ================================

bool cnEqual(cnComplex_t complexNum1, cnComplex_t complexNum2, double tolerance) {
    if (complexNum1.rectForm) { // do the check in rectangular form
        // Convert the second complex number to rectangular form
        complexNum2 = cnRectForm(complexNum2);

        // Check if the real components are different
        if (fabs(complexNum1.real - complexNum2.real) > tolerance) {
            return false;
        }
        // Check if the imaginary components are different
        if (fabs(complexNum1.imag - complexNum2.imag) > tolerance) {
            return false;
        }

    } else { // do the check in polar form
        // Convert the second complex number to polar form
        complexNum2 = cnPolarForm(complexNum2);

        // Check if the magnitudes are different
        if (fabs(complexNum1.mod - complexNum2.mod) > tolerance) {
            return false;
        }
        // Check if the arguments are different and the magnitudes are not zero
        if (fabs(complexNum1.arg - complexNum2.arg) > tolerance && fabs(complexNum1.mod) > tolerance) {
            return false;
        }
    }

    // All checks are passed
    return true;
}

cnComplex_t cnRectForm(cnComplex_t complexNum) {
    // If the complex number is already in rectangular form
    if (complexNum.rectForm) {
        // Return the original complex number
        return complexNum;
    }
    return cnRect(cnReal(&complexNum), cnImag(&complexNum));
}

cnComplex_t cnPolarForm(cnComplex_t complexNum) {
    // If the complex number is in rectangular form
    if (complexNum.rectForm) {
        return cnPolar(cnMag(&complexNum), cnArg(&complexNum));
    }
    // Return the original complex number
    return complexNum;
}

cnComplex_t cnAdd(cnComplex_t complexNum1, cnComplex_t complexNum2) {
    // Use the form of the first complex number
    bool rectForm = complexNum1.rectForm;

    // Convert complex numbers to rectangular form
    complexNum1 = cnRectForm(complexNum1);
    complexNum2 = cnRectForm(complexNum2);

    // Add the real parts
    double real = complexNum1.real + complexNum2.real;
    // Add the imaginary parts
    double imag = complexNum1.imag + complexNum2.imag;
    // Create the resulting complex number
    cnComplex_t result = cnRect(real, imag);
    if (!rectForm) {
        result = cnPolarForm(result); // convert the result to polar form
    }

    // Return the result
    return result;
}

cnComplex_t cnSub(cnComplex_t complexNum1, cnComplex_t complexNum2) {
    complexNum2 = cnScale(complexNum2, -1); // negate the second complex number
    return cnAdd(complexNum1, complexNum2);
}

cnComplex_t cnScale(cnComplex_t complexNum, double scalar) {
    if (complexNum.rectForm) {
        complexNum.real *= scalar; // scale the real component
        complexNum.imag *= scalar; // scale the imaginary component
    } else {
        complexNum.mod *= scalar; // scale the magnitude
    }
    return complexNum;
}

cnComplex_t cnMultiply(cnComplex_t complexNum1, cnComplex_t complexNum2) {
    if (complexNum1.rectForm) { // do calculations in rectangular form
        // Convert the second complex number to rectangular form
        complexNum2 = cnRectForm(complexNum2);

        // Calculate the real component
        double real = (complexNum1.real * complexNum2.real) - (complexNum1.imag * complexNum2.imag);
        // Calculate the imaginary component
        double imag = (complexNum1.real * complexNum2.imag) + (complexNum1.imag * complexNum2.real);

        // Return the resulting complex number
        return cnRect(real, imag);

    } else { // do calculations in polar form
        // Convert the second complex number to polar form
        complexNum2 = cnPolarForm(complexNum2);

        // Calculate the magnitude
        double mag = complexNum1.mod * complexNum2.mod;
        // Calculate the argument
        double arg = cnPrincipleArg(complexNum1.arg + complexNum2.arg);

        // Return the resulting complex number
        return cnPolar(mag, arg);
    }
}

bool cnDivide(cnComplex_t *quotient, cnComplex_t numerator, cnComplex_t denominator) {
    // Save the form of the first complex number
    bool rectForm = numerator.rectForm;
    // Convert complex numbers to polar form
    numerator = cnPolarForm(numerator);
    denominator = cnPolarForm(denominator);

    // Check if denominator is zero
    if (denominator.mod == 0.0) {
        return false;
    }

    // Divide magnitudes
    double mag = numerator.mod / denominator.mod;
    // Subtract arguments
    double arg = cnPrincipleArg(numerator.arg - denominator.arg);
    // Create the resulting complex number
    cnComplex_t result = cnPolar(mag, arg);
    if (rectForm) {
        result = cnRectForm(result); // convert the result to rectangular form
    }
    // Assign the result to the quotient
    *quotient = result;

    // Indicate success
    return true;
}

cnComplex_t cnPow(cnComplex_t base, double power) {
    // Save the current form
    bool rectForm = base.rectForm;
    // Convert to polar form
    base = cnPolarForm(base);

    // Calculate the magnitude
    double mag = pow(base.mod, power);
    // Calculate the argument
    double arg = cnPrincipleArg(base.arg * power);
    // Create the resulting complex number
    cnComplex_t result = cnPolar(mag, arg);
    if (rectForm) {
        result = cnRectForm(result); // convert the result to rectangular form
    }

    // Return the resulting complex number
    return result;
}

cnComplex_t cnPowComplex(cnComplex_t base, cnComplex_t power) {
    // Convert power to rectangular form
    power = cnRectForm(power);

    // Calculate the first factor (from the real power)
    cnComplex_t factor1 = cnPow(base, power.real);
    // Calculate the second factor (from the imaginary power)
    cnComplex_t temp; // temporary variable for intermediate steps
    cnLog(&temp, base); // natural logarithm of the base: ln(b)
    temp = cnMultiply(cnI(power.imag), temp); // product of complex number and natural logarithm: p*ln(b)
    cnComplex_t factor2 = cnExp(temp); // instead of raising b^p, you can raise e^(p*ln(b))
    // Multiply the two factors
    cnComplex_t result = cnMultiply(factor1, factor2); // `result` carries the form of `factor1`, which carries the form of `base`

    // Return the result
    return result;
}

// Returns the conjugate of the complex number
cnComplex_t cnConjugate(cnComplex_t complexNum) {
    complexNum.imag *= -1; // negate the imaginary part or phase (shared memory)
    if (!complexNum.rectForm) { // if the complex number is in polar form
        complexNum.arg = cnPrincipleArg(complexNum.arg); // get principle argument
    }
    return complexNum;
}

cnComplex_t cnExp(cnComplex_t complexNum) {
    // Convert the complex number to rectangular form
    complexNum = cnRectForm(complexNum);
    // Calculate the magnitude
    double mag = exp(complexNum.real);
    // Calculate the argument
    double arg = cnPrincipleArg(complexNum.imag);
    // Return the resulting complex number
    return cnPolar(mag, arg);
}

bool cnLog(cnComplex_t *result, cnComplex_t complexNum) {
    // Convert the complex number to polar form
    complexNum = cnPolarForm(complexNum);

    // Check if the magnitude is zero
    if (complexNum.mod == 0.0) {
        return false;
    }

    // Calculate the real component
    double real = log(complexNum.mod);
    // Calculate the imaginary component
    double imag = complexNum.arg;
    // Return the resulting complex number
    *result = cnRect(real, imag);

    // Indicate success
    return true;
}

double cnPrincipleArg(double angle) {
    // Reduce range to [-PI, PI)
    double arg = fmod(angle + PI, 2 * PI) - PI;
    // Convert range to (-PI, PI]
    if (arg == -PI) {
        arg = PI;
    }
    // Return the principle argument
    return arg;
}

// ================================

#ifdef __PI_WAS_UNDEFINED_BY_USER // if PI was not defined by the user
    #undef PI
    #undef __PI_WAS_UNDEFINED_BY_USER
#endif
