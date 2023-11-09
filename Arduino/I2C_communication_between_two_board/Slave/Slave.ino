// Use level shifter if operating voltage is diffrent in microcontroller board.


#include <Wire.h>

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
}

void loop() {
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  Serial.println(howMany);
  String data="";
 while (0 < Wire.available()) {
    char c = Wire.read();
    data+=(String)c;      /* receive byte as a character */  
    // Serial.print(c);
  }
 Serial.println(data);             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("Hello NodeMCU");  /*send string on request */
}