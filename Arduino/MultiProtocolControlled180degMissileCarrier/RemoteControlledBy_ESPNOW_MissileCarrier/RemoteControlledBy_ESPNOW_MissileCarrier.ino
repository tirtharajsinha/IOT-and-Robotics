#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>


// Servo Conf
int ServoPinX = 5;
int ServoPinY = 3;

Servo ServoX;
Servo ServoY;

int PosX = 0;
int PosY = 0;

int ServoLimitHigh = 180;
int ServoLimitLow = 0;

int ServoStep = 10;  // movement angel on each command

// Carrier enable btn
const int btn = 0;
double btntime = 0;
bool ENABLE = false;

// Carrier enable indecation LED
int led = 13;
int neopixelPin = 21;


const char secretKey[32] = "jfjvjv6#Gb535kb*&jvi";

Adafruit_NeoPixel strip(1, neopixelPin, NEO_GRB + NEO_KHZ800);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char secret_key[32];
  int command;
} struct_message;

// Create a struct_message called myData
struct_message myData;

void setup() {
  Serial.begin(9600);


  // put your setup code here, to run once:
  ServoX.attach(ServoPinX);
  ServoY.attach(ServoPinY);

  // Setting servo to initial position
  if (ServoX.attached() && ServoY.attached()) {
    Serial.println("SERVO Ready");
  }

  ServoY.write(PosY);
  ServoX.write(PosX);

  // Configuring the led and button
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);


  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("initialized ESP-NOW successfully");
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);


  // Serial.println("Joystick DISABLED");
}

void loop() {
  CheckPermission();
}


void UP() {
  // Go up
  if (manageAngel(PosY, 1)) {
    // Serial.println("Going UP");
    PosY += ServoStep;
    ServoY.write(PosY);
  }
}

void DOWN() {
  // Go Down
  if (manageAngel(PosY, 0)) {
    // Serial.println("Going DOWN");
    PosY -= ServoStep;
    ServoY.write(PosY);
  }
}


void RIGHT() {
  // Go Right
  if (manageAngel(PosX, 1)) {
    // Serial.println("Going RIGHT");
    PosX += ServoStep;
    ServoX.write(PosX);
  }
}


void LEFT() {
  // Go Left
  if (manageAngel(PosX, 0)) {
    // Serial.println("Going LEFT");
    PosX -= ServoStep;
    ServoX.write(PosX);
  }
}

bool manageAngel(int a, int direction) {
  if (direction == 1) {
    if ((a + ServoStep) <= ServoLimitHigh) {
      return true;
    } else {
      return false;
    }
  } else {
    if ((a - ServoStep) >= ServoLimitLow) {
      return true;
    } else {
      return false;
    }
  }
}


void CheckPermission() {
  // Serial.println(digitalRead(btn));
  if (digitalRead(btn) == LOW) {
    if ((millis() - btntime) > 1000) {
      btntime = millis();
      ENABLE = !ENABLE;
      if (ENABLE) {
        // Serial.println("Joystick ENABLED");
        digitalWrite(led, HIGH);
      } else {
        // Serial.println("Joystick DISABLED");
        digitalWrite(led, LOW);
      }
    }
  }
}

// exp-now receiver

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  Serial.println("Received data through ESP-NOW from" + String((char *)mac));
  if (ENABLE) {
    memcpy(&myData, incomingData, sizeof(myData));

    if(myData.secret_key!=secretKey){
      Serial.println("Security check FAILED : Wrong key received.")
      return;
    }
    switch (myData.command) {
      case 1:
        LEFT();
        break;
      case 2:
        RIGHT();
        break;
      case 3:
        UP();
        break;
      case 4:
        DOWN();
        break;
      default:
        Serial.print("Invalid command");
    }
  }
}
