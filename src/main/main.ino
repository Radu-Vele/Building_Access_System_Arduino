#include "configs.h"

/* GLOBALS */
volatile int awake;
volatile long prvMillisSleep = 0;
int curr_eeprom_address;

// UID storage
char UIDStringsArray[UID_ARR_MAX_SIZE][UID_LENGTH + 1]; //array of null-ended strings
int UIDStringsArray_size; //number of elements in the array

//Key Codes storage
char keyCodeStringsArray[KEY_CODE_ARR_MAX_SIZE][KEY_CODE_LENGTH + 1];
int keyCodeStringsArraySize;

//Keypad settings
byte rowPins[numKeypadRows] = {R1, R2, R3, R4};
byte colPins[numKeypadCols]= {C1, C2, C3, C4};
char keymap[numKeypadRows][numKeypadCols] = {
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Bluetooth
String bluetoothCommandReceived = "";
bool bluetoothCommandComplete = false;
bool adminMode = false;

/* OBJECTS */
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);
MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN); //RFID object
Servo myServo;
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numKeypadRows, numKeypadCols);

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
  #ifdef INIT_EEPROM
  storeInitialCodes();   //store initial codes in eeprom
  #endif
  
  retrieveEEPROMArrayOfStrings(UIDs_START_ADDRESS, UID_LENGTH, 0); //load eeprom data in UIDStringsArray
  retrieveEEPROMArrayOfStrings(KEY_CODEs_START_ADDRESS, KEY_CODE_LENGTH, 1); //load eeprom data in Keycodes array

  //Servo init
  myServo.attach(SERVO_PIN);
  myServo.write(SERVO_CLOSE_ANGLE);

  //Bluetooth init
  Serial1.begin(9600);
  bluetoothCommandReceived.reserve(200);
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
}

void allowRemoteAccess() {
  writeLineToLcd(0, "Authorized access", true);
  writeLineToLcd(1, "Remote command!", false);
  myServo.write(SERVO_OPEN_ANGLE);
  delay(SERVO_DELAY);     
  myServo.write(SERVO_CLOSE_ANGLE);
}

void setWelcomeMessage() {
    writeLineToLcd(0, WELCOME_MSG_L1, true);
    writeLineToLcd(1, WELCOME_MSG_L2, false);
}

void serialEvent1() {
  String bluetoothInput;
  bluetoothInput = "";
  while(Serial1.available()) {
    char inChar = (char)Serial1.read();
    bluetoothCommandReceived += inChar;
    Serial.println(inChar);
    if(inChar == '\n') {
      bluetoothCommandComplete = true;
    }
  }
}

void parseBluetoothCommand() {
  if(bluetoothCommandReceived.startsWith("{user ")) {
    allowRemoteAccess();
    setWelcomeMessage();
  }
  else if(bluetoothCommandReceived.startsWith("{admin ")) {
    adminMode = true;
  }
}

void checkBluetoothCommand() {
    if(bluetoothCommandComplete) {
      Serial.println(bluetoothCommandReceived);
      parseBluetoothCommand();
      bluetoothCommandComplete = false;
      bluetoothCommandReceived = "";
    }
}

void userModeFlow() {
    checkBluetoothCommand();
    checkSleepMode();
    
    if(awake == 0) {
      checkProximity(); //need to check only if awake is 0, the sleep mode is induced by internal timers  
    }
    else { //only check for card or key if someone is close
      String uid = processRFID(mfrc522);
      if(!uid.equals("")) {
        if(presentInUIDArray(uid)) {
          prvMillisSleep = millis();
          allowAccess();
          setWelcomeMessage();
        }
        else {
          prvMillisSleep = millis();
          writeLineToLcd(0, "Access denied", true);
          delay(SERVO_DELAY);
          setWelcomeMessage();
        }
      }
  
      char key = myKeypad.getKey();
      if(key) {
        String keypadCode = retrieveKeyCode(myKeypad, key);
        if(presentInKeyCodeArray(keypadCode)) {
          prvMillisSleep = millis();
          allowAccess();
          setWelcomeMessage();
        }
        else {
          prvMillisSleep = millis();
          writeLineToLcd(0, "Access denied", true);
          delay(SERVO_DELAY);
          setWelcomeMessage();
        }
      }
    }
}

void adminModeFlow() {
  checkBluetoothCommand();
}

void loop() {
  if(adminMode) {
    adminModeFlow();
  }
  else {
    userModeFlow();
  } 
}
