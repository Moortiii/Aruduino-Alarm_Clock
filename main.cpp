// Include necessary libraries
#include <LiquidCrystal.h>
#include <Arduino.h>
#include <alarm.hpp>
#include <timestamp.hpp>
#include <lcd.hpp>
#include <conversion.hpp>
#include <data.hpp>

void displayLCDText() {
  setLCDText(display, timestamp, alarm);
  lcd.clear();
  lcd.print(display->firstRowText);
  lcd.setCursor(0, 2);
  lcd.print(display->lastRowText);
}

// Toggles between displaying the alarm and current time
void toggleDisplayInterrupt() {
  if(millis() - lastInterrupt > 200)
      toggleDisplay(display);

  lastInterrupt = millis(); // Prevents multiple triggers from fluctuation
}

void toggleEditingInterrupt() {
  if(millis() - lastInterrupt > 200)
    display->editChoice++;

  lastInterrupt = millis(); // Prevents multiple triggers from fluctuation
}

void intializeInterruptTimer() {
  TCCR1A = 0; // Turn off `Compare Output Mode`
  TCCR1B = 0; // Turn off `Timer`, Reset Clock
  TCNT1 = 0; // Reset `Clock Count`
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set the pre-scaler to 1024
  OCR1A = 15625; // Set compare value (16 000 000 / 1 024)
  TCCR1B |= (1 << WGM12); // CTC = Clear Timer On Compare
  TIMSK1 |= (1 << OCIE1A); // Turn on `Output Compare Interrupt`
}

void initializePINs() {
  pinMode(BTN_1, INPUT);
  delay(1);
  pinMode(BTN_2, INPUT);
  delay(1);
  pinMode(BTN_3, INPUT);
  delay(1);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_1), toggleEditingInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_2), toggleDisplayInterrupt, FALLING);
}

void setup() {
  // Set up Serial Monitor and LCD
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Disable all interrupts before configuration
  noInterrupts();

  intializeInterruptTimer();
  initializePINs();
  intializeAlarm(alarm);
  initializeCurrentTime(timestamp);
  initializeDisplay(display, timestamp);

  // Re-enable interrupts when configuration is done
  interrupts();
}

void loop() {
  adjustCurrentlyDisplayedTime(display, timestamp, alarm);
  powerAlarmLED(alarm, LED_1);
  powerSnoozeLED(alarm, LED_2);
  delay(100);

  if(digitalRead(BTN_3) == 0) {
    if(millis() - lastInterrupt > 200) {
      toggleAlarm(alarm);
    }
    lastInterrupt = millis();
  }
}

ISR(TIMER1_COMPA_vect) {
  incrementCurrentTime(timestamp);
  displayLCDText();

  if(alarmShouldSound(alarm, timestamp)) {
    soundAlarm(PIEZO);
  }

  Serial.println("Timestamp tick: ");
  Serial.println(timestamp->tick);
  Serial.println("Alarm tick: ");
  Serial.println(alarm->tick);
}
