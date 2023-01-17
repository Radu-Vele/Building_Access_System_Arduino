#include <Servo.h>

int servoPin = 5;
Servo servoObj;

void setup() {
  servoObj.attach(servoPin );
  servoObj.write(0);
}

void loop() {
  servoObj.write(90);
  delay(1000);
  servoObj.write(150);
  delay(1000);
  servoObj.write(0);
  delay(1000);
}
