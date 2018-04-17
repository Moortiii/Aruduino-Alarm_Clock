#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <timestamp.hpp>

struct lcd_t {
  byte displayChoice;
  int editChoice;
  String firstRowText;
  String lastRowText;
};

void initializeDisplay(struct lcd_t *display, struct timestamp_t *timestamp);
void setCurrentTime(struct lcd_t *display, struct timestamp_t *timestamp);
void setCurrentAlarm(struct lcd_t *display, struct alarm_t *alarm);
void toggleDisplay(struct lcd_t *display);
void setLCDText(struct lcd_t *display, struct timestamp_t *timestamp, struct alarm_t *alarm);
void adjustCurrentlyDisplayedTime(struct lcd_t *display, struct timestamp_t *timestamp, struct alarm_t *alarm);
void displayLCDText();

#endif
