// Setup the API key in config.h

#include "WiFiManager.h"
#include "Config.h"
#include "StorageManager.h"
#include "ApiClient.h"

#include "LogoManager.h"
#include "PngRenderer.h"
#include "DisplayManager.h"
#include "LittleFS.h"

#include "Match.h"

Match matches[MAX_MATCHES];
int matchCount = 0;

LogoManager logoManager;
PngRenderer pngRenderer;
WiFiManager wifi;

Adafruit_ST7735 tft(
  TFT_CS,
  TFT_DC,
  TFT_RST);

DisplayManager display(
  tft,
  logoManager,
  pngRenderer);

uint32_t lastRotation = 0;
uint32_t lastRefresh = 0;

int currentMatch = 0;

static const int SCREEN_W = 160;
static const int BAR_Y = 122;
static const int BAR_H = 4;

static const int MATCH_DURATION = 7000;  // 7 seconds




void connectWifi() {
  wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  wifi.update();
}


void setupTime() {
  configTime(
    0,
    0,
    "pool.ntp.org",
    "time.nist.gov");

  Serial.print(
    "Waiting for NTP...");

  time_t now;

  while (true) {
    time(&now);

    if (
      now > 1700000000) {
      break;
    }

    Serial.print(".");
    delay(500);
  }

  Serial.println();

  Serial.println(
    ctime(&now));
}

bool loadFixtures() {

  if (!wifi.isConnected()) {
    Serial.println("Skipping API fetch (no WiFi)");
    return false;
  }

  bool ok =
    Api.fetchFixtures(
      matches,
      matchCount);

  if (!ok) {
    display.showError(
      "No Data");

    return false;
  }

  Serial.printf(
    "Loaded %d matches\n",
    matchCount);

  if (matchCount > 0) {
    currentMatch = 0;

    display.showMatch(
      matches[0]);
  }

  return true;
}

void drawProgressBar() {
  if (matchCount == 0)
    return;

  float progress =
    (currentMatch + 1) / (float)matchCount;

  if (progress > 1.0f)
    progress = 1.0f;

  int barWidth = SCREEN_W - 10;

  int filled = barWidth * progress;

  static int lastFilled = -1;

  if (filled == lastFilled)
    return;

  lastFilled = filled;

  // background
  tft.fillRect(
    5,
    BAR_Y,
    barWidth,
    BAR_H,
    ST77XX_BLACK);

  // filled part
  if (filled > 0) {
    tft.fillRect(
      5,
      BAR_Y,
      filled,
      BAR_H,
      ST77XX_GREEN);
  }
}
void showLoadingScreen(const char* msg) {
  tft.fillScreen(ST77XX_WHITE);

  // center crest
  pngRenderer.draw("/logos/crest_big.png", 50, 10);

  // optional text
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setCursor(30, 110);
  tft.print(msg);
}

void setup() {
  Serial.begin(115200);

  tft.initR(
    INITR_BLACKTAB);

  Storage.begin();

  logoManager.begin();

  pngRenderer.begin(&tft);

  display.begin();

  showLoadingScreen("Connecting WiFi...");
  connectWifi();

  showLoadingScreen("Syncing time...");
  setupTime();

  showLoadingScreen("Fetching Matches...");
  loadFixtures();

  lastRotation =
    millis();

  lastRefresh =
    millis();


  tft.fillScreen(ST77XX_WHITE);
  display.showMatch(
    matches[currentMatch]);
  drawProgressBar();
}


void loop() {

  // wifi re-connect
  wifi.update();
  //--------------------------------
  // Rotate Match
  //--------------------------------

  if (
    matchCount > 0 && millis() - lastRotation >= MATCH_ROTATION_INTERVAL) {
    currentMatch++;


    if (
      currentMatch >= matchCount) {
      currentMatch = 0;
    }

    display.showMatch(
      matches[currentMatch]);

    lastRotation =
      millis();
    drawProgressBar();
  }

  //--------------------------------
  // Refresh Scores
  //--------------------------------

  if (millis() - lastRefresh >= API_REFRESH_INTERVAL) {
    Serial.println(
      "Refreshing fixtures...");

    loadFixtures();

    lastRefresh =
      millis();
  }
}