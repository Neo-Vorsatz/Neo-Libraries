# Introduction
This is a collection of libraries/modules I've programmed in C/C++, targetted towards electrical or embedded systems engineers.

# Installation & Dependencies
It's recommended to copy this entire repository into somewhere you keep your installed libraries, because some of the modules depend on other modules within this repository.
```bash
git clone https://github.com/Neo-Vorsatz/Neo-Libraries.git
```

Dependencies outside of this repository:<br>
`math.h`,`stdbool.h`

# Libraries
## Complex Numbers
This module is for complex number operations in C.<br>
With it, you can create, edit, and do computations with complex numbers, including but not limited to:
- Getting the magnitude of a complex number
- Complex number multiplication
- Getting the conjugate of a complex number
- Complex exponentiation

## Data Handling
This module is for interpretting and processing data in C.<br>
Some functionality this module offers is:
- Getting the cumulative sum of data
- Sorting data in ascending order, or reversing the order
- Getting the mean, variance and standard deviation of a set of data

## Digital Signal Processing [Warning: In Production]
This module is for interpretting and processing digital signals in C.<br>
Some functionality this module offers is:
- Getting the DC or AC components of a signal
- Getting the energy and power of a signal
- Bringing a signal to and from the frequency domain (Fourier)

## Matrices
This module is for matrix operations in C.<br>
With it, you can create, edit, and do computations with matrices, including but not limited to:
- Matrix multiplication
- Getting the determinant of a square matrix
- Getting the inverse of a square matrix
- Guass elimination into Reduced Row Echelon form
- Solving for vectors, using a transformation and matrix of resulting vectors

## RGB LED [Warning: Untested]
This module is for controlling RGB LEDs, and is programmed in C for microcontrollers.<br>
With it, you can calculate the PWM duty cycle needed for each LED (red, green and blue), taking into account the various voltage drops and series resistances. This module offers support for hex and HSV codes.