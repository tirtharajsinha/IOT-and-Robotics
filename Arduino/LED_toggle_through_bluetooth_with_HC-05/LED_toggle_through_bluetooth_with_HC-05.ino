// # Notice
// HC-05 module is used here.
// Pin config
//+--------+-------------+
//| HC-05  | Arduino UNO |
//|--------+-------------+
//| GND    | GND         |
//| VCC    | 5V          |
//| RXD    | TX(pin 1)   |
//| TXD    | RX(Pin 0)   |
//+--------+-------------+

// Disconnect the RX and TX pin of HC-05 from arduino before code upload and connect back after code upload.
// use Arduino bluetooth Controller
// Tirtharaj Sinha


#define ledPin 13
int data = 0;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); //default baud rate for bt 38400
}
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    data = Serial.read(); // Reads the data from the serial port
    
          if (data == '0') {
            digitalWrite(ledPin, LOW); // Turn LED OFF
            Serial.println("LED: OFF"); 
            }
              else if (data == '1') {
                digitalWrite(ledPin, HIGH);
                Serial.println("LED: ON");
               
              } 
  }
}
