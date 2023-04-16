
// Class for receiving PPM signals
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRPPMReceiverManager_h
#define FRPPMReceiverManager_h

#include <FRSensorManager.h>

class PPMReceiverManager : public SensorManager{
  public:
  PPMReceiverManager(int pinNumber, int numberOfChannels);
  ~PPMReceiverManager();
  
  void Init();
  void SetPrefix(String prefix);
  
  void Update();
  int ReadChannel(int ChannelNumber);
  
  String HeaderString() override;
  String SensorString() override;
  
  private:
  int _pinNumber;
  int _numberOfChannels;
  static volatile unsigned long _lastPulseUS;
  static volatile uint16_t _channel;
  static volatile int* _channelValues;
  
  static PPMReceiverManager* _instance;
  const int _MAXPULSEWIDTH = 1800;
  const int _MINPULSEWIDTH = 400;
  const int _PULSETHRESHUS = 3000; // Threshold for pulse duration in microseconds
  String _prefix = "Ch";  
  
  void CountPulse();
  static void ppm_isr(void* arg);  
  

};


#endif