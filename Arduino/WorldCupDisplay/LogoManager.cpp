#include "LogoManager.h"

bool LogoManager::begin() {
  return LittleFS.begin(true);
}

bool LogoManager::exists(int teamId) {
  return LittleFS.exists(getLogoPath(teamId));
}

String LogoManager::getLogoPath(int teamId) {
  String path =
    "/logos/" + String(teamId) + ".png";

  if (LittleFS.exists(path)) {
    return path;
  }

  return "/logos/default.png";
}

String LogoManager::getWorldCupLogoPath() {
  return "/logos/crest.png";
}