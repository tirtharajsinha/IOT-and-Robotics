// #include <WiFi.h>
#include <esp_wifi.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

/*Put your SSID & Password*/
const char* ssid = "Tirtha";           // Enter SSID here
const char* password = "12233344440";  //Enter Password here

AsyncWebServer server(80);

uint8_t LED1pin = 2;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

void Connect_STATION() {
  WiFi.mode(WIFI_STA);
  esp_wifi_set_ps(WIFI_PS_NONE);

  Serial.print("Connecting to : ");
  Serial.println(ssid);


  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  delay(100);
}

void setup() {
  Serial.begin(115200);

  Connect_STATION();

  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);


  server.on("/", handle_OnConnect);
  server.on("/led1", HTTP_GET, handle_led1on);
  // server.on("/led1", handle_led1off);
  server.on("/led2", HTTP_GET, handle_led2on);

  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404);
  });

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  // server.handleClient();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
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
  } else if (var == "SERVER_TITLE") {
    return "ESP32 Devkit v1";
  }

  return String();
}