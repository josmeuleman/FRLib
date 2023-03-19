#include "Arduino.h"
#include "FRLED.h"

LED::LED() {
  _pinNumber = -1;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkPattern = NULL;
}

LED::LED(int pinNumber) {
  _pinNumber = pinNumber;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkPattern = NULL;
  pinMode(_pinNumber, OUTPUT);
}

void LED::SetPinNumber(int pinNumber) {
  _pinNumber = pinNumber;
  pinMode(_pinNumber, OUTPUT);
}

void LED::SetState(bool state) {
  digitalWrite(_pinNumber, state);
}
void LED::SetOn() {
  _isOn = true;
  SetState(_isOn);
}

void LED::SetOff() {
  _isOn = false;
  SetState(_isOn);
}

void LED::Toggle() {
  _isOn = !_isOn;
  SetState(_isOn);
}

