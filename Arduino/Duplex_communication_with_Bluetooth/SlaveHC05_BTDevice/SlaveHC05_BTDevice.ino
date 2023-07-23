// # Notice
// HC-05 module is used here.
/*

Pin config

+--------+-------------+
| HC-05  | Arduino UNO |
|--------+-------------+
| GND    | GND         |
| VCC    | 5V          |
| RXD    | pin 11      |
| TXD    | pin 10      |
+--------+-------------+

Disconnect the RX and TX pin of HC-05 from arduino before code upload and connect back after code upload.
use Arduino bluetooth Controller
By Tirtharaj Sinha




T0 Enter AT Command Mode
---------------------------

There is a pushbutton near to the EN pin of Bluetooth Module. Press that button and hold. Then connect the Arduino Uno to computer. Then release the button.

Then the LED on the Bluetooth Module start blinking with the inter well of 2 seconds. This indicates now the Bluetooth Module in command mode.

*/

#include <SoftwareSerial.h>

#define ledPin 13

SoftwareSerial EEBlue(10, 11);  // RX | TX
String MACadd = "30:C6:F7:14:ED:8A";

int data = 0;
char name[10] = "BTSlave";
char baud = '4';  //4 = 9600 baud


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);  //default baud rate for bt 38400
  EEBlue.begin(9600);
}
void loop() {
  if (EEBlue.available() > 0) {                 // Checks whether data is comming from the serial port
    String terminalText = EEBlue.readString();  // Reads the data from the Softserial port
    terminalText.trim();

    if (terminalText.substring(0) == "LED:0") {
      digitalWrite(ledPin, LOW);  // Turn LED OFF
      Serial.println("LED: OFF");
      EEBlue.println("LED: OFF");
    } else if (terminalText.substring(0) == "LED:1") {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED: ON");
      EEBlue.println("LED: ON");
    }
    else{
      Serial.println(terminalText);
      EEBlue.println(terminalText);
    }
  }
}
