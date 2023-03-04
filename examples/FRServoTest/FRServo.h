#ifndef FRServo_h
#define FRServo_h

class Servo {
  public:
  Servo();
  Servo(int pinNumber);
  
  void SetPinNumber(int pinNumber);
  void SetMaxSpeed(int maxSpeed);
  void SetTargetPos(int targetPos);

  bool Update();
  bool IsOnTarget();
  
  private:
  int _pinNumber;
  int _targetPos;
  int _currentPos;
  float _maxSpeed;
  bool _isOnTarget;
  long _lastUpdateTime;

};
#endif