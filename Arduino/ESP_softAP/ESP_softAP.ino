#include <ESP8266WiFi.h>
 
const char* wifi_network_ssid = "SINHA_NCBN";
const char* wifi_network_password =  "19061969";
 
const char *soft_ap_ssid = "MyESPAP";
const char *soft_ap_password = "testpassword";
 
// void OnWiFiEvent(WiFiEvent_t event)
// {
//   switch (event) {
 
//     case SYSTEM_EVENT_STA_CONNECTED:
//       Serial.println("ESP32 Connected to WiFi Network");
//       break;
//     case SYSTEM_EVENT_AP_START:
//       Serial.println("ESP32 soft AP started");
//       break;
//     case SYSTEM_EVENT_AP_STACONNECTED:
//       Serial.println("Station connected to ESP32 soft AP");
//       break;
//     case SYSTEM_EVENT_AP_STADISCONNECTED:
//       Serial.println("Station disconnected from ESP32 soft AP");
//       break;
//     default: break;
//   }
// }
 
 
void setup() {
 
  Serial.begin(115200);
   
  // WiFi.mode(WIFI_MODE_APSTA);
 
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
 
  Serial.print("ESP32 IP on the WiFi network: ");
  Serial.println(WiFi.localIP());
     
}
 
void loop() {}