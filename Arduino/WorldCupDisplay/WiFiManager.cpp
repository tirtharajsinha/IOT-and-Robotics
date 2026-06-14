#include "WiFiManager.h"
#include <Arduino.h>

void WiFiManager::begin(
  const char* ssid,
  const char* password) {
  _ssid = ssid;
  _password = password;

  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  Serial.print("WiFi connecting...");
  connecting = true;
  lastAttempt = millis();

  int retries = 0;

  while (
    WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(1000);
    Serial.print(".");
    retries++;
    lastAttempt = millis();
  }
}

bool WiFiManager::isConnected() const {
  return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::update() {
  if (WiFi.status() == WL_CONNECTED) {
    if (connecting) {
      Serial.println("WiFi connected!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      connecting = false;
    }
    return;
  }

  // not connected → retry with backoff
  unsigned long now = millis();

  if (now - lastAttempt > retryDelay) {
    Serial.println("Reconnecting WiFi...");

    WiFi.disconnect();
    WiFi.begin(_ssid, _password);

    lastAttempt = now;

    // exponential backoff (max 30s)
    retryDelay *= 2;
    if (retryDelay > 30000)
      retryDelay = 30000;
  }
}