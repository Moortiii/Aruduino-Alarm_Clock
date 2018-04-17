#ifndef DATA_H
#define DATA_H

#include <LiquidCrystal.h>
#include <timestamp.hpp>
#include <alarm.hpp>
#include <lcd.hpp>

// Define button PINs
const int BTN_1 = 2;
const int BTN_2 = 3;
const int BTN_3 = 11;

// Define LED PINs
const int LED_1 = 12;
const int LED_2 = 13;

// Define PIEZO PIN
const int PIEZO = 10;

// Define LCD PINs
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Create the structures to store our two timestamps
struct timestamp_t *timestamp = (timestamp_t*)malloc(sizeof(timestamp_t));
struct alarm_t *alarm = (alarm_t*)malloc(sizeof(alarm_t));
struct lcd_t *display = (lcd_t*)malloc(sizeof(lcd_t));

// Keep interrupts from triggering too often
unsigned long lastInterrupt = millis();

#endif
