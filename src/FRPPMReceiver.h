#ifndef FRPPMReceiver_h
#define FRPPMReceiver_h


class PPMReceiver {
  public:
  PPMReceiver(int pinNumber, int numberOfChannels);
  void SetLowPassFilter(float* alphaValues);
  float GetLowPassFilter(int channel);
  
  void Update();
  float ReadChannel(int ChannelNumber);

  private:
  int _pinNumber;
  int _numberOfChannels;
  float* _channelValues;
  float* _alphaValues;
  //const int _TIMEOUTUS = 100000; // Timeout for pulse duration in microseconds
  const int _MAXPULSEWIDTH = 1800;
  const int _MINPULSEWIDTH = 400;
  const int _PULSETHRESHUS = 3000; // Threshold for pulse duration in microseconds 

};


#endif