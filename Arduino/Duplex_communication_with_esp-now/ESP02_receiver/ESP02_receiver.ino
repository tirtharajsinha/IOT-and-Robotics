#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define LED_COUNT 1
#define LED_PIN 18

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int r;
    int g;
    int b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

String done;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.r);
  Serial.print("Float: ");
  Serial.println(myData.g);
  Serial.print("Bool: ");
  Serial.println(myData.b);
  Serial.println();

  strip.setPixelColor(0, strip.Color(myData.r, myData.g, myData.b));
  strip.show();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else{
    done="yes";
    Serial.println("initialized ESP-NOW successfully");
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);



  strip.begin();
  strip.show();
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  strip.setBrightness(50);
}
 
void loop() {
}