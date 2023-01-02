/**
 * Initial project version:
 * - the project starts in sleep mode
 * - the the program "wakes up" when the 
 */
#include <TimerOne.h>
#include "ultrasound_fun.h"

#define US_TRIG_PIN 6
#define US_ECHO_PIN 7

volatile int awake;

void setup() {
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
  awake = 0;
  
  Serial.begin(9600);
}

void loop() {
  int newAwake;
  if(userInProximity(US_TRIG_PIN, US_ECHO_PIN)){
    newAwake = 1;
  }
  else {
    newAwake = 0;
  }
  
  if(newAwake != awake) {
    Serial.println("Program state has changed");
  }

  awake = newAwake;
}
