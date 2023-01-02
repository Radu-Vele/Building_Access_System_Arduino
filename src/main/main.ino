#include "ultrasound_fun.h"
#include "rfid_fun.h"

#define US_TRIG_PIN 6
#define US_ECHO_PIN 7

#define RFID_SS_PIN 53
#define RFID_RST_PIN 5

#define SLEEP_AFTER_ms 20000

volatile int awake;
volatile long prvMillisSleep = 0;

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); //RFID object

void setup() {
  // Ultrasound init
  pinMode(US_TRIG_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);

  // RFID init
  SPI.begin();
  mfrc522.PCD_Init();

  // Program state
  awake = 0;
  
  // Serial monitor
  Serial.begin(9600);
}


void checkProximity() {
  if(userInProximity(US_TRIG_PIN, US_ECHO_PIN)){
    awake = 1;
    prvMillisSleep = millis();
    Serial.println("Welcome dear guest! Scan your card!");
  }
}

/**
 * The program system enters sleep mode (for f2f actions) SLEEP_AFTER_ms 
 */
void checkSleepMode() {
  long currMillis = millis();
  
  if((currMillis - prvMillisSleep >= SLEEP_AFTER_ms) && (awake == 1)) {
    awake = 0;
    Serial.println("Entering sleep...");
    prvMillisSleep = currMillis;
  }
}

void loop() {

  checkSleepMode();
  
  if(awake == 0) {
    checkProximity(); //need to check only if awake is 0, the sleep mode is induced by internal timers  
  }
  else {
    processRFID(mfrc522); //only check for card if someone is close
  }
}
