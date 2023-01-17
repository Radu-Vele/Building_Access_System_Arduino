#include "rfid_fun.h"

String processRFID(MFRC522 rfid) {
  if ( !rfid.PICC_IsNewCardPresent()) { 
    return "";
  }

  if ( !rfid.PICC_ReadCardSerial()) { //select one of the cards
    return ""; 
  }

  String uid = retrieveCardUID(rfid);
  return uid;
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
  
  return content.substring(1); 
}

/**
 * @brief Blocking function at the moment
 * 
 * @param rfid 
 */
String waitForCard(MFRC522 rfid) {
  //wait for user to add card
  String uid;
  while(true) {
    uid = processRFID(rfid);
    if(!uid.equals("")) {
      break;
    }
  }
  return uid;
}
