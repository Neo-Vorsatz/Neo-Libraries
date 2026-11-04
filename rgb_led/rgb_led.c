/*
    RGB LED Library, for controlling RGB LEDs
    Implementation file
    Author: Neo Vorsatz
    Last updated: 4 November 2026
*/

// IMPORTS ================================

// External
#include <math.h>

// Internal
#include "rgb_led.h"

// CONSTANTS ================================

// Default settings
const rlSettings RL_DEFAULT_SETTINGS = {
    // Voltage drops
    RL_RED_VOLTAGE_DROP,
    RL_GREEN_VOLTAGE_DROP,
    RL_BLUE_VOLTAGE_DROP,
    // Series resistance
    RL_SERIES_RESISTANCE,
    // Output voltage
    RL_OUTPUT_VOLTAGE,
    // Maximum writable integer
    RL_MAX_INT,
    // Common Anode
    RL_COMMON_ANODE
};

// Default advanced settings
const rlAdvancedSettings RL_DEFAULT_ADVANCED_SETTINGS = {
    // Voltage drops
    RL_RED_VOLTAGE_DROP,
    RL_GREEN_VOLTAGE_DROP,
    RL_BLUE_VOLTAGE_DROP,
    // Series resistance
    RL_SERIES_RESISTANCE,
    RL_SERIES_RESISTANCE,
    RL_SERIES_RESISTANCE,
    // Output voltage
    RL_OUTPUT_VOLTAGE,
    RL_OUTPUT_VOLTAGE,
    RL_OUTPUT_VOLTAGE,
    // Maximum writable integer
    RL_MAX_INT,
    RL_MAX_INT,
    RL_MAX_INT,
    // Common Anode
    RL_COMMON_ANODE
};

// Colors
const rlRGB RL_RED = {255, 0, 0};
const rlRGB RL_GREEN = {0, 255, 0};
const rlRGB RL_BLUE = {0, 0, 255};
const rlRGB RL_WHITE = {255, 255, 255};
const rlRGB RL_BLACK = {0, 0, 0};
const rlRGB RL_YELLOW = {255, 255, 0};
const rlRGB RL_MAGENTA = {255, 0, 255};
const rlRGB RL_CYAN = {0, 255, 255};
const rlRGB RL_ORANGE = {255, 165, 0};
const rlRGB RL_PURPLE = {160, 32, 240};
const rlRGB RL_GRAY = {128, 128, 128};

// CREATING ================================

rlRGB rlRGBCode(unsigned char red, unsigned char green, unsigned char blue) {
    // Create new rgbCode struct
    rlRGB code = {red, green, blue};
    // Return
    return code;
}

void rlDefaultSettings(rlSettings *write) {
    // Set voltage drops
    write->red_voltage_drop = RL_RED_VOLTAGE_DROP;
    write->green_voltage_drop = RL_GREEN_VOLTAGE_DROP;
    write->blue_voltage_drop = RL_BLUE_VOLTAGE_DROP;
    // Set series resistance
    write->series_resistance = RL_SERIES_RESISTANCE;
    // Set output voltage
    write->output_voltage = RL_OUTPUT_VOLTAGE;
    // Set maximum writable integer
    write->max_int = RL_MAX_INT;
    // Set common anode
    write->common_anode = RL_COMMON_ANODE;
}

void rlDefaultSettingsAdv(rlAdvancedSettings *write) {
    // Set voltage drops
    write->red_voltage_drop = RL_RED_VOLTAGE_DROP;
    write->green_voltage_drop = RL_GREEN_VOLTAGE_DROP;
    write->blue_voltage_drop = RL_BLUE_VOLTAGE_DROP;
    // Set series resistances
    write->red_series_resistance = RL_SERIES_RESISTANCE;
    write->green_series_resistance = RL_SERIES_RESISTANCE;
    write->blue_series_resistance = RL_SERIES_RESISTANCE;
    // Set output voltages
    write->red_output_voltage = RL_OUTPUT_VOLTAGE;
    write->green_output_voltage = RL_OUTPUT_VOLTAGE;
    write->blue_output_voltage = RL_OUTPUT_VOLTAGE;
    // Set maximum writable integers
    write->red_max_int = RL_MAX_INT;
    write->green_max_int = RL_MAX_INT;
    write->blue_max_int = RL_MAX_INT;
    // Set common anode
    write->common_anode = RL_COMMON_ANODE;
}

