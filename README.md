# FRLib
 FlightRecorder Library for Arduino IDE. This library contains sublibraries and examples for making a flight recorder for an ESP32.
 The library is written for the Project2.2 for Aeronautical & Precision Engineerring at Inholland, Delft.
 

## FRButton

The class button is allows for monitoring binary sensors such as buttons. 
Usage and Methods:

    #include <FRButton.h>
    Button();
    Button(int pinNumber);
    Button(int pinNumber, bool inverted);
    void SetPinNumber(int pinNumber);
    bool Update();
    bool GetState();
    bool HasChanged();
    bool HasChangedUp();
    bool HasChangedDown();
  Examples:
  FRButtonLEDTest.ino

## FRLED
The class LED is allows for controlling binary outputs such as LEDs. 
Usage and Methods:

	LED();
	LED(int pinNumber);	
	void SetPinNumber(int pinNumber);
	void SetState(bool state);
	void SetOn();
	void SetOff();
	void Toggle();
	
Examples:
FRButtonLEDTest.ino

## FRPPMReceiver
The PPMReceiver creates a listener to a PPM signal.
Usage and Methods:

    PPMReceiver(int pinNumber, int numberOfChannels);
    void SetLowPassFilter(float* alphaValues);
    float GetLowPassFilter(int channel);
    void Update();
    float ReadChannel(int ChannelNumber);
Examples:

FRTimer:
Class Timer
	Timer();
	Timer(uint32_t loopTimeMS);
	void SetLoopTime(uint32_t loopTimeMS);
	void Start();
	bool WaitUntilEnd();
	long GetLoopDuration();
	bool LoopTimePassed();
  
FRGeneric:
String createTimeString(int hour, int minute, int second)
String createDateString(int year, int month, int day)
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
  

