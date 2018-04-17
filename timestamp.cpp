#include <timestamp.hpp>
#include <conversion.hpp>

void initializeCurrentTime(struct timestamp_t *timestamp) {
  timestamp->displayHours = 12;
  timestamp->displayMinutes = 0;
  timestamp->displaySeconds = 0;
  setTimeTick(timestamp);
}

void setTimeTick(struct timestamp_t *timestamp) {
  timestamp->tick =
    (timestamp->displayHours * 3600) +
    (timestamp->displayMinutes * 60) +
    (timestamp->displaySeconds);
}

void adjustClockHours(struct timestamp_t *timestamp) {
  timestamp->displayHours = convertPotToHours();
}

void adjustClockMinutes(struct timestamp_t *timestamp) {
  timestamp->displayMinutes = convertPotToMinOrSec();
}

void adjustClockSeconds(struct timestamp_t *timestamp) {
  timestamp->displaySeconds = convertPotToMinOrSec();
}

// Returns a timestamp formatted as HH:MM:SS
String formatTimeText(struct timestamp_t *timestamp) {
  String fs = String(timestamp->displaySeconds);
  String fm = String(timestamp->displayMinutes);
  String fh = String(timestamp->displayHours);

  if(timestamp->displaySeconds < 10)
    fs = "0" + String(timestamp->displaySeconds);
  if(timestamp->displayMinutes < 10)
    fm = "0" + String(timestamp->displayMinutes);
  if(timestamp->displayHours < 10)
    fh = "0" + String(timestamp->displayHours);

  return String(fh) + ":" + String(fm) + ":" + String(fs);
}

// Simple incrementing clock
void incrementCurrentTime(struct timestamp_t *timestamp) {
  timestamp->displaySeconds++;

  if(timestamp->displaySeconds > 59) {
    timestamp->displaySeconds = 0;
    timestamp->displayMinutes++;
  }

  if(timestamp->displayMinutes > 59) {
    timestamp->displayMinutes = 0;
    timestamp->displayHours++;
  }

  if(timestamp->displayHours > 23) {
    timestamp->displayHours =
      timestamp->displayMinutes =
      timestamp->displaySeconds = 0;
  }

  setTimeTick(timestamp);
}
