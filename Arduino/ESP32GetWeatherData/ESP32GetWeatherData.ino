#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SINHA_NCBN";
const char* password = "19061969";


const String key = "8e44efb0ae84f237a5d93f5f4d629433";
String city = "katwa";
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("\n");
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("..");
  }

  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient

    String reqURL = endpoint + city + "&APPID=" + key + "&units=metric";
    http.begin(reqURL);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String res = http.getString();
      DynamicJsonDocument root(1024);
      deserializeJson(root, res);

      // Serial.println(res);

      String des = root["weather"][0]["description"];
      String temp = root["main"]["temp"];
      String pressure = root["main"]["pressure"];
      String hum = root["main"]["humidity"];


      Serial.println("------------------------");
      Serial.printf("Temp: %s degC\n", temp);
      Serial.printf("Pressure: %s hpa\n", pressure);
      Serial.printf("humidity: %s g/m3\n", hum);
      Serial.print("Weather: ");
      Serial.println(des);
      Serial.println("------------------------\n\n");
    }
    http.end();  //Close connection
  }
  delay(60000);
}