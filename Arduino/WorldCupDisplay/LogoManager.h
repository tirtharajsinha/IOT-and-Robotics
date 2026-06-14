#pragma once

#include <Arduino.h>
#include <LittleFS.h>

class LogoManager {
public:
  bool begin();

  bool exists(int teamId);

  String getLogoPath(int teamId);

  String getWorldCupLogoPath();
};