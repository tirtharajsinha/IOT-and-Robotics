#include "PngRenderer.h"

Adafruit_ST7735* PngRenderer::tft = nullptr;

int16_t PngRenderer::drawX = 0;
int16_t PngRenderer::drawY = 0;

bool PngRenderer::begin(
    Adafruit_ST7735* display
)
{
    tft = display;
    return true;
}

void* PngRenderer::pngOpen(
    const char* filename,
    int32_t* size
)
{
    File* file =
        new File(
            LittleFS.open(
                filename,
                "r"
            )
        );

    if (!(*file))
    {
        delete file;
        return nullptr;
    }

    *size = file->size();

    return file;
}

void PngRenderer::pngClose(
    void* handle
)
{
    File* file =
        static_cast<File*>(handle);

    if (file)
    {
        file->close();
        delete file;
    }
}

int32_t PngRenderer::pngRead(
    PNGFILE* page,
    uint8_t* buffer,
    int32_t length
)
{
    File* file =
        static_cast<File*>(
            page->fHandle
        );

    if (!file)
        return 0;

    return file->read(
        buffer,
        length
    );
}

int32_t PngRenderer::pngSeek(
    PNGFILE* page,
    int32_t position
)
{
    File* file =
        static_cast<File*>(
            page->fHandle
        );

    if (!file)
        return 0;

    file->seek(position);

    return position;
}

int PngRenderer::pngDraw(
    PNGDRAW* draw
)
{
    uint16_t lineBuffer[256];

    PNG png;

    png.getLineAsRGB565(
    draw,
    lineBuffer,
    PNG_RGB565_LITTLE_ENDIAN,
    0xFFFF // white background instead of black
);

    tft->drawRGBBitmap(
        drawX,
        drawY + draw->y,
        lineBuffer,
        draw->iWidth,
        1
    );

    return 1;
}

bool PngRenderer::draw(
    const String& path,
    int16_t x,
    int16_t y
)
{
    drawX = x;
    drawY = y;

    int rc =
        png.open(
            path.c_str(),
            pngOpen,
            pngClose,
            pngRead,
            pngSeek,
            pngDraw
        );

    if (rc != PNG_SUCCESS)
    {
        Serial.printf(
            "PNG open failed: %s\n",
            path.c_str()
        );

        return false;
    }

    rc =
        png.decode(
            nullptr,
            0
        );

    png.close();

    if (rc != PNG_SUCCESS)
    {
        Serial.printf(
            "PNG decode failed: %s\n",
            path.c_str()
        );

        return false;
    }

    return true;
}