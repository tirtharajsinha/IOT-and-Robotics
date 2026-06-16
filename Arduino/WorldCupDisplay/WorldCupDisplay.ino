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


uint32_t bootTime = 0;


Match matches[MAX_MATCHES];
int matchCount = 0;

Match liveMatches[MAX_MATCHES];
int liveMatchCount = 0;

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

void updateLiveMatches() {
  liveMatchCount = 0;

  for (int i = 0; i < matchCount; i++) {
    if (matches[i].isLive()) {
      liveMatches[liveMatchCount++] =
        matches[i];
    }
  }
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

  updateLiveMatches();

  int count =
    (liveMatchCount > 0)
      ? liveMatchCount
      : matchCount;

  if (currentMatch >= count) {
    currentMatch = 0;
  }

  if (!ok) {
    display.showError(
      "No Data");

    return false;
  }

  Serial.printf(
    "Loaded %d matches\n",
    matchCount);


  return true;
}

uint32_t getRefreshInterval() {
  return liveMatchCount > 0
           ? REFRESH_INTERVAL_LIVE
           : REFRESH_INTERVAL_NORMAL;
}

void drawProgressBar() {
  if (matchCount == 0)
    return;

  int totalPages =
    (liveMatchCount > 0)
      ? liveMatchCount
      : matchCount;

  float progress =
    (currentMatch + 1) / (float)totalPages;

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

void restartBoard() {
  constexpr uint32_t RESTART_INTERVAL =
    2UL * 60UL * 60UL * 1000UL;  // 2 hours

  if (
    millis() - bootTime >= RESTART_INTERVAL && liveMatchCount == 0) {
    Serial.println(
      "Scheduled restart");

    delay(1000);

    ESP.restart();
  }
}

void setup() {

  Serial.begin(115200);

  tft.initR(
    INITR_BLACKTAB);

  tft.invertDisplay(false);

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
  Match& match =
    (liveMatchCount > 0)
      ? liveMatches[currentMatch]
      : matches[currentMatch];

  display.showMatch(match);
  drawProgressBar();
}


void loop() {
  // restart board
  restartBoard();

  // wifi re-connect
  wifi.update();
  //--------------------------------
  // Rotate Match
  //--------------------------------



  int displayCount =
    (liveMatchCount > 0)
      ? liveMatchCount
      : matchCount;

  if (
    displayCount > 1 && millis() - lastRotation >= MATCH_ROTATION_INTERVAL) {
    currentMatch++;

    if (currentMatch >= displayCount)
      currentMatch = 0;

    Match& match =
      (liveMatchCount > 0)
        ? liveMatches[currentMatch]
        : matches[currentMatch];

    display.showMatch(match);

    lastRotation = millis();

    drawProgressBar();
  }

  //--------------------------------
  // Refresh Scores
  //--------------------------------

  if (millis() - lastRefresh >= getRefreshInterval()) {
    Serial.println(
      "Refreshing fixtures...");

    if (loadFixtures()) {

      Match& match =
        (liveMatchCount > 0)
          ? liveMatches[currentMatch]
          : matches[currentMatch];

      display.showMatch(match);

      drawProgressBar();
    }


    lastRefresh =
      millis();
  }

  if (!wifi.isConnected()) {
    tft.drawFastHLine(
      0,
      0,
      5,
      ST77XX_RED);
  }
}