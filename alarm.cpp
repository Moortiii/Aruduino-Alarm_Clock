#include <alarm.hpp>
#include <timestamp.hpp>
#include <EEPROM.h>
#include <conversion.hpp>

void intializeAlarm(struct alarm_t *alarm) {
  alarm->displayHours = 0;
  alarm->displayMinutes = 0;
  alarm->displaySeconds = 0;
  alarm->enabled = 0;
  alarm->tick = 0;
  readAlarmFromEEPROM(alarm);
}

void readAlarmFromEEPROM(struct alarm_t *alarm) {
  struct alarm_t stored_alarm;
  EEPROM.get(0, stored_alarm);
  *alarm = stored_alarm;
}

void toggleAlarm(struct alarm_t *alarm) {
  alarm->enabled < 2 ? alarm->enabled++ : alarm->enabled = 0;
}

boolean alarmShouldSound(struct alarm_t *alarm, struct timestamp_t *timestamp) {
  switch(alarm->enabled) {
    case 0:
      return false;
    case 1:
      return timestamp->tick >= alarm->tick;
    case 2:
      return timestamp->tick >= alarm->tick + (60 * 5);
  }
}

void addAlarmToEEPROM(struct alarm_t *alarm) {
  EEPROM.put(0, *alarm);
}

// Save the alarm to EEPROM and display a message to the user
void saveAlarm(struct alarm_t *alarm) {
  alarm->enabled = 1;
  setAlarmTick(alarm);
  addAlarmToEEPROM(alarm);
}

void setAlarmTick(struct alarm_t *alarm) {
  alarm->tick =
    (alarm->displayHours * 3600) +
    (alarm->displayMinutes * 60) +
    (alarm->displaySeconds);
}

void adjustAlarmHours(struct alarm_t *alarm) {
  alarm->displayHours = convertPotToHours();
}

void adjustAlarmMinutes(struct alarm_t *alarm) {
  alarm->displayMinutes = convertPotToMinOrSec();
}

void adjustAlarmSeconds(struct alarm_t *alarm) {
  alarm->displaySeconds = convertPotToMinOrSec();
}

void soundAlarm(const int PIEZO) {
  tone(PIEZO, 200, 500);
}

void powerAlarmLED(struct alarm_t *alarm, const int LED_1) {
  alarm->enabled == 1 ? digitalWrite(LED_1, HIGH) : digitalWrite(LED_1, LOW);
}

void powerSnoozeLED(struct alarm_t *alarm, const int LED_2) {
  alarm->enabled == 2 ? digitalWrite(LED_2, HIGH) : digitalWrite(LED_2, LOW);
}

String formatAlarmText(struct alarm_t *alarm) {
  String fs = String(alarm->displaySeconds);
  String fm = String(alarm->displayMinutes);
  String fh = String(alarm->displayHours);

  if(alarm->displaySeconds < 10)
    fs = "0" + String(alarm->displaySeconds);
  if(alarm->displayMinutes < 10)
    fm = "0" + String(alarm->displayMinutes);
  if(alarm->displayHours < 10)
    fh = "0" + String(alarm->displayHours);

  return String(fh) + ":" + String(fm) + ":" + String(fs);
}
