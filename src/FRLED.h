// Class for binary outputs such as LEDs
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRLED_h
#define FRLED_h

class LED {
  public:
  LED();
  LED(int pinNumber);
  ~LED();

  void SetPinNumber(int pinNumber);
  void Init();

  //void Update();
  void SetState(bool state);
  void SetOn();
  void SetOff();
  void Toggle();
  void SetBlink(int interval);
  void Update();
  
private:
  int _pinNumber;
  bool _isOn;
  bool _blinkMode;
  int _timerInterval;
  hw_timer_t *_timer = NULL;
  
  static void IRAM_ATTR onTimer();
  uint32_t _blinkIntervalUs = 500000;
  static LED* _instance;

};

#endif