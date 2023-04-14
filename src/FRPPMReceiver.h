
// Class for receiving PPM signals
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRPPMReceiver_h
#define FRPPMReceiver_h

#include <FRSensorManager.h>

class PPMReceiver : public SensorManager{
  public:
  PPMReceiver(int pinNumber, int numberOfChannels);
  void SetLowPassFilter(float* alphaValues);
  float GetLowPassFilter(int channel);
  
  void Update();
  float ReadChannel(int ChannelNumber);

  String HeaderString() override;
  String SensorString() override;
  
  private:
  int _pinNumber;
  int _numberOfChannels;
  float* _channelValues;
  float* _alphaValues;
  const int _MAXPULSEWIDTH = 1800;
  const int _MINPULSEWIDTH = 400;
  const int _PULSETHRESHUS = 3000; // Threshold for pulse duration in microseconds 

};


#endif