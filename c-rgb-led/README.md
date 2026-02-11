# C RGB LED [Warning: Untested]
## Overview
This module is for controlling RGB LEDs, and is programmed in C for microcontrollers.<br>
With it, you can calculate the PWM duty cycle needed for each LED (red, green and blue), taking into account the various voltage drops and series resistances. This module offers support for hex and HSV codes.

## Features
This module was designed with the intention of being embedded-friendly:
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `rl` prefix)
- Using singular precision (`float` instead of `double`)

## Quick Start
```c
#include <stdio.h>
#define MX_SIZE 2
#include "matrices.h"

int main() {
  //Create transformation matrix
  matrix transform;
  mxElement_t elements[2][2] = {{1,2},{3,1}};
  mxSet(&transform, 2, 2, elements);

  //Create resultant vector
  matrix result;
  mxSetSize(&result, 2, 1);
  mxElement_t vector[2] = {4,7};
  mxWriteColumn(&result,0,vector);

  //Solve for first element of the (first) input vector
  mxElement_t x = mxSolveCramer(&transform, &result, 0, 0);
  printf("X Coordinate: %f\n", x);

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
#### Red LED Voltage Drop
You can define a macro called `RL_RED_VOLTAGE_DROP` before you `#include` the module, and this will modify the default voltage drop for red LEDs.

#### Green LED Voltage Drop
You can define a macro called `RL_GREEN_VOLTAGE_DROP` before you `#include` the module, and this will modify the default voltage drop for green LEDs.

#### Blue LED Voltage Drop
You can define a macro called `RL_BLUE_VOLTAGE_DROP` before you `#include` the module, and this will modify the default voltage drop for blue LEDs.

#### Series Resistance
You can define a macro called `RL_SERIES_RESISTANCE` before you `#include` the module, and this will modify the default series resistance going to the LEDs.

#### Output Voltage
You can define a macro called `RL_OUTPUT_VOLTAGE` before you `#include` the module, and this will modify the default maximum output voltage going to the LEDs.

#### Maximum Writable Integer
You can define a macro called `RL_MAX_INT` before you `#include` the module, and this will modify the default maximum integer that can be written. This essentially controls the range (from 0 to this number, inclusive) that represents PWM duty cycle.

#### Common Anode
You can define a macro called `RL_COMMON_ANODE` before you `#include` the module, and this will modify whether the default settings assume RGB LEDs to have a common-anode or common-cathode configuration. Use `true` (1) or `false` (0) when defining this macro.

### Constants
| Constant | Description |
| - | - |
| `RL_DEFAULT_SETTINGS` | `rgbSettings` struct with the default settings |
| `RL_DEFAULT_ADVANCED_SETTINGS` | `rgbAdvancedSettings` struct with the default settings |
| `RL_RED` | `rgbCode` struct for the colour red |
| `RL_GREEN` | `rgbCode` struct for the colour green |
| `RL_BLUE` | `rgbCode` struct for the colour blue |
| `RL_WHITE` | `rgbCode` struct for the colour white |
| `RL_BLACK` | `rgbCode` struct for the colour black |
| `RL_YELLOW` | `rgbCode` struct for the colour yellow |
| `RL_MAGENTA` | `rgbCode` struct for the colour magenta |
| `RL_CYAN` | `rgbCode` struct for the colour cyan |
| `RL_ORANGE` | `rgbCode` struct for the colour orange |
| `RL_PURPLE` | `rgbCode` struct for the colour purple |
| `RL_GRAY` | `rgbCode` struct for the colour gray |

### Data Structures
#### RGB Code
This is a struct containing three `unsigned char`, for the red, green and blue values, and hence is able to represent a colour. Create an RGB code like you would any other struct:
```c
rgbCode myColour;
```
then `myColour` will be a struct representing a colour/RGB code.

#### Settings
This is a struct that stores the settings/configuration of an RGB LED and how it's connected/interfaced with. Create settings like you would any other struct:
```c
rgbSettings mySettings;
```
then `mySettings` will be a struct representing the configuration of an RGB LED.

