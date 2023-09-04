#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address

uint8_t broadcastAddress[] = { 0x34, 0x85, 0x18, 0xB8, 0x3B, 0x80 };
uint8_t broadcastAddress1[] = { 0x68, 0x67, 0x25, 0x33, 0x2D, 0xE2 };

int LED = LED_BUILTIN;

// Structure example to send data
// Must match the receiver structure
const char secretKey[32] = "jfjvjv6#Gb535kb*&jvi";

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  char secret_key[32];
  int command;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;


// joystick conf
#define joyX 34
#define joyY 35
#define joybtn 25

double xValue = 0;
double yValue = 0;

int threshhold_latency = 750;
int threshhold_fix = 2000;

long long commandTimeoutX = 0;
long long commandTimeoutY = 0;
int commandTimeout = 100;


// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if(status == ESP_NOW_SEND_SUCCESS){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}

void setup() {
  pinMode(LED, OUTPUT);

  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  checkJoystick();
}



void datasender(int command){
  // Set values to send

  Serial.println(command);

  strcpy(myData.secret_key, secretKey);
  myData.command = command;
  

  // Send message via ESP-NOW

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}



void checkJoystick() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  // Serial.println("JOYSTICK ENABLED");
  if (abs(xValue - threshhold_fix) > threshhold_latency || abs(yValue - threshhold_fix) > threshhold_latency) {
    // Serial.print(xValue);
    // Serial.print("\t");
    // Serial.println(yValue);
    if ((millis() - commandTimeoutX) > commandTimeout) {
      commandTimeoutX = millis();
      if ((xValue - threshhold_fix) > threshhold_latency) {
        datasender(1);
        
      }
      if ((xValue - threshhold_fix) < (-1 * threshhold_latency)) {
        datasender(2);
      }
    }


    if ((millis() - commandTimeoutY) > commandTimeout) {
      commandTimeoutY = millis();
      if ((yValue - threshhold_fix) > threshhold_latency) {
        datasender(3);
      }

      if ((yValue - threshhold_fix) < (-1 * threshhold_latency)) {
        datasender(4);
      }
    }
  }
}