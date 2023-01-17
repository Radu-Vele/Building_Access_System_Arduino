void setup()
{
Serial.begin(9600); // Serial 0 interface for PC
Serial1.begin(9600); // Serial 1 interface for Bluetooth module
}
void loop()
{
if (Serial1.available()) // Read from Bluetooth and send to PC
Serial.write(Serial1.read());
if (Serial.available()) // Read from PC and send to Bluetooth
Serial1.write(Serial.read());
}
