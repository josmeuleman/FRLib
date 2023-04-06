// Manager for a MPU6050 sensor. It uses the SensorManager class, such that the Logger class can log the sensor.
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRTinyGPSManager_h
#define FRTinyGPSManager_h

#include <FRSensorManager.h>
#include <TinyGPSPlus.h>

//creates class which inherents Sensor
class TinyGPSManager : public SensorManager {
  public :
  TinyGPSManager();
  ~TinyGPSManager(); // Add a destructor
  bool Init();
  bool HasValidData();
  String HeaderString() override;
  String SensorString() override;

  private :
  const int _BAUDGPS = 9600;
  const int _TIMEOUTMS = 20;
  TinyGPSPlus* _myGPS;

};

#endif