#ifndef EEPROM_FUN_H
#define EEPROM_FUN_H
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_START_ADDRESS 0
#define UIDs_START_ADDRESS 256
#define UID_LENGTH 11
#define UID_ARR_MAX_SIZE 4


void writeStringToEEPROM(String string, int startAddress);
void retrieveEEPROMArrayOfStrings(int startAddress, int stringLen, char UIDStringsArray[][]);
char* readStringFromEEPROM(int startAddress, int len);
void storeInitialCodes();
void freeMemUIDArrContent();
#endif
