#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <Arduino.h>

struct timestamp_t {
  long int displaySeconds;
  long int displayMinutes;
  long int displayHours;
  long int tick;
};

void setTimeTick(struct timestamp_t *timestamp);
void initializeCurrentTime(struct timestamp_t *timestamp);
String formatTimeText(struct timestamp_t *timestamp);
void incrementCurrentTime(struct timestamp_t *timestamp);
void adjustClockHours(struct timestamp_t *timestamp);
void adjustClockMinutes(struct timestamp_t *timestamp);
void adjustClockSeconds(struct timestamp_t *timestamp);

#endif
