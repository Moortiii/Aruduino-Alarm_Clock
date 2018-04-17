#include <conversion.hpp>
#include <Arduino.h>

int convertPotToHours() {
  return map(analogRead(A0), 0, 1023, 0, 23);
}

int convertPotToMinOrSec() {
  return map(analogRead(A0), 0, 1023, 0, 59);
}
