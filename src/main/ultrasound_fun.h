#ifndef ULTRASOUND_FUN_H
#define ULTRASOUND_FUN_H
#include <Arduino.h>

#define MIN_DISTANCE_CM 10
#define DELAY_US_MEASUREMENT 20
#define TRIG_SPEED 0.0340
//#define DEBUG_ON

/**
 * Returns the distance to nearby object in centimeters
 */
int getCurrentDistance(int trigPin, int echoPin);
bool userInProximity(int trigPin, int echoPin);

#endif
