#include "ultrasound_fun.h"

/**
 * TODO: Might be useful to buffer a few readings (something like a debouncer)
 */
int getCurrentDistance(int trigPin, int echoPin) {
  
  //trigger signal emitted
  digitalWrite(trigPin, LOW);
  delayMicroseconds(DELAY_US_MEASUREMENT);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(DELAY_US_MEASUREMENT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(DELAY_US_MEASUREMENT);

  int time = pulseIn(echoPin, HIGH); //read reflected signal
  int distance = time * TRIG_SPEED / 2; //distance = time * speed 

  #ifdef DEBUG_ON
  Serial.println("Current Distance: ");
  Serial.println(distance);
  #endif

  return distance;
}

bool userInProximity(int trigPin, int echoPin) {
  return (getCurrentDistance(trigPin, echoPin) <= MIN_DISTANCE_CM);
}
