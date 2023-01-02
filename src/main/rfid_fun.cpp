#include "rfid_fun.h"

// TODO: modify it to return a string
bool processRFID(MFRC522 rfid) {
  if ( !rfid.PICC_IsNewCardPresent()) { 
    return false;
  }

  if ( !rfid.PICC_ReadCardSerial()) { //select one of the cards
    return false; 
  }

  String uid = retrieveCardUID(rfid);

  //TODO: compare with eeprom content
  if(uid.equals(" 31 1D 1C 1D")) {
    return true;
  }
  else {
    return false;
  }
}

String retrieveCardUID(MFRC522 rfid) {
  String content= "";
  byte charRead;
  
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();

  #ifdef DEBUG_ON
  Serial.println(content);
  #endif
  
  return content;
}
