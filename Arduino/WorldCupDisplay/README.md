# ⚽ ESP32 World Cup Live Display

Real-time football scoreboard for ESP32 with ST7735, LittleFS, PNG team logos, and Football-Data API integration. Shows live and scheduled matches in a broadcast-style layout with auto-rotation.

## Features

- Live data from Football-Data API
- Team logos stored in LittleFS (`/logos/<teamId>.png`)
- World Cup crest displayed between teams
- Auto-rotating match display (configurable interval)
- Progress bar showing match pagination
- WiFi auto-reconnect
- NTP time synchronization (optional IST conversion)
- TV-style UI (Adafruit GFX)
- PNG rendering via PNGdec (ESP32-optimized)
- Offline fallback using cached JSON

## Hardware Required

- ESP32 Dev Board
- ST7735 TFT Display (160×128, SPI)
- Micro USB cable
- Optional: SD / LittleFS storage (project uses built-in flash)

## Project Structure

Top-level files:

- `WorldCupDisplay.ino`
- `ApiClient.cpp` / `ApiClient.h`
- `DisplayManager.cpp` / `DisplayManager.h`
- `PngRenderer.cpp` / `PngRenderer.h`
- `LogoManager.cpp` / `LogoManager.h`
- `Match.h`
- `WiFiManager.cpp` / `WiFiManager.h`
- `StorageManager.cpp` / `StorageManager.h`
- `Config.h`
- `logoDownloader.py` (helper to fetch logos)

Assets:

- `data/logos/` — development folder containing sample logos (used when preparing LittleFS image)

## Setup

1. Install Arduino libraries (via Library Manager)

- Adafruit GFX Library
- Adafruit ST7735 and ST7789 Library
- ArduinoJson
- PNGdec (v1.1.6)
- WiFi (included with ESP32 core)
- LittleFS (ESP32 core)

2. Configure WiFi and API key

Edit `Config.h` and set your credentials and API key, for example:

```cpp
#define WIFI_SSID "your_wifi"
#define WIFI_PASSWORD "your_password"

#define API_KEY "your_football_data_api_key"
#define COMPETITION_CODE "WC"

#define MATCH_ROTATION_INTERVAL 7000 // milliseconds
```

3. Prepare and upload LittleFS image

- Place logo PNGs into `data/logos/` when using the Arduino "ESP32 Sketch Data Upload" tool.
- In firmware the code expects logos at `/logos/<teamId>.png` inside LittleFS (e.g. `/logos/758.png`).
- Upload using: `Tools → ESP32 Sketch Data Upload` or the LittleFS uploader plugin.

4. Logo format recommendations

- PNG format
- ~32×32 pixels (recommended)
- Prefer no transparency (pre-render on a white background)
- Filenames: `<teamId>.png` (e.g. `758.png`), and `crest.png` for tournament crest

Tip: use `logoDownloader.py` to fetch and prepare logos automatically.

## How it works (high level)

1. Boot and display tournament crest
2. Connect to WiFi (auto-reconnect)
3. Sync time via NTP (optional IST conversion)
4. Fetch matches from Football-Data API and cache JSON in LittleFS
5. Main loop renders one match at a time and rotates every `MATCH_ROTATION_INTERVAL`

Displayed info: team logos, TLA, score (winner highlighted), match status (LIVE / FT / SCHEDULED), date/time, and a progress bar.

## Development

- `logoDownloader.py` — helper script to download logos into `data/logos/` (run with Python 3).
- Build and upload from Arduino IDE: open `WorldCupDisplay.ino`, compile and upload the sketch, then upload LittleFS data.

## Known Constraints

- PNGs should be pre-processed (transparent areas may not render as intended)
- Recommended resolution: 32×32
- ST7735 limited to 16-bit color depth
- ESP32 has limited RAM for large images; optimize assets accordingly

## Future Improvements

- Smooth match transition animations
- Live match blinking indicator
- Gradient score UI and group-stage views
- Dual-display (OLED + TFT) support

## Author Notes

This project is a compact broadcast-style display on ESP32 combining real-time API integration, embedded graphics rendering, filesystem-based asset management, and network resilience.
