# C Digital Signal Processing [Warning: In Production]
## Overview
This module is for processing and generating signals in C.<br>
Some functionality this module offers is:
- Getting the DC or AC components of a signal
- Getting the energy and power of a signal
- Bringing a signal to and from the frequency domain (Fourier)
- Performing real-time operations like filtering

Note: All angles are measured in radians.

## Features
This module was designed with the intention of being embedded-friendly:
- Minimal memory footprint
- No dynamic memory usage (no `malloc` and `free`)*
- Low namespace pollution (uses `ds` prefix)

*may change

## Quick Start
```c
#include <stdio.h>
#include "digital_signal_processing.h"

int main() {
  //TODO

  return 0;
}
```

## Installation & Dependencies
Copy the folder (and its contents) of this module, and the other modules it depends on. Place the copies anywhere where your C-compiler can find it (such as in the same directory as your main file). Then import the module like you would any other module, using `#include`.<br>
It's recommended to copy this entire repository into somewhere you keep your installed libraries.
```bash
git clone https://github.com/Neo-Vorsatz/Neo-Libraries.git
```

This module has the following dependencies:<br>
Standard: `math.h`, `stdbool.h`<br>
This Repository: `data_handling.h`, `complex_numbers.h`

## API Reference
### Macros
#### Pi
You can define a macro called `PI` before you `#include` the module, and this will modify the value of pi used throughout the module.

### Data Structures

### Functions
<details>
<summary>Click to view all Systems functions</summary>

</details>
<details>
<summary>Click to view all Electricity functions</summary>

`double dsDC(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the Direct-Current component of a signal.

`bool dsAC(signal *write, const signal *read);`<br>
Removes the Direct-Current offset from a signal.<br>
Takes a pointer to where the modified signal will be written, and a pointer to the signal.<br>
Returns 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'.

`bool dsPower(signal *write, const signal *read);`<br>
Gets the power of the signal at each time step.<br>
Takes a pointer to where the power of the signal will be written, and a pointer to the signal.<br>
Returns 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'.

`double dsEnergy(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the total energy of a signal.

`bool dsCumSumEnergy(signal *write, signal *read);`<br>
Gets the cumulative sum of energy of a signal.<br>
Takes a pointer to where the cumulative sum of energy will be written, and a pointer to the signal.<br>
Returns 1 (true) if the process was successful, otherwise 0 (false) if there was not enough memory in 'write'.

`double dsAvgPower(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the average power of a signal.

`double dsACRMS(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the Alternating-Current Root-Mean-Square of a signal.

`double dsRMS(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the Root-Mean-Square of a signal.

`double dsDCPower(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the Direct-Current power of a signal.

`double dsACPower(const signal *read);`<br>
Takes a pointer to the signal.<br>
Returns the Alternating-Current power of a signal.

</details>

<details>
<summary>Click to view all Fourier functions</summary>

</details>