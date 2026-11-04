# Introduction
This is a collection of libraries I've programmed in C/C++, targeted towards electrical, embedded systems, or mechatronics engineers.

---

# Installation & Dependencies
It's recommended to copy this entire repository into somewhere you keep your installed libraries, because some of the libraries in this repository depend on other libraries within in repository.
```bash
git clone https://github.com/Neo-Vorsatz/Neo-Libraries.git
```

The following table shows the dependencies of all libraries in this repository.
| Source | Dependencies |
| - | - |
| Standard Library | `math.h`, `stdbool.h`, `string.h` |
| Other | `Arduino.h`, `Servo.h` |

---

# Libraries
| Name | Status | Language | Description |
| - | - | - | - |
| Braccio Actuation | Up to date | C++ | [see below](#braccio-actuation) |
| Complex Numbers | Up to date | C | [see below](#complex-numbers) |
| Data Handling | Up to date | C | [see below](#data-handling) |
| Digital Signal Processing | Incomplete | C | [see below](#digital-signal-processing) |
| Matrices | Up to date | C | [see below](#matrices) |
| RGB LED | Up to date | C | [see below](#rgb-led) |

## Braccio Actuation
This library is a re-implementation of the [Braccio library](https://github.com/arduino-libraries/Braccio) for Arduino. This implementation offers more functionality, by providing more granular control as well as advanced features. A link was provided for more information about the original library, but it appears to be a dead link:
[Tinkerkit Braccio](http://www.arduino.org/products/tinkerkit/17-arduino-tinkerkit/arduino-tinkerkit-braccio)

Here's an online copy of the instruction manual that comes with the Braccio kit:
[Braccio Instruction Manual](https://docs.rs-online.com/f6a4/A700000014019596.pdf)<br>
All of the code examples are obsolete if using this library. I hope the example provided in [Quick Start](#quick-start) will be sufficient.

This library originated in a project for the University of Cape Town:<br>
[Secure Teleoperation of a Robotic Arm using Computer Vision](https://github.com/Neo-Vorsatz-UCT/eee4022s)

## Complex Numbers
This library is for complex number operations in C.<br>
With it, you can create, edit, and do computations with complex numbers, including but not limited to:
- Getting the magnitude of a complex number
- Complex number multiplication
- Getting the conjugate of a complex number
- Complex exponentiation

## Data Handling
This library is for interpreting and processing data in C.<br>
Some functionality this module offers is:
- Getting the cumulative sum of data
- Sorting data in ascending order, or reversing the order
- Getting the mean, variance and standard deviation of a set of data

## Digital Signal Processing
> [!WARNING]
> This library is currently incomplete, and so promises no guarantees of functionality nor consistent APIs.
This library is for interpreting and processing digital signals in C.<br>
Some functionality this module offers is:
- Getting the DC or AC components of a signal
- Getting the energy and power of a signal
- Bringing a signal to and from the frequency domain (Fourier)

## Matrices
This library is for matrix operations in C.<br>
With it, you can create, edit, and do computations with matrices, including but not limited to:
- Matrix multiplication
- Getting the determinant of a square matrix
- Getting the inverse of a square matrix
- Gauss elimination into Reduced Row Echelon form
- Solving for vectors, using a transformation and matrix of resulting vectors

## RGB LED
This library is for controlling RGB LEDs, and is programmed in C for microcontrollers.<br>
With it, you can calculate the PWM duty cycle needed for each LED (red, green and blue), taking into account the various voltage drops and series resistances. This library offers support for hex and HSV codes.
