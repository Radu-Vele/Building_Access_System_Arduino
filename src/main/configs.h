#ifndef CONFIGS_H
#define CONFIGS_H
#include <Arduino.h>
#include "eeprom_fun.h"
#include "ultrasound_fun.h"
#include "rfid_fun.h"
#include "keypad_fun.h"
#include <LiquidCrystal_I2C.h>
#include <Keypad.h> 
#include <Servo.h>

#define US_TRIG_PIN 6
#define US_ECHO_PIN 7

#define RFID_SS_PIN 53
#define RFID_RST_PIN 5

#define I2C_ADDR 0x27           //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3         // Declaring LCD Pins

#define SLEEP_AFTER_ms 10000
#define WELCOME_MSG_L1 "Welcome!"
#define WELCOME_MSG_L2 "Scan your card!"
#define ASLEEP_MSG "Zzz..."
#define ERR_AUTH "ERR Auth"
#define ERR_ALREADY_IN "ERR AlreadyIn"
#define ERR_NOT_PRESENT "ERR UID Not Present"
#define ERR_PASSW "ERR Password not correct"
#define ADMIN_SUCC_MSG "SUCC Welcome, dear Admin!"
#define USER_SUCC_MSG "SUCC Welcome, dear User!"
 
//#define INIT_EEPROM

#define SERVO_PIN 3
#define SERVO_OPEN_ANGLE 90
#define SERVO_CLOSE_ANGLE 0
#define SERVO_DELAY 1000
#endif
