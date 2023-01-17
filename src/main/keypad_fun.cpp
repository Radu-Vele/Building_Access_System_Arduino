#include "keypad_fun.h"

void configureScreen() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input pin (4)");
  lcd.setCursor(0, 1);
  lcd.print('*');
}

String retrieveKeyCode(Keypad myKeypad, char initialKey) {
  configureScreen();
  String keypadCode;
  keypadCode.reserve(4);
  keypadCode = "";
  keypadCode += initialKey;
  char gotKey;
  do {
    gotKey = myKeypad.getKey();
    if(gotKey) {
      if(gotKey != '#') {
        keypadCode += gotKey;
      }
      lcd.print('*');
    }
  } while(gotKey != '#');
  return keypadCode;
  // TODO: add a timeout until the user can insert;
}
