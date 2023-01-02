/*
 * Connection:
 * - SDA: 53
 * - SCK: 52
 * - MOSI: 51
 * - MISO: 50
 * - GND: GND
 * - RST: 5
 * - VCC: 3.3V
 */
#ifndef RFID_FUN_H
#define RFID_FUN_H
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

//#define DEBUG_ON

/**
 * Process RFID card:
 * - check for presence (not present => false)
 * - compare with EEPROM content to return true if the UID is recognized
*/
bool processRFID(MFRC522 rfid);
String retrieveCardUID(MFRC522 rfid);
#endif
