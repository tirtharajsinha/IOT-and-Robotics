/*
Popular commands

AT : Ceck the connection. 
AT+NAME? : See default name 
AT+ADDR? : see default address 
AT+VERSION? : See version 
AT+UART? : See baudrate 
AT+ROLE?: See role of bt module(1=master/0=slave) 
AT+RESET? : Reset and exit AT mode 
AT+ORGL? : Restore factory settings 
AT+PSWD?: see default password

SET command as 
AT+NAME=MY-BT

*/


#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN

void setup() 
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH); 
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}


