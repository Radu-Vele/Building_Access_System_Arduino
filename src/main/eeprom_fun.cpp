#include "eeprom_fun.h"

void writeStringToEEPROM(char* myString, int stringLen, int startAddress) {
  for(int i = 0; i < stringLen; i++) {
    EEPROM.write(startAddress + i, myString[i]);
  }
}

char* readStringFromEEPROM(int startAddress, int len) {
  char* readValue = (char*)calloc(len, sizeof(char));
  if(!readValue) {
    Serial.print("Failed mem allocation");
  }

  for(int i = 0; i < len; i++) {
    char readChar;
    readChar = (char)EEPROM.read(startAddress + i);
    readValue[i] = readChar;
  }

  Serial.print("Read val as string:");
  
  return readValue;
}

void retrieveEEPROMArrayOfStrings(int startAddress, int stringLen, char UIDStringsArray[][]) {
  //read the int that tells the number of stored codes
  int nrOfElements;
  
  EEPROM.get(startAddress, nrOfElements);
  startAddress += sizeof(nrOfElements);

  Serial.println(nrOfElements);

  for(int i = 0; i < nrOfElements; i++) {
      char* currReadString = readStringFromEEPROM(startAddress, stringLen);
      
      for(int j = 0; j < stringLen; j++) {
        UIDStringsArray[i][j] = currReadString[j];
      }

      free(currReadString);

      for(int j = 0; j < stringLen; j++) {
        Serial.print(UIDStringsArray[i][j]);
      }

      
      startAddress += stringLen;
  }
}

void storeInitialCodes() {
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
}

void freeMemUIDArrContent() {
  
}