#### Advanced Settings
Similar to the `rgbSettings` struct, this is a struct that stores the settings/configuration of an RGB LED and how it's connected/interfaced with, but allows for more customisation. This struct doesn't assume all LEDs have the same series resistance, voltage supply, nor maximum writable integer. Create advanced settings like you would any other struct:
```c
rgbAdvancedSettings myAdvSettings;
```
then `myAdvSettings` will be a struct representing the advanced (more customisable) configuration of an RGB LED.

### Functions
<details>
<summary>Click to view all Creating functions</summary>

`rgbCode rlRGBCode(unsigned char red, unsigned char green, unsigned char blue);`<br>
Takes the red value, the green value, and the blue value.<br>
Returns a new rgbCode struct.<br>
Alternatively, the macro `RGB(r,g,b)` can be used when declaring+initialising an rgbCode.

`void rlDefaultSettings(rgbSettings *write);`<br>
Sets rgbSettings to default values.<br>
Takes a pointer to where the settings will be written.

`void rlDefaultSettingsAdv(rgbAdvancedSettings *write);`<br>
Sets rgbAdvancedSettings to default values.<br>
Takes a pointer to where the settings will be written.

`void rlAdvance(rgbAdvancedSettings *write, const rgbSettings *settings);`<br>
Sets rgbAdvancedSettings to the same values as rgbSettings.<br>
Takes a pointer to where the advanced settings will be written, and a pointer to the settings.

</details>

<details>
<summary>Click to view all Calculations functions</summary>

`rgbCode rlHexToDec(const char hex[6]);`<br>
Takes a pointer to a hex code.<br>
Returns an RGB code struct, equivalent to the hex code.

`float rlDutyCycle(float output_voltage, float voltage_drop, float series_resistance, float power);`<br>
Takes the maximum output voltage going to the LED, the voltage drop across the LED, the series resistance of the LED, and the power desired to go to the LED.<br>
Returns the duty cycle needed for an amount of power, assuming common cathode.

`void rlDutyCyclesAdv(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rgbAdvancedSettings *settings, rgbCode code);`<br>
Calculates the duty cycles needed to display an RGB colour.<br>
Takes a pointer to where the red duty cycle will be written, a pointer to where the green duty cycle will be written, a pointer to where the blue duty cycle will be written, the settings of the RGB LED, and the RGB code.

`void rlDutyCycles(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rgbSettings *settings, rgbCode code);`<br>
Calculates the duty cycles needed to display an RGB colour.<br>
Takes a pointer to where the red duty cycle will be written, a pointer to where the green duty cycle will be written, a pointer to where the blue duty cycle will be written, the settings of the RGB LED, and the RGB code.

`void rlWriteValuesAdv(unsigned int *red, unsigned int *green, unsigned int *blue, const rgbAdvancedSettings *settings, rgbCode code);`<br>
Calculates the integers (likely for PWM) needed to display an RGB colour.<br>
Takes a pointer to where the red integer will be written, a pointer to where the green integer will be written, a pointer to where the blue integer will be written, the settings of the RGB LED, and the RGB code.

`void rlWriteValues(unsigned int *red, unsigned int *green, unsigned int *blue, const rgbSettings *settings, rgbCode code);`<br>
Calculates the integers (likely for PWM) needed to display an RGB colour.<br>
Takes a pointer to where the red integer will be written, a pointer to where the green integer will be written, a pointer to where the blue integer will be written, the settings of the RGB LED, and the RGB code.

`rgbCode rlLerp(rgbCode start, rgbCode end, float percentage);`<br>
Takes the start RGB code, the end RGB code, and a percentage from 0 to 1.<br>
Returns an RGB code that's the linear interpolation between two RGB codes.

`rgbCode rlHSVToRGB(float hue, float saturation, float value);`<br>
Takes the hue of the HSV code, the saturation of the HSV code, and the value of the HSV code.<br>
Returns an RGB code equivalent to the given HSV code.

</details>