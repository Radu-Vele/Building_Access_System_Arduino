#include "keypad_fun.h"

void retrieveKeyCode(Keypad myKeypad, char initialKey) {
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
    }
  } while(gotKey != '#');
  // TODO: show * on lcd as user inputs code
  // TODO: add a timeout until the user can insert;
}
