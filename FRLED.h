#ifndef FRLED_h
#define FRLED_h

class FRLED {
  public:
  FRLED();
  FRLED(int pinNumber);

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