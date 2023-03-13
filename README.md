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
	
FRPPMReceiver:
Class: PPMReceiver
	PPMReceiver(int pinNumber, int numberOfChannels);
	void SetLowPassFilter(float* alphaValues);
	float GetLowPassFilter(int channel);
	void Update();
	float ReadChannel(int ChannelNumber);

FRTimer:
Class Timer
	Timer();
	Timer(uint32_t loopTimeMS);
	void SetLoopTime(uint32_t loopTimeMS);
	void Start();
	bool WaitUntilEnd();
	long GetLoopDuration();
	bool IsTimeFor();
  
FRGeneric:
String createTimeString(int hour, int minute, int second)
String createDateString(int year, int month, int day)
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
  