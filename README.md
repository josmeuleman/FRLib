# FRLib
FlightRecorder Library for Arduino IDE. This library contains sublibraries and examples for making a flight recorder for an ESP32.
The library is written for the Project2.2 for Aeronautical & Precision Engineerring at Inholland, Delft.

## FRGeneric
Generic functions for several sub libraries
Usage and methods:

	#include <FRGeneric.h>
	String createTimeString(int hour, int minute, int second)
	String createDateString(int year, int month, int day)
	String createFloatString(float value, unsigned int accuracy)
	String createIntString(int value)
	float mapf(float x, float in_min, float in_max, float out_min, float out_max) 

All generated strings are ended with a "; ". This is conventient for plotting signals in the Serial monitor, and for writing to a csv file.


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

	#include <FRLED.h>
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
The PPMReceiver class creates a listener to a PPM signal.
Usage and Methods:

    #include <FRPPMReceiver.h>
	PPMReceiver(int pinNumber, int numberOfChannels);
    void SetLowPassFilter(float* alphaValues);
    float GetLowPassFilter(int channel);
    void Update();
    float ReadChannel(int ChannelNumber);

Examples:
FRPPMReceiverTest.ino

## FRTimer
The Timer class reates a timer object that uses the millis() command to ensure timing accurate timing of a loop
Usage and Methods:
	
	#include <FRTimer.h> 
	Timer();
	Timer(uint32_t loopTimeMS);
	void SetLoopTime(uint32_t loopTimeMS);
	void Start();
	bool WaitUntilEnd();
	long GetLoopDuration();
	bool LoopTimePassed();
  
Examples:
FRTimerDemo.ino
FRTimerAndOverSamplingDemo.ino

## FRLogger
The Logger class creates a handler for logging data to an SD cards. The FRLogger uses a generic sensor class, FRSensorManager. For the usage of FRSensorManager, see next section.
Usage and Methods:

	#include <FRLogger.h>
	Logger();
	bool CheckSD();
	void AddSensor(SensorManager* Sensor);
	String GetLoggerFileName();
	bool IsLogging();
	bool StartLogger();
	bool StopLogger();
	String UpdateSensors();
	void WriteLogger();	

Examples:
FRLoggerDemo.ino

## FRSensorManager
The SensorManager class is a parent class for specific sensor manager. The Logger monitors objects of the class SensorManager. In specific classes of SensorManagers, the methods are implemented
Usage and Methods:
	
	#include <FRSensorManager.h>
	String HeaderString();
	String SensorString();


## FRMPU6050Manager
The MPU6050Manager class is a class for specifically logging an MPU6050 sensor. It is derived from the SensorManager class. Internally it uses the library Adafruit_MPU6050

	MPU6050Manager();
	~MPU6050Manager();
	bool Init(TwoWire &myWire, mpu6050_accel_range_t accelRange, mpu6050_gyro_range_t gyroRange)
	String HeaderString() override;
	String SensorString() override;

Note that:
- The method init expects the I2C communication to be running
- The method init requires a range for the accelerometer and the gyro. The values are defined in the library Adafruit_MPU6050

Examples:
FRLoggerDemo.ino
