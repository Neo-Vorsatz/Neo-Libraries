# C Complex Numbers
## Overview
This module is for complex number operations in C.<br>
With it, you can create, edit, and do computations with complex numbers, including but not limited to:
- Getting the magnitude of a complex number
- Complex number multiplication
- Getting the conjugate of a complex number
- Complex exponentiation

Note: All angles are measured in radians.

## Credits
This module was made with the help of [Ambesiwe Sonka](https://github.com/Ambesiwe).

## Features
This module was designed with the intention of being embedded-friendly:
- Minimal memory footprint
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `cn` prefix)

## Quick Start
```c
#include <stdio.h>
#include "complex_numbers.h"

int main() {
  complex z1 = cnRect(1.0, 2.0); //1+2i
  complex z2 = cnPolar(3.0, 0.785); //5 @ pi/4

  complex sum = cnAdd(z1, z2);
  printf("Real: %f, Imag: %f\n", cnReal(&sum), cnImag(&sum));

  return 0;
}
```

## Installation & Dependencies
Copy the header and implementation files anywhere where your C-compiler can find it (such as in the same directory as your main file). Then import the module like you would any other module, using `#include`.

This module has the following dependencies:<br>
Standard: `math.h`, `stdbool.h`<br>
This Repository: None

## API Reference
### Macros
#### Pi
You can define a macro called `PI` before you `#include` the module, and this will modify the value of pi used throughout the module.

### Data Structures
#### Complex Number
This is a struct containing two variables that determine the value of the complex number, as well as whether these variables represents rectangular or polar form. Create a complex number like you would any other struct:
```c
complex myComplexNum;
```
then `myComplexNum` will be a struct representing a complex number.

### Functions
<details>
<summary>Click to view all Creating functions</summary>

`complex cnRect(double real, double imag);`<br>
Takes the real part of the complex number, and the imaginary part of the complex number.<br>
Returns a complex number in rectangular form.

`complex cnPolar(double mag, double phase);`<br>
Takes the magnitude of the complex number, and the phase of the complex number.<br>
Returns a complex number in polar form.

`complex cnR(double real);`<br>
Takes the real part of the complex number.<br>
Returns a complex number in rectangular form, with only a real component.

`complex cnI(double imag);`<br>
Takes the imaginary part of the complex number.<br>
Returns a complex number in rectangular form, with only an imaginary component.

`complex cnA(double arg);`<br>
Takes the argument of the complex number.<br>
Returns a complex number in polar form, with magnitude 1.

</details>

<details>
<summary>Click to view all Reading functions</summary>

`double cnReal(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns the real component of a complex number.

`double cnImag(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns the imaginary component of a complex number.

`double cnMag(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns the magnitude of a complex number.

`double cnArg(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns the argument of a complex number.

`bool cnIsRect(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns whether or not a complex number is in rectangular form.

`bool cnIsPolar(const complex *complexNum);`<br>
Takes a complex number.<br>
Returns whether or not a complex number is in polar form.

</details>

<details>
<summary>Click to view all Updating functions</summary>

`void cnSetReal(complex *complexNum, double real);`<br>
Sets the real component of a complex number.<br>
Takes a complex number, and the new real component of the complex number.

`void cnSetImag(complex *complexNum, double imag);`<br>
Sets the imaginary component of a complex number.<br>
Takes a complex number, and the new imaginary component of the complex number.

`void cnSetMag(complex *complexNum, double mag);`<br>
Sets the magnitude of a complex number.<br>
Takes a complex number, and the new magnitude of the complex number.

`void cnSetArg(complex *complexNum, double arg);`<br>
Sets the argument of a complex number.<br>
Takes a complex number, and the new argument of the complex number.

`void cnSetForm(complex *complexNum, bool rect);`<br>
Sets whether or not a complex number is in rectangular form.<br>
Warning: This changes the effective-value of the complex number, not just the form.<br>
Takes a complex number, and whether or not the complex number is set to rectangular form, else polar form.

</details>

<details>
<summary>Click to view Operations functions</summary>

`bool cnEqual(complex complexNum1, complex complexNum2, double tolerance);`<br>
Takes a complex number, another complex number, and the tolerance to use when comparing floating points.<br>
Returns whether or not two complex numbers are equal.

`complex cnRectForm(complex complexNum);`<br>
Takes a complex number.<br>
Returns the complex number in rectangular form.

`complex cnPolarForm(complex complexNum);`<br>
Takes a complex number.<br>
Returns the complex number in polar form.

`complex cnAdd(complex complexNum1, complex complexNum2);`<br>
Takes a complex number, and another complex number.<br>
Returns the sum of two complex numbers.

`complex cnSub(complex complexNum1, complex complexNum2);`<br>
Takes a complex number, and another complex number.<br>
Returns the difference of two complex numbers.

`complex cnScale(complex complexNum, double scalar);`<br>
Takes a complex number, and a real scalar.<br>
Returns the complex number multiplied by a scalar.

`complex cnMultiply(complex complexNum1, complex complexNum2);`<br>
Takes a complex number, and another complex number.<br>
Returns the product of two complex numbers.

`bool cnDivide(complex *quotient, complex numerator, complex denominator);`<br>
Calculates the quotient of two complex numbers.<br>
Takes a pointer to where the result will be written, a complex number, and another complex number.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`complex cnPow(complex base, double power);`<br>
Takes a complex number, and the power to raise the complex number to.<br>
Returns the complex number raised to a real power.

`complex cnPowComplex(complex base, complex power);`<br>
Takes a complex number, and the power to raise the complex number to.<br>
Returns the complex number raised to a complex power.

`complex cnConjugate(complex complexNum);`<br>
Takes a complex number.<br>
Returns the conjugate of the complex number.

`complex cnExp(complex complexNum);`<br>
Takes a complex number.<br>
Returns e raised to the power of a complex number (Euler's formula).

`bool cnLog(complex *result, complex complexNum);`<br>
Calculates the natural logarithm of a complex number.<br>
Takes a pointer to where the result will be written, and a complex number.<br>
Returns 1 (true) if the process was successful, otherwise returns 0 (false).

`double cnPrincipleArg(double angle);`<br>
Takes an angle.<br>
Returns the principle argument of an angle.

</details>