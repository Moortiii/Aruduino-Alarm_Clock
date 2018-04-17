#include <lcd.hpp>
#include <LiquidCrystal.h>
#include <timestamp.hpp>
#include <alarm.hpp>

void setCurrentTime(struct lcd_t *display, struct timestamp_t *timestamp) {
  display->lastRowText = "Current Time";
  display->firstRowText = formatTimeText(timestamp);
}

void setAlarmTime(struct lcd_t *display, struct alarm_t *alarm) {
  display->lastRowText = "Alarm";
  display->firstRowText = formatAlarmText(alarm);
}

void initializeDisplay(struct lcd_t *display, struct timestamp_t *timestamp) {
  display->editChoice = 0;
  setCurrentTime(display, timestamp);
}

void toggleDisplay(struct lcd_t *display) {
  display->displayChoice = !display->displayChoice;
}

void setLCDText(struct lcd_t *display, struct timestamp_t *timestamp, struct alarm_t *alarm) {
  display->displayChoice == LOW ? setCurrentTime(display, timestamp) : setAlarmTime(display, alarm);
}

void adjustCurrentlyDisplayedTime(struct lcd_t *display, struct timestamp_t *timestamp, struct alarm_t *alarm) {
  if(display->displayChoice == LOW) {
    switch(display->editChoice) {
      case 0:
        break;
      case 1:
        adjustClockHours(timestamp);
        break;
      case 2:
        adjustClockMinutes(timestamp);
        break;
      case 3:
        adjustClockSeconds(timestamp);
        break;
      default:
        display->editChoice = 0;
        break;
    }
  } else if(display->displayChoice == HIGH) {
    switch(display->editChoice) {
      case 0:
        break;
      case 1:
        adjustAlarmHours(alarm);
        break;
      case 2:
        adjustAlarmMinutes(alarm);
        break;
      case 3:
        adjustAlarmSeconds(alarm);
        break;
      default:
        saveAlarm(alarm);
        display->editChoice = 0;
        break;
    }
  }
}
