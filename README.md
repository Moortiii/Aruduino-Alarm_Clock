# Arduino Uno / ATMEGA 328P Alarm Clock

Digital Alarm Clock created using the Genuino Starter Kit which comes with an Arduino Uno / ATMEGA 328P. This project was created as a final assignment for a university course called Operating Systems and Microprocessors.

## Features

 - Ability to set the current time
 - Ability to set an alarm for a given time
 - Ability to switch between displaying the set alarm and current time
 - Alarm is stored in the EEPROM and will persist through a power-cycle
 - Alarm can be snoozed by 5 minutes with the press of a button
 - Piezo Speaker buzzes when the alarm is set to go off
 - Current time starts at 12:00:00 when powered on
 - LEDs indicate whether the alarm is enabled / snoozed / disabled

## Connections / Wiring
Below is a sketch of the alarm clock created using the simulator on TinkerCad. The breadboard that comes with the Genuino Starter Kit is severely limited in terms of space and so fitting everything onto the board might be challenging. We personally recommend connecting all wires that  don't require a resistor and which go from the LCD to either GND or 5V directly underneath the display as it removes a ton of clutter.

It is also possible to use the internal pull-up resistors as is done on the image below, but for the best results we recommend setting up external pull-up resistors as the Arduino Library is somewhat finicky and will occasionally bug out.

![Connections / Wiring](https://i.imgur.com/nPtXubQ.png)

## User Interface
The Alarm Clock is equipped with three buttons and a potentiometer.

**Button 1**

Pressing the first button toggles between adjusting the hours, minutes and seconds of the currently set display mode. This is done by reading the value of the potentiometer and mapping the values to a number between 0 and 23 for hours / 0 and 59 for minutes and seconds.

| Times Pressed| Function |
|- | - |
| 1 | Adjust the hours of the current alarm / time (0 - 23) |
| 2 | Adjust the minutes of the current alarm / time (0 - 59) |
| 3 | Adjust the seconds of the current alarm / time (0 - 59) |
| 4 | Save the current time / Save and enable the alarm |

**Button 2**


Pressing the second button toggles between displaying the current time and the set alarm.

**Button 3**


Pressing the third button toggles the current alarm.

| Times Pressed | Function | Indicator |
| -- | -- | -- |
| 1 | Enable the alarm | Green LED is lit |
| 2 | Snooze the alarm | Red LED is lit |
| 3 | Disable the alarm | No LED is lit |

## How does it work?

The Arduino is set to fire an interrupt every 1000ms. There are four key variables:

 1. **int** displayHours
 2. **int** displayMinutes
 3. **int** displaySeconds
 4. **long int** tick

The interrupt increases the displaySeconds by one every time it fires and a function turns this into a simple incrementing clock. Afterwards the hours, minutes and seconds are converted to a tick using the following arithmetic:

*tick = (displayHours x 3600) + (displayMinutes x 60) + displaySeconds;*

In order to check if an alarm should sound, a tick is created in the same way for the current alarm and the two numbers are compared.  One could argue that we are doing things backwards. It would be possible to store only a tick, increment it and transform it into human readable time. While this is perhaps simpler, there is one major drawback that comes to mind with this solution.

**Goal:** *The user should be able to easily adjust the current alarm / time*

Storing only a tick means the potentiometer would need to map the numbers 0 - 1023 to the range 0 - 86400 and the user would have no way to adjust the hours minutes and seconds individually. Ultimately, we decided that this would be both tedious and frustrating to the users.
