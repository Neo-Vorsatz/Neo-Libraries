// Programme to test the complex numbers library
// by Neo Vorsatz
// Last updated: 25 December 2025

#include "complex_numbers.c"
#include <stdio.h>

void printComplex(complex complexNum) {
  if (complexNum.rect_form) {
    if (complexNum.imag < 0) {
      printf("%.3f%.3fi", complexNum.real, complexNum.imag); //Print without adding a '+'
    } else {
      printf("%.3f+%.3fi", complexNum.real, complexNum.imag); //Print while adding a '+'
    }
    
  } else {
    printf("%.3f<%.3f", complexNum.mod, complexNum.arg);
  }
}

int main() {
  complex z0;
  complex z1;
  complex z2;

  printf("=== Creating ===\n");

  //Testing creating rectangular complex numbers
  z1 = cnRect(1, 2);
  printf("Rectangular complex number: ");
  printComplex(z1);
  printf(" | expected: 1+2i\n");

  //Testing creating polar complex numbers
  z2 = cnPolar(3, 4);
  printf("Polar complex number: ");
  printComplex(z2);
  printf(" | expected: 3<-2.283\n");

  //Testing creating purely real numbers
  z0 = cnR(5);
  printf("Purely real number: ");
  printComplex(z0);
  printf(" | expected: 5+0i\n");

  //Testing creating purely imaginary numbers
  z0 = cnI(6);
  printf("Purely imaginary number: ");
  printComplex(z0);
  printf(" | expected: 0+6i\n");

  //Testing creating imagninary numbers with magnitude 1
  z0 = cnA(-3.14159265358979323846); //-PI or -180 degrees
  printf("Complex number with magnitude 1: ");
  printComplex(z0);
  printf(" | expected: 1<3.142\n");

  printf("=== Reading ===\n");

  //Testing getting real component
  printf("Real component: %.3f | expected: -1.961\n", cnReal(&z2));

  //Testing getting imaginary component
  printf("Imaginary component: %.3f | expected: -2.270\n", cnImag(&z2));

  //Testing getting magnitude/modulus
  printf("Magnitude/Modulus: %.3f | expected: 2.236\n", cnMag(&z1));

  //Testing getting argument
  printf("Argument: %.3f | expected: 1.107\n", cnArg(&z1));

  //Testing getting form
  if (cnIsRect(&z1)) {
    printf("Determined rectangular form as rectangular. (Yay)\n");
  }
  if (cnIsPolar(&z1)) {
    printf("Determined rectangular form as polar. (Oops)\n");
  }
  if (cnIsRect(&z2)) {
    printf("Determined polar form as rectangular. (Oops)\n");
  }
  if (cnIsPolar(&z2)) {
    printf("Determined polar form as polar. (Yay)\n");
  }

  printf("=== Updating ===\n");

  //Testing setting real and imaginary components
  cnSetReal(&z2, -2);
  cnSetImag(&z2, 2);
  printf("Setting rectangular: ");
  printComplex(z2);
  printf(" | expected: 2.828<2.356\n");

  //Testing setting magnitude and argument
  cnSetMag(&z1, 2);
  cnSetArg(&z1, -0.5235987756); //-PI/6 or -30 degrees
  printf("Setting polar: ");
  printComplex(z1);
  printf(" | expected: 1.732-1i\n");

  //Testing setting form
  cnSetForm(&z2, 1);
  printf("Forced rectangular: ");
  printComplex(z2);
  printf(" | expected: 2.828+2.356i\n");
  cnSetForm(&z1, 0);
  printf("Forced polar: ");
  printComplex(z1);
  printf(" | expected: 1.732<-1\n");

  printf("=== Operations ===\n");

  z1 = cnPolar(5, 0.927295218); //3+4i
  z2 = cnRect(1, 2);
  
  //Testing converting to rectangular form
  z1 = cnRectForm(z1);
  printf("Rectangular form: ");
  printComplex(z1);
  printf(" | expected: 3+4i\n");

  //Testing converting to polar form
  z2 = cnPolarForm(z2);
  printf("Polar form: ");
  printComplex(z2);
  printf(" | expected: 2.236<1.107\n");
  
  //Testing addition
  z0 = cnAdd(z1, z2);
  printf("Addition: ");
  printComplex(z0);
  printf(" | expected: 4+6i\n");

  //Testing subtraction
  z0 = cnSub(z1, z2);
  printf("Subtraction: ");
  printComplex(z0);
  printf(" | expected: 2+2i\n");

  //Testing scaling
  z0 = cnScale(z1, 3);
  printf("Scaling: ");
  printComplex(z0);
  printf(" | expected: 9+12i\n");

  //Testing multiplication
  z0 = cnMultiply(z1, z2);
  printf("Rect multiplication: ");
  printComplex(z0);
  printf(" | expected: -5+10i\n");
  z0 = cnMultiply(z2, z1);
  printf("Polar multiplication: ");
  printComplex(z0);
  printf(" | expected: 11.180<2.034\n");

  //Testing division
  cnDivide(&z0, z1, z2);
  printf("Division: ");
  printComplex(z0);
  printf(" | expected: 2.2-0.4i\n");

  //Testing real power
  z0 = cnPow(z1, 2.5);
  printf("Real power: ");
  printComplex(z0);
  printf(" | expected: -38+41i\n");

  //Testing complex power
  z0 = cnPowComplex(z1, z2);
  printf("Complex power: ");
  printComplex(z0);
  printf(" | expected: -0.420-0.660i\n");

  //Testing conjugate
  z0 = cnConjugate(z1);
  printf("Rect conjugate: ");
  printComplex(z0);
  printf(" | expected: 3-4i\n");
  z0 = cnConjugate(z2);
  printf("Polar conjugate: ");
  printComplex(z0);
  printf(" | expected: 2.236<-1.107\n");

  //Testing exponential
  z0 = cnRect(cnMag(&z2), cnArg(&z2));
  z0 = cnExp(z0);
  printf("Exponential: ");
  printComplex(z0);
  printf(" | expected: 9.356<1.107\n"); //Same argument as z2

  //Testing natural logarithm
  cnLog(&z0, cnR(-1)); //Euler's identity
  printf("Natural logarithm: ");
  printComplex(z0);
  printf(" | expected: 0+3.142i\n"); //0+PIi

  //Testing equality
  z1 = cnRect(0.0, 3.1416); //0+PIi
  if (cnEqual(z0, z1, 0.0001)) {
    printf("Equality: These values are equal.\n");
  } else {
    printf("Equality: These values are not equal.\n");
  }

  //Testing principle argument
  printf("Principle argument: %.3f | expected: -1\n", cnPrincipleArg(5.283185307)); //-1+2*PI

  //Finished
  return 0;
}