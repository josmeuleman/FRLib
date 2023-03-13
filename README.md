# FRLib
 FlightRecorder Library for Arduino IDE


FRButton:
Class: Button
	Button();
	Button(int pinNumber);
	Button(int pinNumber, bool _inverted);
	void SetPinNumber(int pinNumber);
	bool Update();
	bool GetState();
	bool HasChanged();
	bool HasChangedUp();
	bool HasChangedDown();
  
FRLED:
Class: LED
	LED();
	LED(int pinNumber);	
	void SetPinNumber(int pinNumber);
	void SetState(bool state);
	void SetOn();
	void SetOff();
	void Toggle();
	
FRPPMReceiver
Class: PPMReceiver
	PPMReceiver(int pinNumber, int numberOfChannels);
	void SetLowPassFilter(float* alphaValues);
	float GetLowPassFilter(int channel);
	void Update();
	float ReadChannel(int ChannelNumber);

FRTimer	
Class Timer
  Timer();
  Timer(uint32_t loopTimeMS);
  void SetLoopTime(uint32_t loopTimeMS);
  void Start();
  bool WaitUntilEnd();
  long GetLoopDuration();
  bool IsTimeFor();
  
FRGeneric
  