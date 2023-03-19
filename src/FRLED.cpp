// Class for binary outputs such as LEDs
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "Arduino.h"
#include "FRLED.h"

LED::LED() {
  _pinNumber = -1;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkMode = false;    
}

LED::LED(int pinNumber) {
  _pinNumber = pinNumber;
  _isOn = false;
  _lastTimeMS = 0;
  _blinkMode = false;   
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
  _blinkMode = false;  
}

void LED::SetOff() {
  _isOn = false;
  SetState(_isOn);
  _blinkMode = false;
}

void LED::Toggle() {
  _isOn = !_isOn;
  SetState(_isOn);
}

void LED::SetBlink(int onTimeMS, int offTimeMS) {
  _onTimeMS = onTimeMS;
  _offTimeMS = offTimeMS;
  _lastTimeMS = millis();
  _blinkMode = true;
}

void LED::Update(){
  long dt = millis() - _lastTimeMS;
  if (!_blinkMode) {
	return;
  }
  if (dt<_onTimeMS) {
	SetState(true);
	return;
  }
  if (dt< (_onTimeMS + _offTimeMS)) {
	SetState(false);
	return;
  }
  else {
	SetState(true);
	_lastTimeMS = millis();
  }
}


