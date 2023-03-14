#ifndef FRTimer_h
#define FRTimer_h


class Timer{
  public:
  Timer();
  Timer(uint32_t loopTimeMS);

  void SetLoopTime(uint32_t loopTimeMS);
  void Start();
  bool WaitUntilEnd();
  long GetLoopDuration();
  bool LoopTimePassed();


  private:
  uint _loopTimeMS;
  long _startTime;
  bool _hasOverRun;
  long _loopDuration; 
};

#endif