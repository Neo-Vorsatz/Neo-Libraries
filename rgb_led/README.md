# RGB LED

---

## Overview
This library is for controlling RGB LEDs, and is programmed in C for microcontrollers.<br>
With it, you can calculate the PWM duty cycle needed for each LED (red, green and blue), taking into account the various voltage drops and series resistances. This library offers support for hex and HSV codes.

---

## Features
This library was designed with the intention of being embedded-friendly:
- No dynamic memory usage (no `malloc` and `free`)
- Low namespace pollution (uses `rl` prefix)
- Using singular precision (`float` instead of `double`)

---

## Installation & Dependencies
Copy the header and implementation files anywhere where your compiler can find it, such as in the same directory as your main file. In a development environment like the one PlatformIO provides, the recommendation is to copy this entire folder and put it inside `lib`.<br>
Then import the library like you would any other library, using `#include`.

This library has the following dependencies:<br>
| Source | Dependencies |
| - | - |
| This Repository | None |
| Standard Library | `math.h`, `stdbool.h` |
| Other | None |

---

## Quick Start
```c++
#include <Arduino.h>
#include "rgb_led.h"

//Pin assignments
#define PIN_RED   9
#define PIN_GREEN 10
#define PIN_BLUE  11

void writeColour(rlRGB code) {
    unsigned int r, g, b;
    rlWriteValues(&r, &g, &b, &RL_DEFAULT_SETTINGS, code);
    analogWrite(PIN_RED, r);
    analogWrite(PIN_GREEN, g);
    analogWrite(PIN_BLUE, b);
}

void setup() {
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
}

void loop() {
    //Rainbow cycle
    for (float hue=0.0f; hue<360.0f; hue+=1.0f) {
        rlRGB colour = rlHSVToRGB(hue, 1.0f, 1.0f);
        writeColour(colour);
        delay(20);
    }
}
```

---

## API Reference

---

### Types
#### RGB Code
This is a struct containing three `unsigned char`, for the red, green and blue values, and hence is able to represent a colour. Create an RGB code like you would any other struct:
```c
rlRGB myColour;
```
An initialized instance can be created using `rlrlRGB()` or `RGB()`.

#### Settings
This is a struct that stores the settings/configuration of an RGB LED and how it's connected/interfaced with. Create settings like you would any other struct:
```c
rlSettings mySettings;
```
A declared instance can be set to the defaults using `rlDefaultSettings()`.

#### Advanced Settings
Similar to the `rlSettings` struct, this is a struct that stores the settings/configuration of an RGB LED and how it's connected/interfaced with, but allows for more customisation. This struct doesn't assume all LEDs have the same series resistance, voltage supply, nor maximum writeable integer. Create advanced settings like you would any other struct:
```c
rlAdvancedSettings myAdvSettings;
```
A declared instance can be set to the defaults using `rlDefaultSettingsAv()`, or an existing instance of `rlSettings` can be promoted to `rlAdvancedSettings` using `rlAdvance()`.

---

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

---

### Constants
| Constant | Description |
| - | - |
| `RL_DEFAULT_SETTINGS` | `rlSettings` struct with the default settings |
| `RL_DEFAULT_ADVANCED_SETTINGS` | `rlAdvancedSettings` struct with the default settings |
| `RL_RED` | `rlRGB` struct for the colour red |
| `RL_GREEN` | `rlRGB` struct for the colour green |
| `RL_BLUE` | `rlRGB` struct for the colour blue |
| `RL_WHITE` | `rlRGB` struct for the colour white |
| `RL_BLACK` | `rlRGB` struct for the colour black |
| `RL_YELLOW` | `rlRGB` struct for the colour yellow |
| `RL_MAGENTA` | `rlRGB` struct for the colour magenta |
| `RL_CYAN` | `rlRGB` struct for the colour cyan |
| `RL_ORANGE` | `rlRGB` struct for the colour orange |
| `RL_PURPLE` | `rlRGB` struct for the colour purple |
| `RL_GRAY` | `rlRGB` struct for the colour gray |

---

### Functions
<details>
<summary>Click to view all Creating functions</summary>

`rlRGB rlrlRGB(unsigned char red, unsigned char green, unsigned char blue);`<br>
Takes the red value, the green value, and the blue value.<br>
Returns a new rlRGB struct.<br>
Alternatively, the macro `RGB(r,g,b)` can be used when declaring+initialising an rlRGB.

`void rlDefaultSettings(rlSettings *write);`<br>
Sets rlSettings to default values.<br>
Takes a pointer to where the settings will be written.

`void rlDefaultSettingsAdv(rlAdvancedSettings *write);`<br>
Sets rlAdvancedSettings to default values.<br>
Takes a pointer to where the settings will be written.

`void rlAdvance(rlAdvancedSettings *write, const rlSettings *settings);`<br>
Sets rlAdvancedSettings to the same values as rlSettings.<br>
Takes a pointer to where the advanced settings will be written, and a pointer to the settings.

</details>

<details>
<summary>Click to view all Calculations functions</summary>

`rlRGB rlHexToDec(const char hex[6]);`<br>
Takes a pointer to a hex code.<br>
Returns an RGB code struct, equivalent to the hex code.

`float rlDutyCycle(float output_voltage, float voltage_drop, float series_resistance, float power);`<br>
Takes the maximum output voltage going to the LED, the voltage drop across the LED, the series resistance of the LED, and the power desired to go to the LED.<br>
Returns the duty cycle needed for an amount of power, assuming common cathode.

`void rlDutyCyclesAdv(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rlAdvancedSettings *settings, rlRGB code);`<br>
Calculates the duty cycles needed to display an RGB colour.<br>
Takes a pointer to where the red duty cycle will be written, a pointer to where the green duty cycle will be written, a pointer to where the blue duty cycle will be written, the settings of the RGB LED, and the RGB code.

`void rlDutyCycles(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rlSettings *settings, rlRGB code);`<br>
Calculates the duty cycles needed to display an RGB colour.<br>
Takes a pointer to where the red duty cycle will be written, a pointer to where the green duty cycle will be written, a pointer to where the blue duty cycle will be written, the settings of the RGB LED, and the RGB code.

`void rlWriteValuesAdv(unsigned int *red, unsigned int *green, unsigned int *blue, const rlAdvancedSettings *settings, rlRGB code);`<br>
Calculates the integers (likely for PWM) needed to display an RGB colour.<br>
Takes a pointer to where the red integer will be written, a pointer to where the green integer will be written, a pointer to where the blue integer will be written, the settings of the RGB LED, and the RGB code.

`void rlWriteValues(unsigned int *red, unsigned int *green, unsigned int *blue, const rlSettings *settings, rlRGB code);`<br>
Calculates the integers (likely for PWM) needed to display an RGB colour.<br>
Takes a pointer to where the red integer will be written, a pointer to where the green integer will be written, a pointer to where the blue integer will be written, the settings of the RGB LED, and the RGB code.

`rlRGB rlLerp(rlRGB start, rlRGB end, float percentage);`<br>
Takes the start RGB code, the end RGB code, and a percentage from 0 to 1.<br>
Returns an RGB code that's the linear interpolation between two RGB codes.

`rlRGB rlHSVToRGB(float hue, float saturation, float value);`<br>
Takes the hue of the HSV code, the saturation of the HSV code, and the value of the HSV code.<br>
Returns an RGB code equivalent to the given HSV code.

</details>
