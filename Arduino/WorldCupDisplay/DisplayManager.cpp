#include "DisplayManager.h"
#include "colors.h"
#include "PngRenderer.h"

static const int W = 160;
static const int H = 128;

static const int LOGO_Y = 5;
static const int TEXT_Y = 52;
static const int SCORE_Y = 70;
static const int STATUS_Y = 95;
static const int DATE_Y = 112;
static const int HOME_X = 22;
static const int MID_X = 80;
static const int AWAY_X = 128;

DisplayManager::DisplayManager(
  Adafruit_ST7735& display,
  LogoManager& logoManager,
  PngRenderer& renderer)
  : tft(display),
    logos(logoManager),
    png(renderer) {
}

void DisplayManager::begin() {
  tft.setRotation(3);

  tft.fillScreen(
    Colors::Background);
}

void DisplayManager::showLoading() {
  tft.fillScreen(
    Colors::Background);



  drawCenteredText(
    "Loading...",
    55,
    2);
}

void DisplayManager::showError(
  const String& message) {
  tft.fillScreen(
    Colors::Background);

  tft.setTextColor(
    Colors::Error);

  drawCenteredText(
    "ERROR",
    35,
    2);

  drawCenteredText(
    message,
    70);
}

void DisplayManager::showMatch(const Match& match) {
  tft.fillScreen(Colors::Background);

  //---------------------------
  // TOP ROW: Logos
  //---------------------------
  //   tft.fillRect(x, y, draw->iWidth, draw->iHeight, ST77XX_WHITE);
  png.draw(logos.getLogoPath(match.homeTeamId), 8, LOGO_Y);
  png.draw(logos.getWorldCupLogoPath(), 67, LOGO_Y + 5);
  png.draw(logos.getLogoPath(match.awayTeamId), 115, LOGO_Y);

  //---------------------------
  // TEAM NAMES
  //---------------------------

  tft.setFont(NULL);
  tft.setTextSize(2);
  tft.setTextColor(Colors::Primary);

  // HOME team under left logo
  tft.setCursor(HOME_X - 10, TEXT_Y);
  tft.print(match.homeTla);

  // AWAY team under right logo
  tft.setCursor(AWAY_X - 10, TEXT_Y);
  tft.print(match.awayTla);

  //---------------------------
  // SCORE (MAIN FOCUS)
  //---------------------------
  if (match.status != "TIMED") {
    tft.setTextSize(2);

    if (match.homeWon())
      tft.setTextColor(Colors::Primary);
    else
      tft.setTextColor(Colors::Secondary);

    tft.setCursor(60, SCORE_Y);
    tft.print(match.homeGoals);

    tft.setTextColor(Colors::Primary);
    tft.setCursor(76, SCORE_Y);
    tft.print("-");

    if (match.awayWon())
      tft.setTextColor(Colors::Primary);
    else
      tft.setTextColor(Colors::Secondary);

    tft.setCursor(92, SCORE_Y);
    tft.print(match.awayGoals);
  }



  //---------------------------
  // STATUS BADGE
  //---------------------------

  uint16_t statusColor = Colors::Primary;

  if (match.status == "IN_PLAY") {
    statusColor = Colors::Live;
    tft.fillCircle(150, STATUS_Y, 3, Colors::Live);
  } else if (match.status == "FINISHED") {
    statusColor = Colors::Secondary;
  }


  tft.setTextColor(statusColor);

  if (match.status == "TIMED") {
    drawCenteredText(match.displayStatus(), STATUS_Y - 12, 2);
  } else {
    drawCenteredText(match.displayStatus(), STATUS_Y-2, 1);
  }



  //---------------------------
  // DATE FOOTER
  //---------------------------

  tft.setTextColor(Colors::Primary);
  drawCenteredText(match.istDate + " IST", DATE_Y-2);
}

void DisplayManager::drawStatus(
  const Match& match) {
  uint16_t color =
    Colors::Primary;

  if (match.status == "IN_PLAY") {
    color =
      Colors::Live;
  }

  tft.setTextColor(
    color);

  drawCenteredText(
    match.displayStatus(),
    100,
    1);
}

void DisplayManager::drawCenteredText(
  const String& text,
  int y,
  uint8_t size) {
  tft.setTextSize(size);

  int16_t x1, y1;
  uint16_t w, h;

  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (160 - w) / 2;

  tft.setCursor(x, y);
  tft.print(text);
}