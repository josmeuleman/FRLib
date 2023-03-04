#include "Arduino.h"
#include "FRPPMReceiver.h"

PPMReceiver::PPMReceiver(int pinNumber, int numberOfChannels) {
  _numberOfChannels = numberOfChannels;
  _pinNumber = pinNumber;
  if (_channelValues != 0) {
    delete[] _channelValues;
  }
  _channelValues = new float[_numberOfChannels];
  if (_alphaValues != 0) {
    delete[] _alphaValues;
  }
  _alphaValues = new float[_numberOfChannels];

  for (int i = 0; i < _numberOfChannels; i++) {
    _channelValues[i] = 0.0;
    _alphaValues[i] = 1.0;
  }
  pinMode(_pinNumber, INPUT);
}

void PPMReceiver::SetLowPassFilter(float* alphaValues) {
  for (int i = 0; i < _numberOfChannels; i++) {
    if ((alphaValues[i] > 0.0) & (alphaValues[i] <= 1.0)) {
      _alphaValues[i] = alphaValues[i];
    } else {
      _alphaValues[i] = 1.0;
    }
  }
}

float PPMReceiver::GetLowPassFilter(int channel) {
  return (_alphaValues[channel]);	
}

void PPMReceiver::Update() {
  if (pulseIn(_pinNumber, HIGH) > _PULSETHRESHUS) { //If pulse > 3000 useconds, continues
    for (int i = 0; i < _numberOfChannels; i++) {
      int x = pulseIn(_pinNumber, HIGH);
      if ((x < _MAXPULSEWIDTH) && (x > _MINPULSEWIDTH)) {
		  
		float x_ = (x - _MINPULSEWIDTH) * 2.0/(_MAXPULSEWIDTH - _MINPULSEWIDTH) - 1.0;
        float a = _alphaValues[i];
        float a_ = 1.0 - a;
        _channelValues[i] = a * x_ + a_ * _channelValues[i];
      }
    }
  }
}

float PPMReceiver::ReadChannel(int ChannelNumber) {
  if ((ChannelNumber >= 0) && (ChannelNumber < _numberOfChannels)) {
    return (_channelValues[ChannelNumber]);
  } 
  else {
    return (0);
  }
}
