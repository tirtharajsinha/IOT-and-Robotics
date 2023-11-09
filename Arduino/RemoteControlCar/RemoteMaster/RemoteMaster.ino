#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "index_html.h"

/*Put WiFi SSID & Password*/
const char* ssid = "SINHA_NCBN";    // Enter SSID here
const char* password = "19061969";  // Enter Password here
const String newHostname = "nodemcu";
int I2C_DEVICE_ADDRESS = 8;


MDNSResponder mdns;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\r\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // Send the current LED status
        const char* res = "OK";
        webSocket.sendTXT(num, res, strlen(res));
      }
      break;
    case WStype_TEXT:
      // Serial.printf("[%u] get Text: %s\r\n", num, payload);
      handle_joystick(payload, length);

      // send data to all connected clients
      webSocket.broadcastTXT(payload, length);
      break;
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\r\n", num, length);
      hexdump(payload, length);

      // echo data back to browser
      webSocket.sendBIN(num, payload, length);
      break;
    default:
      Serial.printf("Invalid WStype [%d]\r\n", type);
      break;
  }
}



void handle_joystick(uint8_t* payload, size_t length) {
  String json = (char*)payload;

  DynamicJsonDocument data(1024);
  deserializeJson(data, json);
  
  DynamicJsonDocument doc(1024);
  doc["data"][0] = data["x"];
  doc["data"][1] = data["y"];
  doc["data"][2] = data["angle"];
  String remote;
  serializeJson(doc, remote);

  Wire.beginTransmission(I2C_DEVICE_ADDRESS); /* begin with device address 8 */
  Wire.write(remote.c_str());                /* sends hello string */
  Wire.endTransmission();                     /* stop transmitting */
}



void handle_OnConnect() {
  String html = index_html;
  String ip = WiFi.localIP().toString().c_str();
  html.replace("{{IPADDRESS}}", ip);
  server.send(200, "text/html", html);
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);

  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  Serial.println("Connecting to ");
  Serial.println(ssid);


  WiFi.hostname(newHostname.c_str());

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
  }

  Serial.println("");

  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin(newHostname, WiFi.localIP())) {
    Serial.println("MDNS responder started");
    mdns.addService("http", "tcp", 80);
    mdns.addService("ws", "tcp", 81);
  } else {
    Serial.println("MDNS.begin failed");
  }

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.begin();
  Serial.print("HTTP Server Started on : http://" + newHostname + ".local");
}
void loop() {
  webSocket.loop();
  server.handleClient();
}
