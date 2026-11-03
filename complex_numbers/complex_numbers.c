// Complex Numbers Library, for complex number operations
// Implementation file
// by Ambesiwe Sonka and Neo Vorsatz
// Last updated: 25 December 2025

#include <math.h>
#include "complex_numbers.h"

/* EDIT WITH MACROS ================================*/

#ifndef PI
  #define PI 3.14159265358979323846 //Same value in math.h, but defined locally
  #define __PI_WAS_UNDEFINED_BY_USER //Note that PI was not defined by the user
#endif

/*================================*/
/* CREATING ================================*/

//Returns a complex number in rectangular form
complex cnRect(double real, double imag) {
  complex complexNum = {real, imag, true};
  return complexNum;
}

//Returns a complex number in polar form
complex cnPolar(double mag, double arg) {
  if (mag<0) { //If the magnitude is negative
    mag = -mag; //Correct the magnitude
    arg += PI; //Rotate the phase
  }
  complex complexNum = {mag, cnPrincipleArg(arg), false};
  return complexNum;
}

//Returns a complex number in rectangular form, with only a real component
complex cnR(double real) {
  complex complexNum = {real, 0.0, true};
  return complexNum;
}

//Returns a complex number in rectangular form, with only an imaginary component
complex cnI(double imag) {
  complex complexNum = {0.0, imag, true};
  return complexNum;
}

//Returns a complex number in polar form, with magnitude 1
complex cnA(double arg) {
  complex complexNum = {1.0, cnPrincipleArg(arg), false};
  return complexNum;
}

/*================================*/
/* READING ================================*/

//Returns the real component of a complex number
double cnReal(const complex *complexNum) {
  //If the complex number is in rectangular form
  if (complexNum->rect_form) {
    return complexNum->real;
  }
  return complexNum->mod*cos(complexNum->arg);
}

//Returns the imaginary component of a complex number
double cnImag(const complex *complexNum) {
  //If the complex number is in rectangular form
  if (complexNum->rect_form) {
    return complexNum->imag;
  }
  return complexNum->mod*sin(complexNum->arg);
}

//Returns the magnitude of a complex number
double cnMag(const complex *complexNum){
  //If the complex number is in rectangular form
  if (complexNum->rect_form) {
    //Use Pythagorean formula
    return sqrt((complexNum->real*complexNum->real)+(complexNum->imag*complexNum->imag));
  }
  return complexNum->mod;
}

//Returns the argument of a complex number
double cnArg(const complex *complexNum){
  //If the complex number is in rectangular form
  if (complexNum->rect_form) {
    return cnPrincipleArg(atan2(complexNum->imag, complexNum->real));
  }
  return complexNum->arg;
}

//Returns whether or not a complex number is in rectangular form
bool cnIsRect(const complex *complexNum){
  return complexNum->rect_form;
}

//Returns whether or not a complex number is in polar form
bool cnIsPolar(const complex *complexNum){
  return !complexNum->rect_form;
}

/*================================*/
/* UPDATING ================================*/

//Sets the real component of a complex number
void cnSetReal(complex *complexNum, double real){
  bool rect_form = complexNum->rect_form; //Save the current form
  *complexNum = cnRectForm(*complexNum); //Convert to rectangular form
  complexNum->real = real;
  if (!rect_form) {
    *complexNum = cnPolarForm(*complexNum); //Convert back to polar form
  }
}

//Sets the imaginary component of a complex numbers
void cnSetImag(complex *complexNum, double imag){
  bool rect_form = complexNum->rect_form; //Save the current form
  *complexNum = cnRectForm(*complexNum); //Convert to rectangular form
  complexNum->imag = imag;
  if (!rect_form) {
    *complexNum = cnPolarForm(*complexNum); //Convert back to polar form
  }
}

//Sets the magnitude of a complex number
void cnSetMag(complex *complexNum, double mag){
  //Converting to polar form
  bool rect_form = complexNum->rect_form; //Save the current form
  *complexNum = cnPolarForm(*complexNum); //Convert to polar form

  //Assigning new magnitude
  if (mag<0) { //If the magnitude is negative
    complexNum->mod = -mag;
  } else { //The magnitude is positive
    complexNum->mod = mag;
  }

  //Converting back to rectangular form if necessary
  if (rect_form) {
    *complexNum = cnRectForm(*complexNum); //Convert back to polar form
  }
}

