#include <WiFi.h>
#include "index.h"
#include "login.h"
#include <ESPAsyncWebServer.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";         // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);

uint8_t LED1pin = 2;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

int numOfSSID = 0;


void Connect_AP_STATION() {
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.disconnect();


  // AP mode connection
  WiFi.softAP(AP_ssid, AP_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);


  // Connecting to STA mode
  Serial.print("Connecting to : ");
  Serial.println(STA_ssid);


  
}


void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  Connect_AP_STATION();


  server.on("/", handle_OnConnect);
  server.on("/scan", handle_OnScan);
  server.on("/led1", HTTP_GET, handle_led1on);
  server.on("/led2", HTTP_GET, handle_led2on);
  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404);
  });

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  // server.handleClient();
  if (LED1status) {
    digitalWrite(LED1pin, HIGH);
  } else {
    digitalWrite(LED1pin, LOW);
  }

  if (LED2status) {
    digitalWrite(LED2pin, HIGH);
  } else {
    digitalWrite(LED2pin, LOW);
  }
}

void handle_OnConnect(AsyncWebServerRequest* request) {
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
  request->send_P(200, "text/html", index_html, processor);
}

void handle_OnScan(AsyncWebServerRequest* request) {
  request->send_P(200, "text/html", login_html, scanProcessor);
}

void handle_led1on(AsyncWebServerRequest* request) {
  String ledreq = "";
  if (request->hasParam("state")) {
    ledreq = request->getParam("state")->value();
  }
  Serial.println("led request" + ledreq);

  if (ledreq == "ON") {
    LED1status = HIGH;
    Serial.println("GPIO4 Status: ON");
  } else if (ledreq = "OFF") {
    LED1status = LOW;
    Serial.println("GPIO4 Status: OFF");
  }

  request->redirect("/");
}



void handle_led2on(AsyncWebServerRequest* request) {
  String ledreq = "";
  if (request->hasParam("state")) {
    ledreq = request->getParam("state")->value();
  }

  if (ledreq == "ON") {
    LED2status = HIGH;
    Serial.println("GPIO5 Status: ON");
  } else if (ledreq = "OFF") {
    LED2status = LOW;
    Serial.println("GPIO5 Status: OFF");
  }

  request->redirect("/");
}



String processor(const String& var) {
  //Serial.println(var);
  if (var == "BUTTON_TYPE") {
    String buttons = "";

    if (LED1status) {
      buttons += btn1off;
    } else {
      buttons += btn1on;
    }

    if (LED2status) {
      buttons += btn2off;
    } else {
      buttons += btn2on;
    }



    return buttons;
  }
  return String();
}
String scanProcessor(const String& var) {
  //Serial.println(var);
  if (var == "AVAILABLE_WIFI") {
    String buttons = "";
    int n = numOfSSID;
    if (n == 0) {
      Serial.println("no networks found");
      buttons += "No Wifi network found.";

    } else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found

        // Serial.print(WiFi.SSID(i));
        buttons += "<div class='station'><span class='name'><img src='' alt='' class='wifiicon'>" + WiFi.SSID(i) + "</span></div>";

        delay(10);
      }
    }




    return buttons;
  }
  return String();
}