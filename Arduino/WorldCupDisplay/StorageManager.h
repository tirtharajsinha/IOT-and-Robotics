#pragma once

#include <LittleFS.h>

class StorageManager
{
public:

    bool begin();

    bool saveJson(
        const String& path,
        const String& data
    );

    String loadJson(
        const String& path
    );

    bool exists(
        const String& path
    );

    bool saveBinary(
        const String& path,
        uint8_t* data,
        size_t len
    );

    File open(
        const String& path,
        const char* mode
    );
};

extern StorageManager Storage;