#include "rfid_fun.h"

bool processRFID(MFRC522 rfid) {
  if ( !rfid.PICC_IsNewCardPresent()) { 
    return false;
  }

  if ( !rfid.PICC_ReadCardSerial()) { //select one of the cards
    return false; 
  }

  String uid = retrieveCardUID(rfid);

  //TODO: compare with eeprom content
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
