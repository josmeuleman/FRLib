// Class for binary outputs such as LEDs
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "Arduino.h"
#include "FRLED.h"

LED* LED::_instance = nullptr; // Initialize the static member variable

LED::LED() {
  _instance = this; // Store a pointer to this instance
  _pinNumber = -1;
  _isOn = false;
  _blinkMode = false;

}

LED::LED(int pinNumber) {
  _instance = this; // Store a pointer to this instance
  _pinNumber = pinNumber;
  _isOn = false;
  _blinkMode = false;   
  pinMode(_pinNumber, OUTPUT);
}
LED::~LED() {
  delete _timer;
}

void LED::SetPinNumber(int pinNumber) {
  _pinNumber = pinNumber;
  pinMode(_pinNumber, OUTPUT);
}

void LED::Init() {
  _timer = timerBegin(0, 80, true);
  timerAttachInterrupt(_timer, &LED::onTimer, true);
}

void LED::SetState(bool state) {
  digitalWrite(_pinNumber, state);
}

void LED::SetOn() {
  _isOn = true;
  SetState(_isOn);
  _blinkMode = false;  
  timerAlarmDisable(_timer);

}

void LED::SetOff() {
  _isOn = false;
  SetState(_isOn);
  _blinkMode = false;
  timerAlarmDisable(_timer);

}

void LED::Toggle() {
  _isOn = !_isOn;
  SetState(_isOn);
}

void LED::SetBlink(int interval) {
  _blinkIntervalUs = interval * 1000;
  _blinkMode = true;
  timerAlarmWrite(_timer, _blinkIntervalUs, true);
  timerAlarmEnable(_timer);
}

void IRAM_ATTR LED::onTimer() {
  static bool ledState = false;
  digitalWrite(_instance->_pinNumber, ledState);
  ledState = !ledState;
}

