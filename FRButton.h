#ifndef FRButton_h
#define FRButton_h

class FRButton {
  public:
  FRButton();
  FRButton(int pinNumber);
  FRButton(int pinNumber, bool _inverted);
  
  void SetPinNumber(int pinNumber);
  
  bool GetState();
  bool HasChanged();
  bool HasChangedUp();
  bool HasChangedDown();

  private:
  int _pinNumber;
  bool _isPushed;
  bool _inverted;


};

#endif