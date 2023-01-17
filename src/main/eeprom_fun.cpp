#include "eeprom_fun.h"

void writeStringToEEPROM(char* myString, int stringLen, int startAddress) {
  for(int i = 0; i < stringLen; i++) {
    EEPROM.write(startAddress + i, myString[i]);
  }
}

char* readStringFromEEPROM(int startAddress, int len) {
  char* readValue = (char*)calloc(len + 1, sizeof(char));
  if(!readValue) {
    Serial.println("Failed mem allocation");
  }

  int i;
  for(i = 0; i < len; i++) {
    char readChar;
    readChar = (char)EEPROM.read(startAddress + i);
    readValue[i] = readChar;
  }  
  readValue[i] = '\0'; //to be able to use String.h functions
  
  return readValue;
}

void retrieveEEPROMArrayOfStrings(int startAddress, int stringLen, int mode) {
  int nrOfElements;
  
  EEPROM.get(startAddress, nrOfElements);
  startAddress += sizeof(nrOfElements);
  if(mode == 0) {
    UIDStringsArray_size = nrOfElements; //update the global size
  }
  else {
    keyCodeStringsArraySize = nrOfElements;
  }

  for(int i = 0; i < nrOfElements; i++) {
      char* currReadString = readStringFromEEPROM(startAddress, stringLen);
      for(int j = 0; j < stringLen + 1; j++) { //add the string to the global array
        if(mode == 0) {
          UIDStringsArray[i][j] = currReadString[j];
        }
        else {
          keyCodeStringsArray[i][j] = currReadString[j];
        }
      }
    
      free(currReadString);
      startAddress += stringLen;
  }
}

void storeInitialCodes() {
  // UIDs
  char uid1[UID_LENGTH] = "31 1D 1C 1D";
  char uid2[UID_LENGTH] = "41 1D 1C 3D";
  int initialLen = 2;
  int currAddress = UIDs_START_ADDRESS;
  
  EEPROM.put(currAddress,initialLen);
  currAddress += sizeof(int);

  writeStringToEEPROM(uid1, UID_LENGTH, currAddress);
  currAddress += UID_LENGTH;

  writeStringToEEPROM(uid2, UID_LENGTH, currAddress);
  currAddress += UID_LENGTH;

  //Keycodes
  char keyCode1[KEY_CODE_LENGTH]="A792";
  char keyCode2[KEY_CODE_LENGTH]="0000";

  currAddress = KEY_CODEs_START_ADDRESS;
  EEPROM.put(currAddress,initialLen);
  currAddress += sizeof(int);

  writeStringToEEPROM(keyCode1, KEY_CODE_LENGTH, currAddress);
  currAddress += KEY_CODE_LENGTH;

  writeStringToEEPROM(keyCode2, KEY_CODE_LENGTH, currAddress);
  currAddress += KEY_CODE_LENGTH;
}

bool presentInUIDArray(String uid, int* index) {
  char charArrUID[UID_LENGTH + 1];
  uid.toCharArray(charArrUID, UID_LENGTH + 1);
  charArrUID[UID_LENGTH] = '\0';

  for(int i = 0; i < UIDStringsArray_size; i++){
    if(strcmp(charArrUID, UIDStringsArray[i]) == 0) {
      if(index) {
        *index = i;
      }
      
      return true;
    }
  }
  return false;
}

bool presentInKeyCodeArray(String readCode) {
  char charArrKey[KEY_CODE_LENGTH + 1];
  readCode.toCharArray(charArrKey, KEY_CODE_LENGTH + 1);
  charArrKey[KEY_CODE_LENGTH] = '\0';
  for(int i = 0; i < keyCodeStringsArraySize; i++) {
    if(strcmp(charArrKey, keyCodeStringsArray[i]) == 0) {
      return true;
    }
  }
  return false;
}

void updateMemory(int mode) {
  int startAddress;
  int arrSize;
  int wordSize;
  if(mode == 0) {
    startAddress = UIDs_START_ADDRESS;
    arrSize = UIDStringsArray_size;
    wordSize = UID_LENGTH;
  }
  else {
    startAddress = KEY_CODEs_START_ADDRESS;
    arrSize = keyCodeStringsArraySize;
    wordSize = KEY_CODE_LENGTH;
  }
  Serial.print("New size: ");
  Serial.println(arrSize);
  
  int currAddress = startAddress;
  
  EEPROM.put(currAddress, arrSize);
  currAddress += sizeof(int);

  
  if(mode == 0) {
    for(int i = 0; i < arrSize; i++) {
      writeStringToEEPROM(UIDStringsArray[i], wordSize, currAddress);
      currAddress += wordSize;
    }
  }
  else {
    for(int i = 0; i < arrSize; i++) {
      writeStringToEEPROM(keyCodeStringsArray[i], wordSize, currAddress);
      currAddress += wordSize;
    }
  }
}
