// # Notice
// HC-05 module is used here.
// Pin config
//+--------+-------------+
//| HC-05  | ESP32       |
//|--------+-------------+
//| GND    | GND         |
//| VCC    | 5V          |
//| RXD    | TX(pin 11)  |
//| TXD    | RX(Pin 12)  |
//+--------+-------------+

// Disconnect the RX and TX pin of HC-05 from arduino before code upload and connect back after code upload.
// use Arduino bluetooth Controller
// Tirtharaj Sinha


#define ledPin 8
String data = "";
#define DATA_SIZE 26  // 26 bytes is a lower than RX FIFO size (127 bytes)
#define BAUD 9600   // Any baudrate from 300 to 115200
#define TEST_UART 1   // Serial1 will be used for the loopback testing with different RX FIFO FULL values
#define RXPIN 12      // GPIO 12 => RX for Serial1
#define TXPIN 11      // GPIO 11 => TX for Serial1


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);  //default baud rate for bt 38400
  Serial1.begin(BAUD, SERIAL_8N1, RXPIN, TXPIN);
}
void loop() {
  if (Serial1.available() > 0) {  // Checks whether data is comming from the serial port      // Reads the data from the serial port
    Serial1.setTimeout(100);
    data=Serial1.readStringUntil('\n');
    Serial.print("BT : ");
    Serial.println(data);

    

    if (data == "0") {
      digitalWrite(ledPin, LOW);  // Turn LED OFF
      Serial1.println("LED: OFF");
    } else if (data == "1") {
      digitalWrite(ledPin, HIGH);
      Serial1.println("LED: ON");
    }
    else{
      Serial1.println("ok");
    }
  }
}
