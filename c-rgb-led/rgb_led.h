// RGB LED Library, for controlling RGB LEDs
// Header file
// by Neo Vorsatz
// Last updated: 11 February 2026

//Header guard
#ifndef RGB_LED_H
#define RGB_LED_H

//Includes
#include <stdbool.h>

//C++ compatibility
#ifdef __cplusplus
  extern "C" {
#endif

/* EDIT WITH MACROS ================================*/

#ifndef RL_RED_VOLTAGE_DROP
  #define RL_RED_VOLTAGE_DROP 2.0f //Default value of voltage drop across red LED
#endif

#ifndef RL_GREEN_VOLTAGE_DROP
  #define RL_GREEN_VOLTAGE_DROP 3.2f //Default value of voltage drop across green LED
#endif

#ifndef RL_BLUE_VOLTAGE_DROP
  #define RL_BLUE_VOLTAGE_DROP 3.1f //Default value of voltage drop across blue LED
#endif

#ifndef RL_SERIES_RESISTANCE
  #define RL_SERIES_RESISTANCE 100.0f //Default value of series resistance
#endif

#ifndef RL_OUTPUT_VOLTAGE
  #define RL_OUTPUT_VOLTAGE 5.0f //Default value of output voltage
#endif

#ifndef RL_MAX_INT
  #define RL_MAX_INT 255 //Default value of maximum writable integer
#endif

#ifndef RL_COMMON_ANODE
  #define RL_COMMON_ANODE false //Default boolean if common anode LEDs are used
#endif

/*================================*/
/* CONSTANTS ================================*/

//Settings
extern const rgbSettings RL_DEFAULT_SETTINGS;
extern const rgbAdvancedSettings RL_DEFAULT_ADVANCED_SETTINGS;

//Colours
extern const rgbCode RL_RED;
extern const rgbCode RL_GREEN;
extern const rgbCode RL_BLUE;
extern const rgbCode RL_WHITE;
extern const rgbCode RL_BLACK;
extern const rgbCode RL_YELLOW;
extern const rgbCode RL_MAGENTA;
extern const rgbCode RL_CYAN;
extern const rgbCode RL_ORANGE;
extern const rgbCode RL_PURPLE;
extern const rgbCode RL_GRAY;

/*================================*/
/* TYPE DEFINITIONS ================================*/

//Structure for a RGB code
typedef struct {
  unsigned char red; //Red value
  unsigned char green; //Green value
  unsigned char blue; //Blue value
} rgbCode;

//Structure for simple settings of a RGD LED
typedef struct {
  //Voltage drops
  float red_voltage_drop; //Voltage drop across red LED
  float green_voltage_drop; //Voltage drop across green LED
  float blue_voltage_drop; //Voltage drop across blue LED
  //Series resistance
  float series_resistance; //Series resistance for all LEDs
  //Output voltage
  float output_voltage; //Output voltage for all LEDs
  //Maximum writable integer
  unsigned int max_int; //Maximum writable integer for all LEDs
  //Common Anode
  bool common_anode;
} rgbSettings;

//Structure for advanced settings of a RGB LED
typedef struct {
  //Voltage drops
  float red_voltage_drop; //Voltage drop across red LED
  float green_voltage_drop; //Voltage drop across green LED
  float blue_voltage_drop; //Voltage drop across blue LED
  //Series resistances
  float red_series_resistance; //Series resistance of red LED
  float green_series_resistance; //Series resistance of green LED
  float blue_series_resistance; //Series resistance of blue LED
  //Output voltage
  float red_output_voltage; //Output voltage for red LED
  float green_output_voltage; //Output voltage for green LED
  float blue_output_voltage; //Output voltage for blue LED
  //Maximum writable integer
  unsigned int red_max_int; //Maximum writable integer for read LED
  unsigned int green_max_int; //Maximum writable integer for green LED
  unsigned int blue_max_int; //Maximum writable integer for blue LED
  //Common Anode
  bool common_anode;
} rgbAdvancedSettings;

/*================================*/
/* CREATING ================================*/

/**
 * @param red The red value
 * @param green The green value
 * @param blue The blue value
 * 
 * @return A new rgbCode struct
 */
rgbCode rlRGBCode(unsigned char red, unsigned char green, unsigned char blue);

//Allows users to do: rgbCode myColor = RGB(100, 50, 200);
#define RGB(r,g,b) (rgbCode){(unsigned char)(r),(unsigned char)(g),(unsigned char)(b)}

/**
 * @brief Sets rgbSettings to default values
 * 
 * @param write A pointer to where the settings will be written
 */
void rlDefaultSettings(rgbSettings *write);

/**
 * @brief Sets rgbAdvancedSettings to default values
 * 
 * @param write A pointer to where the settings will be written
 */
void rlDefaultSettingsAdv(rgbAdvancedSettings *write);

/**
 * @brief Sets rgbAdvancedSettings to the same values as rgbSettings
 * 
 * @param write A pointer to where the advanced settings will be written
 * @param settings A pointer to the settings
 */
void rlAdvance(rgbAdvancedSettings *write, const rgbSettings *settings);

/*================================*/
/* CALCULATIONS ================================*/

/**
 * @param hex A pointer to a hex code
 * 
 * @return An RGB code struct, equivalent to the hex code
 */
rgbCode rlHexToDec(const char hex[6]);

/**
 * @param output_voltage The maximum output voltage going to the LED
 * @param voltage_drop The voltage drop across the LED
 * @param series_resistance The series resistance of the LED
 * @param power The power desired to go to the LED
 * 
 * @return The duty cycle needed for an amount of power, assuming common cathode
 */
float rlDutyCycle(float output_voltage, float voltage_drop, float series_resistance, float power);

/**
 * @brief Calculates the duty cycles needed to display an RGB colour
 * 
 * @param red_duty_cycle A pointer to where the red duty cycle will be written
 * @param green_duty_cycle A pointer to where the green duty cycle will be written
 * @param blue_duty_cycle A pointer to where the blue duty cycle will be written
 * @param settings The settings of the RGB LED
 * @param code The RGB code
 */
void rlDutyCyclesAdv(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rgbAdvancedSettings *settings, rgbCode code);

/**
 * @brief Calculates the duty cycles needed to display an RGB colour
 * 
 * @param red_duty_cycle A pointer to where the red duty cycle will be written
 * @param green_duty_cycle A pointer to where the green duty cycle will be written
 * @param blue_duty_cycle A pointer to where the blue duty cycle will be written
 * @param settings The settings of the RGB LED
 * @param code The RGB code
 */
void rlDutyCycles(float *red_duty_cycle, float *green_duty_cycle, float *blue_duty_cycle, const rgbSettings *settings, rgbCode code);

/**
 * @brief Calculates the integers (likely for PWM) needed to display an RGB colour
 * 
 * @param red A pointer to where the red integer will be written
 * @param green A pointer to where the green integer will be written
 * @param blue A pointer to where the blue integer will be written
 * @param settings The settings of the RGB LED
 * @param code The RGB code
 */
void rlWriteValuesAdv(unsigned int *red, unsigned int *green, unsigned int *blue, const rgbAdvancedSettings *settings, rgbCode code);

/**
 * @brief Calculates the integers (likely for PWM) needed to display an RGB colour
 * 
 * @param red A pointer to where the red integer will be written
 * @param green A pointer to where the green integer will be written
 * @param blue A pointer to where the blue integer will be written
 * @param settings The settings of the RGB LED
 * @param code The RGB code
 */
void rlWriteValues(unsigned int *red, unsigned int *green, unsigned int *blue, const rgbSettings *settings, rgbCode code);

/**
 * @param start The start RGB code
 * @param end The end RGB code
 * @param percentage A percentage from 0 to 1
 * 
 * @return An RGB code that's the linear interpolation between two RGB codes
 */
rgbCode rlLerp(rgbCode start, rgbCode end, float percentage);

/**
 * @param hue The hue of the HSV code
 * @param saturation The saturation of the HSV code
 * @param value The value of the HSV code
 * 
 * @return An RGB code equivalent to the given HSV code
 */
rgbCode rlHSVToRGB(float hue, float saturation, float value);

/*================================*/

#ifdef __cplusplus
  }
#endif

#endif