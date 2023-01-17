#ifndef EEPROM_FUN_H
#define EEPROM_FUN_H
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_START_ADDRESS 0 //The array of recognized UIDs starts here with the number of elements (int x) followed by x strings of predefined length
#define UIDs_START_ADDRESS 256
#define UID_LENGTH 11
#define UID_ARR_MAX_SIZE 10
#define KEY_CODEs_START_ADDRESS 512
#define KEY_CODE_LENGTH 4
#define KEY_CODE_ARR_MAX_SIZE 10

extern char UIDStringsArray[UID_ARR_MAX_SIZE][UID_LENGTH + 1];
extern int UIDStringsArray_size;

extern char keyCodeStringsArray[KEY_CODE_ARR_MAX_SIZE][KEY_CODE_LENGTH + 1];
extern int keyCodeStringsArraySize;

void writeStringToEEPROM(String string, int startAddress);

/**
 * Populates the UIDStringsArray from the EEPROM
 * 
 * @param
 *  * mode - 0 for UID retrieval
 *         - 1 for keyCode retrieval
 */
void retrieveEEPROMArrayOfStrings(int startAddress, int stringLen,  int mode);

char* readStringFromEEPROM(int startAddress, int len);

/**
 * Configures the initial EEPROM content (factory)
 */
void storeInitialCodes();

// Check if receive input is present in the EEPROM
bool presentInUIDArray(String uid, int* index);
bool presentInKeyCodeArray(String readCode);

/**
 * Overwrite memory with the new version of the array of data
 */
void updateMemory(int mode);
#endif