//Sets the argument of a complex number
void cnSetArg(complex *complexNum, double arg){
  bool rect_form = complexNum->rect_form; //Save the current form
  *complexNum = cnPolarForm(*complexNum); //Convert to polar form
  complexNum->arg = cnPrincipleArg(arg);
  if (rect_form) {
    *complexNum = cnRectForm(*complexNum); //Convert back to polar form
  }
}

//Sets whether or not a complex number is in rectangular form
void cnSetForm(complex *complexNum, bool rect){
  complexNum->rect_form = rect;
}

/*================================*/
/* OPERATIONS ================================*/

//Returns whether or not two complex numbers are equal
bool cnEqual(complex complexNum1, complex complexNum2, double tolerance) {
  if (complexNum1.rect_form) { //Do the check in rectangular form
    //Convert the second complex number to rectangular form
    complexNum2 = cnRectForm(complexNum2);

    //Check if the real components are different
    if (fabs(complexNum1.real-complexNum2.real)>tolerance) {
      return false;
    }
    //Check if the imaginary components are different
    if (fabs(complexNum1.imag-complexNum2.imag)>tolerance) {
      return false;
    }

  } else { //Do the check in polar form
    //Convert the second complex number to polar form
    complexNum2 = cnPolarForm(complexNum2);

    //Check if the magnitudes are different
    if (fabs(complexNum1.mod-complexNum2.mod)>tolerance) {
      return false;
    }
    //Check if the arguments are different and the magnitudes are not zero
    if (fabs(complexNum1.arg-complexNum2.arg)>tolerance && fabs(complexNum1.mod)>tolerance) {
      return false;
    }
  }

  //All checks are passed
  return true;
}

//Returns the complex number in rectangular form
complex cnRectForm(complex complexNum) {
  //If the complex number is already in rectangular form
  if (complexNum.rect_form) {
    //Return the original complex number
    return complexNum;
  }
  return cnRect(cnReal(&complexNum), cnImag(&complexNum));
}

//Returns the complex number in polar form
complex cnPolarForm(complex complexNum) {
  //If the complex number is in rectangular form
  if (complexNum.rect_form) {
    return cnPolar(cnMag(&complexNum), cnArg(&complexNum));
  }
  //Return the original complex number
  return complexNum;
}

//Returns the sum of two complex numbers
complex cnAdd(complex complexNum1, complex complexNum2) {
  //Use the form of the first complex number
  bool rect_form = complexNum1.rect_form;

  //Convert complex numbers to rectangular form
  complexNum1 = cnRectForm(complexNum1);
  complexNum2 = cnRectForm(complexNum2);

  //Add the real parts
  double real = complexNum1.real+complexNum2.real;
  //Add the imaginary parts
  double imag = complexNum1.imag+complexNum2.imag;
  //Create the resulting complex number
  complex result = cnRect(real, imag);
  if (!rect_form) {
    result = cnPolarForm(result); //Convert the result to polar form
  }

  //Return the result
  return result;
}

//Returns the difference of two complex numbers
complex cnSub(complex complexNum1, complex complexNum2) {
  complexNum2 = cnScale(complexNum2, -1); //Negate the second complex number
  return cnAdd(complexNum1, complexNum2);
}

//Returns the complex number multiplied by a real scalar
complex cnScale(complex complexNum, double scalar) {
  if (complexNum.rect_form) {
    complexNum.real *= scalar; //Scale the real component
    complexNum.imag *= scalar; //Scale the imaginary component
  } else {
    complexNum.mod *= scalar; //Scale the magnitude
  }
  return complexNum;
}

//Returns the product of two complex numbers
complex cnMultiply(complex complexNum1, complex complexNum2) {
  if (complexNum1.rect_form) { //Do calculations in rectangular form
    //Convert the second complex number to rectangular form
    complexNum2 = cnRectForm(complexNum2);

    //Calculate the real component
    double real = complexNum1.real*complexNum2.real-complexNum1.imag*complexNum2.imag;
    //Calculate the imaginary component
    double imag = complexNum1.real*complexNum2.imag+complexNum1.imag*complexNum2.real;

    //Return the resulting complex number
    return cnRect(real, imag);

  } else { //Do calculations in polar form
    //Convert the second complex number to polar form
    complexNum2 = cnPolarForm(complexNum2);

    //Calculate the magnitude
    double mag = complexNum1.mod*complexNum2.mod;
    //Calculate the argument
    double arg = cnPrincipleArg(complexNum1.arg+complexNum2.arg);

    //Return the resulting complex number
    return cnPolar(mag, arg);
  }
}

