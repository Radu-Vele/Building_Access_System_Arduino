#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


#define I2C_ADDR 0x27           //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3         // Declaring LCD Pins
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define ServoPin 3

Servo srv ;

const byte numRows= 4;          //number of rows on the keypad
const byte numCols= 4;          //number of columns on the keypad

 String receivedCode = ""; 

char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

char keypressed;                 //Where the keys are stored it changes very often
String code= "6601";  //The default code, you can change it or make it a 'n' digits one

short a=0,i=0,s=0,j=0;          //Variables used later

byte rowPins[numRows] = {30,31,32,33}; //Rows 0 to 3 //if you modify your pins you should modify this too
byte colPins[numCols]= {34,35,36,37}; //Columns 0 to 3

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void OpenDoor(){             //Lock opening function open for 3s
  srv.write(90);
}

void setup() {
          Serial.begin(9600);
          srv.attach(ServoPin);
          srv.write(0);
          lcd.init ();
          lcd.backlight(); //Lighting backlight
          lcd.print("Standby");      //What's written on the LCD you can change
}

void loop(){
  keypressed = myKeypad.getKey();               //Constantly waiting for a key to be pressed
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter code");            //Message to show
  GetCode();                          //Getting code function
  if(receivedCode.equals(code)){           //The GetCode function assign a value to a (it's correct when it has the size of the code array)
    OpenDoor();  
  }
  else {//Open lock function if code is correct
    lcd.clear();               
    lcd.print("Wrong");          //Message to print when the code is wrong
    delay(2000);
  }
  lcd.clear();
  lcd.print("Standby");             //Return to standby mode it's the message do display when waiting       
}

void GetCode(){ //Getting code sequence
  i=0; //All variables set to 0
  a=0;
  j=0; 
  receivedCode = "";                            
  while(keypressed != 'A'){                                     //The user press A to confirm the code otherwise he can keep typing
    keypressed = myKeypad.getKey();   
    
    Serial.print(keypressed);                      
    if(keypressed != NO_KEY && keypressed != 'A' ){       //If the char typed isn't A and neither "nothing"
      lcd.setCursor(j,1);                                  //This to write "*" on the LCD whenever a key is pressed it's position is controlled by j
      lcd.print("*");
      j++;
    }
    
    receivedCode += keypressed;
 }

  keypressed = NO_KEY;
}
