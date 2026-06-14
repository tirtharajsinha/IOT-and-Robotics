#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "Match.h"
#include "LogoManager.h"
#include "PngRenderer.h"

class DisplayManager
{
public:
    DisplayManager(
        Adafruit_ST7735& display,
        LogoManager& logoManager,
        PngRenderer& renderer
    );

    void begin();

    void showLoading();

    void showError(
        const String& message
    );

    void showMatch(
        const Match& match
    );

private:
    Adafruit_ST7735& tft;

    LogoManager& logos;

    PngRenderer& png;

    void drawCenteredText(
        const String& text,
        int y,
        uint8_t size = 1
    );

    void drawStatus(
        const Match& match
    );
};