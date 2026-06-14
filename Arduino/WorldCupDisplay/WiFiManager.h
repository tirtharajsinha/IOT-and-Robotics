#pragma once

#include <WiFi.h>

class WiFiManager
{
public:
    void begin(
        const char* ssid,
        const char* password
    );

    void update();

    bool isConnected() const;

private:
    const char* _ssid;
    const char* _password;

    unsigned long lastAttempt = 0;
    int retryDelay = 2000;

    bool connecting = false;
};