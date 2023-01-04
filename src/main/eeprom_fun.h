#ifndef EEPROM_FUN_H
#define EEPROM_FUN_H
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_START_ADDRESS 0
//The array of recognized UIDs starts here with the number of elements (int x) followed by x strings of predefined length
#define UIDs_START_ADDRESS 256
#define UID_LENGTH 11
#define UID_ARR_MAX_SIZE 4

extern char UIDStringsArray[UID_ARR_MAX_SIZE][UID_LENGTH + 1];
extern int UIDStringsArray_size;

void writeStringToEEPROM(String string, int startAddress);

/**
 * Populates the UIDStringsArray from the EEPROM
 */
void retrieveEEPROMArrayOfStrings(int startAddress, int stringLen);

char* readStringFromEEPROM(int startAddress, int len);

/**
 * Configures the initial EEPROM content (factory)
 */
void storeInitialCodes();

bool presentInUIDArray(String uid);
#endif
