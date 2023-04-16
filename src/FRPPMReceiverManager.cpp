// Class for receiving PPM signals, and add it to logger
// 
// 2023-04-16, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "Arduino.h"
#include "FRPPMReceiverManager.h"
#include "FRGeneric.h"

PPMReceiverManager* PPMReceiverManager::_instance = nullptr;

volatile unsigned long PPMReceiverManager::_lastPulseUS;
volatile uint16_t PPMReceiverManager::_channel;
volatile int* PPMReceiverManager::_channelValues;

PPMReceiverManager::PPMReceiverManager(int pinNumber, int numberOfChannels) {
  _instance = this; // Store a pointer to this instance
  _numberOfChannels = numberOfChannels;
  _pinNumber = pinNumber;
 
  if (_channelValues != 0) {
    delete[] _channelValues;
  }
  _channelValues = new int[_numberOfChannels];
  
  for (int i = 0; i < _numberOfChannels; i++) {
	_channelValues[i] = 0;
  }
  _channel = 0;
}

PPMReceiverManager::~PPMReceiverManager() {
  detachInterrupt(_pinNumber);
  delete[] _channelValues;
}

void PPMReceiverManager::Init(){
  pinMode(_pinNumber, INPUT);
  attachInterruptArg(digitalPinToInterrupt(_pinNumber), ppm_isr, this, CHANGE);
  _lastPulseUS = micros();
}


void PPMReceiverManager::SetPrefix(String prefix) {
  _prefix = prefix; 
}

int PPMReceiverManager::ReadChannel(int ChannelNumber) {
  if ((ChannelNumber >= 0) && (ChannelNumber < _numberOfChannels)) {
    return (_channelValues[ChannelNumber]);
  } 
  else {
    return (0);
  }
}

String PPMReceiverManager::HeaderString(){
  String tempString;
  for (int i = 0; i < _numberOfChannels; i++) {
	tempString.concat(_prefix);
	tempString.concat(i);
	tempString.concat("; ");
  }
  return tempString;
}

String PPMReceiverManager::SensorString(){
  String tempString;
  for (int i = 0; i < _numberOfChannels; i++) {
	tempString.concat(createFloatString(_channelValues[i], 2));  
  }
  return tempString;
}

void PPMReceiverManager::CountPulse() {
  unsigned long tNow = micros();
  if (digitalRead(_pinNumber)) {
    _lastPulseUS = micros();
  } else {
    long x = tNow - _lastPulseUS;
    _lastPulseUS = tNow;
    if (x > _PULSETHRESHUS) {
      _channel = 0;
    }
    else {
	  if (_channel < _numberOfChannels) {
	    _channelValues[_channel] = x;
        _channel++;
	  }
	}
  }  
}

void IRAM_ATTR PPMReceiverManager::ppm_isr(void* arg) {
  PPMReceiverManager* receiver = reinterpret_cast<PPMReceiverManager*>(arg);
  receiver->CountPulse();
}
