// Manager for a ms4525do sensor (differential pressure, pitot). It uses the SensorManager class, such that the Logger class can log the sensor.
// 
// 2023-04-05, Jos Meuleman & Tim van Cuylenborg, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRMs4525doManager_h
#define FRMs4525doManager_h

#include <FRSensorManager.h>
#include <ms4525do.h>  // include the library for the ms4525do sensor
#include <Wire.h>

//creates class which inherents Sensor
class Ms4525doManager : public SensorManager {
  public :
  Ms4525doManager();
  ~Ms4525doManager(); // Add a destructor
  bool Init(TwoWire &myWire);
  String HeaderString() override;
  String SensorString() override;

  private :
  bfs::Ms4525do _myPitot  
  const int PITOT_I2C_ADDRESS = 0x28;     // I2C address of the Pitot sensor
};

#endif