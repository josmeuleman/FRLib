#include "Arduino.h"
#include "FRButton.h"

FRButton::FRButton() {
  _pinNumber = -1;
  _isPushed = false;
  _inverted = false;
}

FRButton::FRButton(int pinNumber) {
  _pinNumber = pinNumber;
  _isPushed = false;
  _inverted = false;
  pinMode(pinNumber, INPUT);
}

FRButton::FRButton(int pinNumber, bool inverted) {
  _pinNumber = pinNumber;
  _isPushed = false;
  _inverted = inverted;
  pinMode(pinNumber, INPUT);
}

bool FRButton::GetState() {
  _isPushed = _inverted ^ digitalRead(_pinNumber);
  return _isPushed;
}

bool FRButton::HasChanged() {
  bool oldState = _isPushed;
  _isPushed = GetState();
  return _isPushed ^ oldState;
}

bool FRButton::HasChangedUp() {
  bool oldState = _isPushed;
  _isPushed = GetState();
  return _isPushed > oldState;
}

bool FRButton::HasChangedDown() {
  bool oldState = _isPushed;
  _isPushed = GetState();
  return _isPushed < oldState;
}
