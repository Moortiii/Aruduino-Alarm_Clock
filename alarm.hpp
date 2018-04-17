#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

// Define a structure to manage timestamps
struct alarm_t {
  long int displaySeconds;
  long int displayMinutes;
  long int displayHours;
  long int enabled;
  long int tick;
};

void saveAlarm(struct alarm_t *alarm);
void intializeAlarm(struct alarm_t *alarm);
void readAlarmFromEEPROM(struct alarm_t *alarm);
void toggleAlarm(struct alarm_t *alarm);
void addAlarmToEEPROM(struct alarm_t *alarm);
void setAlarmTick(struct alarm_t *alarm);
void adjustAlarmHours(struct alarm_t *alarm);
void adjustAlarmMinutes(struct alarm_t *alarm);
void adjustAlarmSeconds(struct alarm_t *alarm);
void soundAlarm(const int PIEZO);
void powerAlarmLED(struct alarm_t *alarm, const int LED_1);
void powerSnoozeLED(struct alarm_t *alarm, const int LED_2);
String formatAlarmText(struct alarm_t *alarm);
boolean alarmShouldSound(struct alarm_t *alarm, struct timestamp_t *timestamp);

#endif
