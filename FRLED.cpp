#include "Arduino.h"
#include "FRLED.h"

FRLED::FRLED() {
  _pinNumber = -1;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkPattern = NULL;
}

FRLED::FRLED(int pinNumber) {
  _pinNumber = pinNumber;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkPattern = NULL;
  pinMode(_pinNumber, OUTPUT);
}

void FRLED::SetPinNumber(int pinNumber) {
  _pinNumber = pinNumber;
  pinMode(_pinNumber, OUTPUT);
}

void FRLED::SetState(bool state) {
  digitalWrite(_pinNumber, state);
}
void FRLED::SetOn() {
  _isOn = true;
  SetState(_isOn);
}

void FRLED::SetOff() {
  _isOn = false;
  SetState(_isOn);
}

void FRLED::Toggle() {
  _isOn = !_isOn;
  SetState(_isOn);
}

