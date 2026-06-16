#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

namespace Colors
{
    constexpr uint16_t Background =
        ST77XX_WHITE;

    constexpr uint16_t Primary =
        ST77XX_BLACK;

    constexpr uint16_t Secondary =
        0xBDF7;

    constexpr uint16_t Success =
        ST77XX_GREEN;

    constexpr uint16_t Error =
        ST77XX_RED;

    constexpr uint16_t Live =
        ST77XX_RED;

    constexpr uint16_t Upcoming =
        ST77XX_BLUE;

    constexpr uint16_t Green=
        ST77XX_GREEN;

    constexpr uint16_t LGreen=
        0xadff96;
    
}