//Calculates the quotient of two complex numbers
bool cnDivide(complex *quotient, complex numerator, complex denominator) {
  //Save the form of the first complex number
  bool rect_form = numerator.rect_form;
  //Convert complex numbers to polar form
  numerator = cnPolarForm(numerator);
  denominator = cnPolarForm(denominator);

  //Check if denominator is zero
  if (denominator.mod==0.0) {
    return false;
  }

  //Divide magnitudes
  double mag = numerator.mod/denominator.mod;
  //Subtract arguments
  double arg = cnPrincipleArg(numerator.arg-denominator.arg);
  //Create the resulting complex number
  complex result = cnPolar(mag, arg);
  if (rect_form) {
    result = cnRectForm(result); //Convert the result to rectangular form
  }
  //Assign the result to the quotient
  *quotient = result;

  //Indicate success
  return true;
}

//Returns the complex number raised to a real power
complex cnPow(complex base, double power) {
  //Save the current form
  bool rect_form = base.rect_form;
  //Convert to polar form
  base = cnPolarForm(base);

  //Calculate the magnitude
  double mag = pow(base.mod, power);
  //Calculate the argument
  double arg = cnPrincipleArg(base.arg*power);
  //Create the resulting complex number
  complex result = cnPolar(mag, arg);
  if (rect_form) {
    result = cnRectForm(result); //Convert the result to rectangular form
  }

  //Return the resulting complex number
  return result;
}

//Returns the complex number raised to a complex power
complex cnPowComplex(complex base, complex power) {
  //Convert power to rectangular form
  power = cnRectForm(power);

  //Calculate the first factor (from the real power)
  complex factor1 = cnPow(base, power.real);
  //Calculate the second factor (from the imaginary power)
  complex temp; //Temporary variable for intermediate steps
  cnLog(&temp, base); //Natural logarithm of the base: ln(b)
  temp = cnMultiply(cnI(power.imag), temp); //Product of complex number and natural logarithm: p*ln(b)
  complex factor2 = cnExp(temp); //Instead of raising b^p, you can raise e^(p*ln(b))
  //Multiply the two factors
  complex result = cnMultiply(factor1, factor2); //`result` carries the form of `factor1`, which carries the form of `base`

  //Return the result
  return result;
}

//Returns the conjugate of the complex number
complex cnConjugate(complex complexNum) {
  complexNum.imag *= -1; //Negate the imaginary part or phase (shared memory)
  if (!complexNum.rect_form) { //If the complex number is in polar form
    complexNum.arg = cnPrincipleArg(complexNum.arg); //Get principle argument
  }
  return complexNum;
}

//Returns e raised to the power of a complex number (Euler's formula)
complex cnExp(complex complexNum) {
  //Convert the complex number to rectangular form
  complexNum = cnRectForm(complexNum);
  //Calculate the magnitude
  double mag = exp(complexNum.real);
  //Calculate the argument
  double arg = cnPrincipleArg(complexNum.imag);
  //Return the resulting complex number
  return cnPolar(mag, arg);
}

//Returns the natural logarithm of a complex number
bool cnLog(complex *result, complex complexNum) {
  //Convert the complex number to polar form
  complexNum = cnPolarForm(complexNum);

  //Check if the magnitude is zero
  if (complexNum.mod==0.0) {
    return false;
  }

  //Calculate the real component
  double real = log(complexNum.mod);
  //Calculate the imaginary component
  double imag = complexNum.arg;
  //Return the resulting complex number
  *result = cnRect(real, imag);

  //Indicate success
  return true;
}

//Returns the principle argument of an angle
double cnPrincipleArg(double angle) {
  //Reduce range to [-PI, PI)
  double arg = fmod(angle+PI, 2*PI)-PI;
  //Convert range to (-PI, PI]
  if (arg==-PI) {
    arg = PI;
  }
  //Return the principle argument
  return arg;
}

/*================================*/

#ifdef __PI_WAS_UNDEFINED_BY_USER //if PI was not defined by the user
  #undef PI
  #undef __PI_WAS_UNDEFINED_BY_USER
#endif