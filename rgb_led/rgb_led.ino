// Programme to test the RGB LED library
// by Neo Vorsatz
// Last updated: 29 May 2026

#include <Arduino.h>
#include "rgb_led.h"

//Pin assignments
#define PIN_RED   9
#define PIN_GREEN 10
#define PIN_BLUE  11

void writeColour(rgbCode code) {
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
  //Testing solid colours
  writeColour(RL_RED); //Red for 1 second
  delay(1000);
  writeColour(rlHexToDec("00FF00")); //Green for 1 second
  delay(1000);
  writeColour(rlRGBCode(0, 0, 255)); //Blue for 1 second
  delay(1000);

  //Rainbow cycle
  for (float hue=0.0f; hue<360.0f; hue+=1.0f) {
    rgbCode colour = rlHSVToRGB(hue, 1.0f, 1.0f);
    writeColour(colour);
    delay(20);
  }

  //Ramp up: black to white
  for (float value=0.0f; value<1.0f; value+=0.01f) {
    rgbCode colour = rlHSVToRGB(0.0f, 0.0f, value);
    writeColour(colour);
    delay(50);
  }

  //Ramp down: white to black
  for (float value=1.0f; value>0.0f; value-=0.01f) {
    rgbCode colour = rlHSVToRGB(0.0f, 0.0f, value);
    writeColour(colour);
    delay(50);
  }

  //Interpolate: red to blue
  for (float progress=0.0f; progress<1.0f; progress+=0.01f) {
    rgbCode colour = rlLerp(RL_RED, RL_BLUE, progress);
    writeColour(colour);
    delay(50);
  }

  //Interpolate: blue to yellow
  for (float progress=0.0f; progress<1.0f; progress+=0.01f) {
    rgbCode colour = rlLerp(RL_BLUE, RL_YELLOW, progress);
    writeColour(colour);
    delay(50);
  }

  //Interpolate: yellow to gray
  for (float progress=0.0f; progress<1.0f; progress+=0.01f) {
    rgbCode colour = rlLerp(RL_YELLOW, RL_GRAY, progress);
    writeColour(colour);
    delay(20);
  }

  //Pause
  rgbCode off = RGB(0, 0, 0);
  writeColour(off);
  delay(1000);
}
