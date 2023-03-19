#include "Arduino.h"
#include "FRTimer.h"

Timer::Timer() {
  _loopTimeMS = 0;
  _startTime = millis();
  _hasOverRun = false;
}

Timer::Timer(uint32_t loopTimeMS) {
  if (loopTimeMS > 0) {
    _loopTimeMS = loopTimeMS;
  } else {
    _loopTimeMS = 0;
  }
  _startTime = millis();
  _hasOverRun = false;
}

void Timer::SetLoopTime(uint32_t loopTimeMS) {
  if (loopTimeMS > 0) {
    _loopTimeMS = loopTimeMS;
  }
}

void Timer::Start(){
  _startTime = millis();
}

bool Timer::WaitUntilEnd() {
  long tNow = millis();
  _loopDuration = tNow - _startTime;
  if (_loopDuration > _loopTimeMS) {
    _hasOverRun = true;
  } 
  else {
    while (millis() < _startTime + _loopTimeMS) {}
    _hasOverRun = false;
  }
  _startTime = millis();
  return _hasOverRun;
}

long Timer::GetLoopDuration(){
  return _loopDuration;
}
	
bool Timer::LoopTimePassed(){
  long tNow = millis();
  _loopDuration = tNow - _startTime;
  if (_loopDuration >= _loopTimeMS) {
	_startTime = millis();
	return true;
  }
  else {
	return false;
  }
  
}
