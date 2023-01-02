#include "ultrasound_fun.h"
#include "rfid_fun.h"
#include <LiquidCrystal_I2C.h>

#define US_TRIG_PIN 6
#define US_ECHO_PIN 7

#define RFID_SS_PIN 53
#define RFID_RST_PIN 5

#define I2C_ADDR 0x27           //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3         // Declaring LCD Pins

#define SLEEP_AFTER_ms 10000

volatile int awake;
volatile long prvMillisSleep = 0;

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

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

  //LCD init
  lcd.init();
  lcd.backlight(); //Lighting backlight
  lcd.setCursor(0,0);
  lcd.print("Initialized ok");      //What's written on the LCD you can change
          
}

void writeLineToLcd(int lineNr, String text, bool clscr) {
  if(clscr) {
    lcd.clear();
  }
  lcd.setCursor(0, lineNr);
  lcd.print(text);
}

void checkProximity() {
  if(userInProximity(US_TRIG_PIN, US_ECHO_PIN)){
    awake = 1;
    prvMillisSleep = millis();
    
    writeLineToLcd(0, "Welcome!", true);
    writeLineToLcd(1, "Scan your card!", false);
  }
}

/**
 * The system enters sleep mode (for f2f actions) SLEEP_AFTER_ms 
 */
void checkSleepMode() {
  long currMillis = millis();
  
  if((currMillis - prvMillisSleep >= SLEEP_AFTER_ms) && (awake == 1)) {
    awake = 0;
    writeLineToLcd(0, "Zzz...", true);
    prvMillisSleep = currMillis;
  }
}

void loop() {

  checkSleepMode();
  
  if(awake == 0) {
    checkProximity(); //need to check only if awake is 0, the sleep mode is induced by internal timers  
  }
  else { //only check for card if someone is close
    if(processRFID(mfrc522)) {
      writeLineToLcd(0, "Authorized access", true);
    }
  }
}
