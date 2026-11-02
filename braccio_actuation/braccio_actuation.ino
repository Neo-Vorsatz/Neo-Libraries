/*
    Program to test the Braccio actuation library 
    Author: Neo Vorsatz
    Last updated: 2 November 2026
*/

#include <Arduino.h>
#include "braccio_actuation.h"

void doMotions() {
    // Test non-blocking incrementing method
    vector_t target = baNewVector(
        90.0f, // base <- forward
        90.0f, // joint1 <- upward
        90.0f, // joint2 <- upward
        90.0f, // joint3 <- upward
        90.0f, // wrist <- neutral
        180.0f // claw <- closed
    );
    baUpdateTarget(target);
    while (!baAtTarget()) {
        baStep(); // move the Braccio arm incrementally towards the target
    }
    delay(2000);
    
    // Test blocking movement
    target = baNewVector(
        0.0f, // base <- left
        180.0f, // joint1 <- forward
        0.0f, // joint2 <- backward
        180.0f, // joint3 <- forward
        180.0f, // wrist <- left
        0.0f // claw <- open
    );
    baMove(target);
    delay(2000);

    // Test aggressive movement
    target = baNewVector(
        90.0f, // base <- forward
        0.0f, // joint1 <- backward
        180.0f, // joint2 <- forward
        0.0f, // joint3 <- forward
        90.0f, // wrist <- neutral
        180.0f // claw <- closed
    );
    baSetPosition(target);
    delay(2000);
}

void setup() {
    // Initialize arm
    if (!baInit()) {
        while (1); // stop the program
    }
    delay(2000);
}

void loop() {
    // Test movements
    doMotions();

    // Test movements faster
    baSetFilterTau(0.1f);
    doMotions();

    // Test movements slower
    baSetFilterFreq(0.265f);
    doMotions();

    // Reset speed
    baSetFilterTau(0.333f);
}
