#include "hl_state3034.h"

void HL_State_3034::setState(uint8_t state) {
  _state = state;
}
uint8_t HL_State_3034::getState() {
  return _state;
}

void HL_State_3034::cycleState() {
  //   c = (c + 1) % 7;
  setState ((getState() + 1) % 7);
}

void HL_State_3034::setInterval(long interval) {
  _interval = interval;
}

long HL_State_3034::getInterval() {
  return _interval;
}