void rlAdvance(rlAdvancedSettings *write, const rlSettings *settings) {
    // Set voltage drops
    write->red_voltage_drop = settings->red_voltage_drop;
    write->green_voltage_drop = settings->green_voltage_drop;
    write->blue_voltage_drop = settings->blue_voltage_drop;
    // Set series resistances
    write->red_series_resistance = settings->series_resistance;
    write->green_series_resistance = settings->series_resistance;
    write->blue_series_resistance = settings->series_resistance;
    // Set output voltages
    write->red_output_voltage = settings->output_voltage;
    write->green_output_voltage = settings->output_voltage;
    write->blue_output_voltage = settings->output_voltage;
    // Set maximum writable integers
    write->red_max_int = settings->max_int;
    write->green_max_int = settings->max_int;
    write->blue_max_int = settings->max_int;
    // Set common anode
    write->common_anode = settings->common_anode;
}

// CALCULATIONS ================================

rlRGB rlHexToDec(const char hex[6]) {
    // Check if hex code starts with '#'
    if (hex[0] == '#') {
        hex++; // skip over '#'
    }
    // Create array to store decimal values
    char dec[6];
    // Initialise variable to remember if the end of the string is found
    int end_of_string = 0;
    // Convert chars to decimals
    for (unsigned int i=0; i<6; i++) {
        // If the end of the string is found
        if (hex[i] == '\0') {
            end_of_string = 1;
        }
        // If the end of the string was ever found
        if (end_of_string) {
            dec[i] = 0;
            continue;
        }
        // If the char is a number
        if (hex[i] >= '0' && hex[i] <= '9') {
            dec[i] = hex[i] - '0';
        // If the char is an uppercase letter
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            dec[i] = hex[i] - 'A' + 10;
        // If the char is a lowercase letter
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            dec[i] = hex[i] - 'a' + 10;
        // The char is unrecognised
        } else {
            dec[i] = 0;
        }
    }
    // Create RGB code
    rlRGB code = {dec[0]*16+dec[1], dec[2]*16+dec[3], dec[4]*16+dec[5]};
    // Return
    return code;
}

float rlDutyCycle(float output_voltage, float voltage_drop, float series_resistance, float power) {
    // Calculate maximum current
    float current = (output_voltage - voltage_drop) / series_resistance;
    // Calculate duty cycle
    float duty_cycle = power / (voltage_drop * current);
    // Return
    return duty_cycle;
}

/**
 * @param output_voltage The maximum output voltage going to the LED
 * @param voltage_drop The voltage drop across the LED
 * @param series_resistance The series resistance of the LED
 * @param duty_cycle The duty cycle going to the LED
 * 
 * @return The amount of power going to the LED, assuming common cathode
 */
static float rlPower(float output_voltage, float voltage_drop, float series_resistance, float duty_cycle) {
    // Calculate maximum current
    float current = (output_voltage - voltage_drop) / series_resistance;
    // Calculate power
    float power = voltage_drop * current * duty_cycle;
    // Return
    return power;
}

/**
 * @param settings The settings of the RGB LED
 * 
 * @return The maximum power, of the LED that receives the least power
 */
static float rlMaxPowerAdv(const rlAdvancedSettings *settings) {
    // Calculate the power of the red LED
    float red_power = rlPower(settings->red_output_voltage, settings->red_voltage_drop, settings->red_series_resistance, 1.0);
    // Calculate the power of the green LED
    float green_power = rlPower(settings->green_output_voltage, settings->green_voltage_drop, settings->green_series_resistance, 1.0);
    // Calculate the power of the blue LED
    float blue_power = rlPower(settings->blue_output_voltage, settings->blue_voltage_drop, settings->blue_series_resistance, 1.0);
    // Return the minimum of maximum powers
    return fmin(red_power, fmin(green_power, blue_power));
}

void rlDutyCyclesAdv(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rlAdvancedSettings *settings, rlRGB code) {
    // Calculate the maximum power
    float max_power = rlMaxPowerAdv(settings);
    // Calculate the red duty cycle
    float power = max_power*((float)code.red) / 255.0f;
    *red_duty_cycle = rlDutyCycle(settings->red_output_voltage, settings->red_voltage_drop, settings->red_series_resistance, power);
    // Calculate the green duty cycle
    power = max_power*((float)code.green) / 255.0f;
    *green_duty_cycle = rlDutyCycle(settings->green_output_voltage, settings->green_voltage_drop, settings->green_series_resistance, power);
    // Calculate the blue duty cycle
    power = max_power*((float)code.blue) / 255.0f;
    *blue_duty_cycle = rlDutyCycle(settings->blue_output_voltage, settings->blue_voltage_drop, settings->blue_series_resistance, power);
    // Invert the duty cycles if common anode
    if (settings->common_anode) {
        *red_duty_cycle = 1.0f - *red_duty_cycle;
        *green_duty_cycle = 1.0f - *green_duty_cycle;
        *blue_duty_cycle = 1.0f - *blue_duty_cycle;
    }
}

