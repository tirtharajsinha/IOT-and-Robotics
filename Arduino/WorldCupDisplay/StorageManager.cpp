#include "StorageManager.h"

StorageManager Storage;


bool StorageManager::begin() {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
    return false;
  }

  Serial.println("LittleFS mounted");

  return true;
}

bool StorageManager::exists(
  const String& path) {
  return LittleFS.exists(path);
}

bool StorageManager::saveJson(
  const String& path,
  const String& data) {
  File f =
    LittleFS.open(path, "w");

  if (!f)
    return false;

  f.print(data);

  f.close();

  return true;
}

String StorageManager::loadJson(
  const String& path) {
  File f =
    LittleFS.open(path, "r");

  if (!f)
    return "";

  String data =
    f.readString();

  f.close();

  return data;
}

bool StorageManager::saveBinary(
  const String& path,
  uint8_t* data,
  size_t len) {
  File f =
    LittleFS.open(path, "w");

  if (!f)
    return false;

  f.write(data, len);

  f.close();

  return true;
}

File StorageManager::open(
  const String& path,
  const char* mode) {
  return LittleFS.open(
    path,
    mode);
}