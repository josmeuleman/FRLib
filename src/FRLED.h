// Class for binary outputs such as LEDs
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRLED_h
#define FRLED_h

class LED {
  public:
  LED();
  LED(int pinNumber);

  void SetPinNumber(int pinNumber);
  //void SetBlinkMode(int* blinkPattern);

  //void Update();
  void SetState(bool state);
  void SetOn();
  void SetOff();
  void Toggle();
  
  private:
  int _pinNumber;
  bool _isOn;
  long _lastTimeMS;
  int* _blinkPattern;

};


#endif