#include "Arduino.h"
#include "FRButton.h"

Button::Button() {
  _pinNumber = -1;
  _isPushed = false;
  _inverted = false;
}

Button::Button(int pinNumber) {
  _pinNumber = pinNumber;
  _isPushed = false;
  _inverted = false;
  pinMode(pinNumber, INPUT);
}

Button::Button(int pinNumber, bool inverted) {
  _pinNumber = pinNumber;
  _isPushed = false;
  _inverted = inverted;
  pinMode(pinNumber, INPUT);
}

void Button::SetPinNumber(int pinNumber) {
  _pinNumber = pinNumber;
  pinMode(_pinNumber, INPUT);
}

bool Button::Update() {
  _prevState = _isPushed;
  _isPushed = _inverted ^ digitalRead(_pinNumber);
  return _isPushed;
}
bool Button::GetState() {
  return _isPushed;
}

bool Button::HasChanged() {
  return _isPushed ^ _prevState;
}

bool Button::HasChangedUp() {
  _isPushed = GetState();
  return _isPushed > _prevState;
}

bool Button::HasChangedDown() {
  _isPushed = GetState();
  return _isPushed < _prevState;
}
