# Braccio Actuation

---

## Overview
This library is a re-implementation of the [Braccio library](https://github.com/arduino-libraries/Braccio) for Arduino. This implementation offers more functionality, by providing more granular control as well as advanced features. A link was provided for more information about the original library, but it appears to be a dead link:
[Tinkerkit Braccio](http://www.arduino.org/products/tinkerkit/17-arduino-tinkerkit/arduino-tinkerkit-braccio)

Here's an online copy of the instruction manual that comes with the Braccio kit:
[Braccio Instruction Manual](https://docs.rs-online.com/f6a4/A700000014019596.pdf)<br>
All of the code examples are obsolete if using this library. I hope the example provided in [Quick Start](#quick-start) will be sufficient.

This library originated in a project for the University of Cape Town:<br>
[Secure Teleoperation of a Robotic Arm using Computer Vision](https://github.com/Neo-Vorsatz-UCT/eee4022s)

---

## Features
- Minimal reliance on C++ features
- Non-blocking actuation with exponential smoothing
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `ba` prefix)
- Uses singular precision (`float` instead of `double`)

---

## Installation & Dependencies
Copy the header and implementation files anywhere where your compiler can find it, such as in the same directory as your main file. In a development environment like the one PlatformIO provides, the recommendation is to copy this entire folder and put it inside `lib`.<br>
Then import the library like you would any other library, using `#include`.

This library has the following dependencies:<br>
| Source | Dependencies |
| - | - |
| This Repository | None |
| Standard Library | None |
| Other | `Arduino.h`, `Servo.h` |

---

## Quick Start
```c++
#include <Arduino.h>
#include "braccio_actuation.h"

void setup() {
    // Initialize serial
    Serial.begin(9600);
    if (Serial) {Serial.println("Program started");}

    // Initialize arm
    if (!baInit()) {
        if (Serial) {Serial.println("Initializing Braccio failed");}
        while (1); // stop the program
    }

    // Set a target
    vector_t target = baNewVector(
        90.0f, // base <- forward
        90.0f, // joint1 <- upward
        90.0f, // joint2 <- upward
        90.0f, // joint3 <- upward
        90.0f, // wrist <- neutral
        180.0f // claw <- closed
    );
    baUpdateTarget(target);
    if (Serial) {Serial.println("Starting movement...");}
}

void loop() {
    // Move the Braccio arm incrementally towards the target
    baStep();

    // Check if the target is reached
    if (baAtTarget()) {
        while (1); // stop the program
    }
}
```

---

## API Reference

---

### Types
#### Vector
This is a struct containing six `float`, which each represent an angle for a joint of the Braccio.
Create a vector like you would any other struct:
```c++
vector_t myVector;
```
An initialized instance can be created using `baNewVector()`.

---

### Macros
#### Default Soft Start
The value of `BA_DEFAULT_SOFT_START` is 20, and is the recommended value for the soft start speed when calling `baInit()`.

#### Disable Soft Start
The value of `BA_DISABLE_SOFT_START` is 0, and will disable soft start, making the servo motors receive full power immediately.

#### Max Soft Start
The value of `BA_MAX_SOFT_START` is 40, and is the fastest the library allows the motors to be started, without disabling soft start altogether.

#### Min Soft Start
The value of `BA_MIN_SOFT_START` is 5, and is the slowest the library allows the motors to be started.

#### MX
The value of `BA_Mx` (where `x` refers to a number from 1 to 6) is `x-1`. For example, `BA_M3` has value 2. This macro is used to sequence the motor connectors, if for whatever reason your motors are connected in an unconventional order. This is done when calling `baInit()`.
```c++
const int connections[6] = {BA_M1, BA_M2, BA_M4, BA_M3, BA_M5, BA_M6}; // connections 3 and 4 are swapped
baInit(BA_DEFAULT_SOFT_START, connections);
```
#### Position Tolerance
The value of `BA_POS_TOLERANCE` is 25.0f, and is the default acceptable sum of squared errors, when comparing the target and actual position of each of the motors.

---

### Constants
#### Default Connection
`BA_DEFAULT_CONN` is a 6-element array of integers that describes the default sequence of motor connect (1 to 6).

---

### Functions
<details>
<summary>Click to view all Initializers and Creation functions</summary>

`void baInit(int softStart=BA_DEFAULT_SOFT_START, const int conn[6]=BA_DEFAULT_CONN);`<br>
Initializes the Braccio arm operation.<br>
Takes the soft start value, and the connector arrangement/order.

`vector_t baNewVector(float base, float joint1, float joint2, float joint3, float wrist, float claw);`<br>
Creates a new vector.<br>
Takes the value for the base, the value for the first joint, the value for the second joint, the value for the third joint, the value for the wrist, and the value for the claw.<br>
Returns the new vector.

</details>

<details>
<summary>Click to view all Reading functions</summary>

`vector_t baGetTarget();`<br>
Gets the desired position the Braccio arm is aiming for.<br>
Returns the desired position.

`vector_t baGetPosition();`<br>
Gets the current position of the Braccio arm.<br>
Return the current position.

`float baGetError();`<br>
Gets the squared error between the desired position and the current position.<br>
Returns the sum of squared position errors.

`bool baAtTarget(float tolerance=BA_POS_TOLERANCE);`<br.
Checks if the Braccio arm is at the desired position.<br>
Takes the squared positional tolerance.<br>
Returns `true` if the arm is at the desired position, otherwise `false`.

</details>

<details>
<summary>Click to view all Controlling functions</summary>

`bool baSetPosition(vector_t position);`<br>
Sets the position of the Braccio arm.<br>
Takes the position to set the arm to.<br>
Returns `true` if the position is within the mechanical constraints, otherwise `false`.<br>
Note that this function is not recommended, because it'll cause jerking.

`bool baUpdateTarget(vector_t target);`<br>
Updates the desired position of the Braccio arm.<br>
Takes the desired position.<br>
Returns `true` if the position is within the mechanical constraints, otherwise `false`.

`void baStep();`<br>
Steps the Braccio arm towards the desired position.<br>
Note that this function is recommended, and should be called within a loop, along with `baUpdateTarget()`.

`bool baMove(vector_t target);`<br>
Handles the movement of the Braccio arm completely.<br>
Takes the desired position.<br>
Returns `true` if the position is within the mechanical constraints, otherwise `false`.<br>
Note that this function is blocking; occupies a thread until the desired position is reached. The function stops running when negligibly close to the desired position.

`void baSetFilterTau(float tau);`<br>
Sets the time constant for 1 stage of the cascaded 2nd order low-pass filter.<br>
Takes the new time constant, measured in seconds.

`void baSetFilterFreq(float freq);`<br>
Sets the cutoff frequency (Hz) for 1 stage of the cascaded 2nd order low-pass filter.<br>
Takes the new cutoff frequency.<br>
Note that the filter's characteristic is stored as a time constant (tau), making `baSetFilterTau()` more efficient. You can manually calculate the time constant as: tau=1/(2*pi*freq).

</details>

<details>
<summary>Click to view all Management functions</summary>

`bool baTargetReachable(vector_t target);`<br>
Checks if the target is reachable, given mechanical constraints.<br>
Takes the desired position.<br>
Returns `true` if the target is reachable, otherwise `false`.

`bool baBoundPosition(vector_t *position);`<br>
Bounds a pos by the mechanical constraints.<br>
Takes a pointer to the position to bound.<br>
Returns `true` if the position was within the mechanical constraints, otherwise `false`.<br>
Note that most controlling functions call this automatically.

</details>

---

## License
In accordance with the original library, this library is licensed under the GNU Lesser General Public License v2.1, as published by the Free Software Foundation.
