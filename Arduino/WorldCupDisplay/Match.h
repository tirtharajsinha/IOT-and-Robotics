#pragma once

#include <Arduino.h>

struct Match {
  int id;

  int homeTeamId;
  int awayTeamId;

  String homeTeam;
  String awayTeam;

  String homeCrest;
  String awayCrest;

  String homeTla;
  String awayTla;

  int homeGoals;
  int awayGoals;

  String status;

  String utcDate;
  String istDate;

  bool finished;

  String displayStatus() const {
    if (status == "TIMED" || status == "SCHEDULED")
      return "UPCOMING";

    if (status == "IN_PLAY")
      return "LIVE";

    if (status == "PAUSED")
      return "HT";

    if (status == "FINISHED")
      return "FT";

    return status;
  }



  bool isDraw() const {
    return homeGoals == awayGoals;
  }

  bool homeWon() const {
    return homeGoals > awayGoals;
  }

  bool awayWon() const {
    return awayGoals > homeGoals;
  }

  bool isLive() const {
    return status == "IN_PLAY" || status == "PAUSED";
  }

  bool isUpcoming() const {
    return status == "TIMED";
  }
};