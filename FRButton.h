#ifndef FRButton_h
#define FRButton_h

class Button {
  public:
  Button();
  Button(int pinNumber);
  Button(int pinNumber, bool _inverted);
  
  void SetPinNumber(int pinNumber);
  
  bool Update();
  bool GetState();
  bool HasChanged();
  bool HasChangedUp();
  bool HasChangedDown();

  private:
  int _pinNumber;
  bool _isPushed;
  bool _inverted;
  bool _prevState;


};

#endif