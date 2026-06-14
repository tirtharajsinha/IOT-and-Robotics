#include "ApiClient.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

#include "Config.h"
#include "StorageManager.h"

ApiClient Api;

static String utcToIst(
    const String& utc
)
{
    struct tm tm = {};

    strptime(
        utc.c_str(),
        "%Y-%m-%dT%H:%M:%SZ",
        &tm
    );

    time_t t =
        mktime(&tm);

    t += 19800;

    struct tm ist;

    gmtime_r(
        &t,
        &ist
    );

    char buffer[32];

    strftime(
        buffer,
        sizeof(buffer),
        "%d %b %H:%M",
        &ist
    );

    return String(buffer);
}

static String buildUrl() {
  time_t now;

  time(&now);

  time_t start =
    now - (HOURS_BACK * 3600);

  time_t end =
    now + (HOURS_FORWARD * 3600);

  struct tm tmStart;
  struct tm tmEnd;

  gmtime_r(&start, &tmStart);
  gmtime_r(&end, &tmEnd);

  char fromBuf[16];
  char toBuf[16];

  strftime(
    fromBuf,
    sizeof(fromBuf),
    "%Y-%m-%d",
    &tmStart);

  strftime(
    toBuf,
    sizeof(toBuf),
    "%Y-%m-%d",
    &tmEnd);

  String url =
    "https://api.football-data.org/v4/competitions/";

  url += COMPETITION_CODE;

  url += "/matches?dateFrom=";
  url += fromBuf;

  url += "&dateTo=";
  url += toBuf;

  return url;
}

bool ApiClient::requestFixtures(
  String& response) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(
      "WiFi not connected");

    return false;
  }

  String url =
    buildUrl();

  Serial.println(url);

  HTTPClient http;

  http.begin(url);

  http.addHeader(
    "X-Auth-Token",
    API_KEY);

  int code =
    http.GET();

  Serial.printf(
    "HTTP Code: %d\n",
    code);

  if (code != HTTP_CODE_OK) {
    http.end();
    return false;
  }

  response =
    http.getString();

  Storage.saveJson(
    "/fixtures.json",
    response);

  http.end();

  return true;
}

bool ApiClient::parseFixtures(
  const String& json,
  Match* matches,
  int& count) {
  DynamicJsonDocument doc(
    1024 * 64);

  auto err =
    deserializeJson(
      doc,
      json);

  if (err) {
    Serial.println(
      err.c_str());

    return false;
  }

  JsonArray arr =
    doc["matches"];

  count = 0;

  for (JsonObject m : arr) {
    if (count >= MAX_MATCHES)
      break;

    Match& match =
      matches[count];

    match.id =
      m["id"];

    match.homeTeamId =
      m["homeTeam"]
       ["id"]
      | 0;

    match.awayTeamId =
      m["awayTeam"]
       ["id"]
      | 0;

    match.homeTeam =
      m["homeTeam"]
       ["name"]
         .as<String>();

    match.awayTeam =
      m["awayTeam"]
       ["name"]
         .as<String>();

    match.homeCrest =
      m["homeTeam"]
       ["crest"]
         .as<String>();

    match.awayCrest =
      m["awayTeam"]
       ["crest"]
         .as<String>();

    match.homeTla =
      m["homeTeam"]
       ["tla"]
         .as<String>();

    match.awayTla =
      m["awayTeam"]
       ["tla"]
         .as<String>();

    match.homeGoals =
      m["score"]
       ["fullTime"]
       ["home"]
      | 0;

    match.awayGoals =
      m["score"]
       ["fullTime"]
       ["away"]
      | 0;

    match.status =
      m["status"]
        .as<String>();

    match.utcDate =
      m["utcDate"]
        .as<String>();

    match.istDate =
      utcToIst(
        match.utcDate);

    match.finished =
      (match.status == "FINISHED");

    match.homeGoals =
      max(
        0,
        match.homeGoals);

    match.awayGoals =
      max(
        0,
        match.awayGoals);

    count++;
  }

  return true;
}

bool ApiClient::fetchFixtures(
  Match* matches,
  int& count) {
  String json;

  bool online =
    requestFixtures(
      json);

  if (!online) {
    json =
      Storage.loadJson(
        "/fixtures.json");

    if (json.length() == 0)
      return false;
  }

  bool ok =
    parseFixtures(
      json,
      matches,
      count);

  if (ok) {
    Serial.println();
    Serial.println(
      "========== MATCHES ==========");

    for (int i = 0; i < count; i++) {
      Match& m =
        matches[i];

      Serial.printf(
        "%02d) %s vs %s\n",
        i + 1,
        m.homeTeam.c_str(),
        m.awayTeam.c_str());

      Serial.printf(
        "Status: %s\n",
        m.status.c_str());

      Serial.printf(
        "Score : %d-%d\n",
        m.homeGoals,
        m.awayGoals);

      Serial.printf(
        "UTC   : %s\n",
        m.utcDate.c_str());

      Serial.println();
    }

    Serial.printf(
      "Loaded %d matches\n",
      count);
  }

  return ok;
}


