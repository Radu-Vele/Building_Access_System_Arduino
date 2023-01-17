#ifndef KEYPAD_FUN_H
#define KEYPAD_FUN_H
#include <Keypad.h>
#include "configs.h"

#define R1 30
#define R2 31
#define R3 32
#define R4 33

#define C1 34
#define C2 35
#define C3 36
#define C4 37

#define numKeypadRows 4
#define numKeypadCols 4
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;
String retrieveKeyCode(Keypad myKeypad, char initialKey);
void configureScreen();
#endif
