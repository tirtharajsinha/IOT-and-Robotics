#pragma once

#include <Arduino.h>
#include <LittleFS.h>
#include <PNGdec.h>
#include <Adafruit_ST7735.h>

class PngRenderer
{
public:
    bool begin(Adafruit_ST7735* display);

    bool draw(
        const String& path,
        int16_t x,
        int16_t y
    );

private:
    static void* pngOpen(
        const char* filename,
        int32_t* size
    );

    static void pngClose(
        void* handle
    );

    static int32_t pngRead(
        PNGFILE* page,
        uint8_t* buffer,
        int32_t length
    );

    static int32_t pngSeek(
        PNGFILE* page,
        int32_t position
    );

    static int pngDraw(
        PNGDRAW* draw
    );

private:
    static Adafruit_ST7735* tft;

    static int16_t drawX;
    static int16_t drawY;

    PNG png;
};