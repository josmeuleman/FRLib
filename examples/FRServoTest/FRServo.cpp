#include "Arduino.h"
#include "FRServo.h"

Servo::Servo() {
  _pinNumber = -1;
  _targetPos = -1;
  _currentPos = -1;
  _maxSpeed = -1;
  _isOnTarget = false;
  _lastUpdateTime = 0;
}

Servo::Servo(int pinNumber) {
  _pinNumber = pinNumber;
  _targetPos = -1;
  _currentPos = -1;
  _maxSpeed = -1;
  _isOnTarget = false;
  _lastUpdateTime = 0;
  pinMode(_pinNumber, OUTPUT);
}

void Servo::SetPinNumber(int pinNumber) {
  _pinNumber = pinNumber;
  pinMode(_pinNumber, OUTPUT);
}

void Servo::SetMaxSpeed(int maxSpeed) {
  _maxSpeed = maxSpeed;
}

void Servo::SetTargetPos(int targetPos){
  _targetPos = targetPos;
}

bool Servo::Update(){
  long tNow = millis();
  long dT = tNow - _lastUpdateTime;
  _lastUpdateTime = tNow;

  if (_maxSpeed<0){
    _currentPos = _targetPos;
  }
  else {
    long maxStep = dT*_maxSpeed;
    int sign = 0;
    int deltaPos = _targetPos - _currentPos;
    if (deltaPos > 0) {
      sign = 1;
    }
    else if (deltaPos < 0) {
      sign = -1;
    }
    if (deltaPos*sign > maxStep) {
      deltaPos = sign*maxStep;
    }
    _currentPos +=deltaPos;
  }
  Serial.print(_currentPos);
  Serial.print("; ");
  analogWrite(_pinNumber, _currentPos);
  return IsOnTarget();

}

bool Servo::IsOnTarget(){
  if ((_targetPos>0) & (_currentPos>0) & (_targetPos==_currentPos)) {
    _isOnTarget = true;
  }
  else {
    _isOnTarget = false;
  }
  return _isOnTarget;


}