void rlDutyCycles(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rlSettings *settings, rlRGB code) {
    // Create an advanced version of the settings
    rlAdvancedSettings advanced_settings;
    rlAdvance(&advanced_settings, settings);
    // Call the advanced function
    rlDutyCyclesAdv(red_duty_cycle, green_duty_cycle, blue_duty_cycle, &advanced_settings, code);
}

void rlWriteValuesAdv(unsigned int *red, unsigned int *green, unsigned int *blue, const rlAdvancedSettings *settings, rlRGB code) {
    // Calculate the duty cycles for each colour
    float red_duty_cycle, green_duty_cycle, blue_duty_cycle;
    rlDutyCyclesAdv(&red_duty_cycle, &green_duty_cycle, &blue_duty_cycle, settings, code);
    // Convert to integer values
    *red = (unsigned int)(red_duty_cycle * settings->red_max_int);
    *green = (unsigned int)(green_duty_cycle * settings->green_max_int);
    *blue = (unsigned int)(blue_duty_cycle * settings->blue_max_int);
}

void rlWriteValues(unsigned int *red, unsigned int *green, unsigned int *blue, const rlSettings *settings, rlRGB code) {
    // Create an advanced version of the settings
    rlAdvancedSettings advanced_settings;
    rlAdvance(&advanced_settings, settings);
    // Call the advanced function
    rlWriteValuesAdv(red, green, blue, &advanced_settings, code);
}

rlRGB rlLerp(rlRGB start, rlRGB end, float percentage) {
    rlRGB lerp;
    lerp.red = (unsigned char)(start.red + (end.red - start.red) * percentage);
    lerp.green = (unsigned char)(start.green + (end.green - start.green) * percentage);
    lerp.blue = (unsigned char)(start.blue + (end.blue - start.blue) * percentage);
    return lerp;
}

rlRGB rlHSVToRGB(float hue, float saturation, float value) {
    // Check for achromatic (gray) colour
    if (saturation <= 0.0f) {
        rlRGB code = {(unsigned char)(value * 255), (unsigned char)(value * 255), (unsigned char)(value * 255)};
        return code;
    }

    // Get the hue sector
    float div_60 = hue / 60.0f;
    int sector = floor(div_60);
    // Get the fractional portion
    float frac = div_60 - sector;
    // Get the inverse of the saturation (it's used a lot)
    float inverse = 1.0f - saturation;
    // Calculate the RGB values
    unsigned char primary_colour = 255 * value; // value of the colour mainly responsible for the hue
    unsigned char secondary_colour; // value of the colour assisting in hue
    if (sector % 2 == 0) { // if the secondary colour is on an ascending sector, w.r.t. hue
        secondary_colour = 255 * value * ( inverse + (saturation * frac) );
    } else { // the secondary colour is on an ascending sector, w.r.t. hue
        secondary_colour = 255 * value * ( inverse + (saturation * (1.0f - frac)) );
    }
    unsigned char tertiary_colour = 255 * value * inverse; // value of the colour responsible for whitening

    // Create the RGB code
    rlRGB code;
    switch (sector % 6) {
        case 0:
            code.red = primary_colour;
            code.green = secondary_colour;
            code.blue = tertiary_colour;
            break;
        case 1:
            code.red = secondary_colour;
            code.green = primary_colour;
            code.blue = tertiary_colour;
            break;
        case 2:
            code.red = tertiary_colour;
            code.green = primary_colour;
            code.blue = secondary_colour;
            break;
        case 3:
            code.red = tertiary_colour;
            code.green = secondary_colour;
            code.blue = primary_colour;
            break;
        case 4:
            code.red = secondary_colour;
            code.green = tertiary_colour;
            code.blue = primary_colour;
            break;
        case 5:
            code.red = primary_colour;
            code.green = tertiary_colour;
            code.blue = secondary_colour;
            break;
    }
    return code;
}
