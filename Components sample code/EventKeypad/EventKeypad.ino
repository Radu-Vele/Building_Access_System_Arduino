/* @file EventSerialKeypad.pde
 || @version 1.0
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
 || #
 */
#include <Keypad.h>
#define R1 30
#define R2 31
#define R3 32
#define R4 33

#define C1 34
#define C2 35
#define C3 36
#define C4 37

const byte numKeypadRows = 4; //four rows
const byte numKeypadCols = 4; //three columns


char keymap[numKeypadRows][numKeypadCols] = {
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[numKeypadRows] = {R1, R2, R3, R4};
byte colPins[numKeypadCols]= {C1, C2, C3, C4};

Keypad keypad = Keypad( makeKeymap(keymap), rowPins, colPins, numKeypadRows, numKeypadCols );
byte ledPin = 13; 

boolean blink = false;
boolean ledPin_state;

void setup(){
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
    digitalWrite(ledPin, HIGH);           // Turn the LED on.
    ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop(){
    char key;// = keypad.getKey();

    if (key) {
        Serial.println(key);
    }
    if (blink){
        digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
        delay(100);
    }
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    Serial.println("Event!");
}
