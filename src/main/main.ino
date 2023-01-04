#include "configs.h"

/* GLOBALS */
volatile int awake;
volatile long prvMillisSleep = 0;
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);
MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); //RFID object
int curr_eeprom_address;
Servo myServo;
char UIDStringsArray[UID_ARR_MAX_SIZE][UID_LENGTH + 1]; //array of null-ended strings
int UIDStringsArray_size; //number of elements in the array

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
  lcd.print("Initialized ok");

  //EEPROM init
  curr_eeprom_address = EEPROM_START_ADDRESS;
  #ifdef INIT_EEPROM
  storeInitialCodes();   //store initial codes in eeprom
  #endif
  retrieveEEPROMArrayOfStrings(UIDs_START_ADDRESS, UID_LENGTH); //load eeprom data in UIDStringsArray

  //Servo init
  myServo.attach(SERVO_PIN);
  myServo.write(SERVO_CLOSE_ANGLE);
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
    setWelcomeMessage();
  }
}

/**
 * The system enters sleep mode (for f2f actions) SLEEP_AFTER_ms 
 */
void checkSleepMode() {
  long currMillis = millis();
  
  if((currMillis - prvMillisSleep >= SLEEP_AFTER_ms) && (awake == 1)) {
    awake = 0;
    writeLineToLcd(0, ASLEEP_MSG, true);
    prvMillisSleep = currMillis;
  }
}

void allowAccess() {
  writeLineToLcd(0, "Authorized access", true);
  myServo.write(SERVO_OPEN_ANGLE);
  delay(SERVO_DELAY);     
  myServo.write(SERVO_CLOSE_ANGLE);
  writeLineToLcd(0, "Authorized access", true);
}

void setWelcomeMessage() {
    writeLineToLcd(0, WELCOME_MSG_L1, true);
    writeLineToLcd(1, WELCOME_MSG_L2, false);
}

void loop() {  
  checkSleepMode();
  
  if(awake == 0) {
    checkProximity(); //need to check only if awake is 0, the sleep mode is induced by internal timers  
  }
  else { //only check for card if someone is close
    String uid = processRFID(mfrc522);
    if(!uid.equals("")) {
      if(presentInUIDArray(uid)) {
        prvMillisSleep = millis();
        allowAccess();
        setWelcomeMessage();
      }
      else {
        writeLineToLcd(0, "Access denied", true);
        delay(SERVO_DELAY);     
        setWelcomeMessage();
      }
    }
  }
}
