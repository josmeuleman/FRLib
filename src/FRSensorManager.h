// Generic SensorManager for the Logger in FRLib
// 
// 2023-03-20, Jos Meuleman & Tim van Cuylenborg, Inholland Aeronautical & Precision Engineering, The Netherlands


#ifndef FRSensorManager_h
#define FRSensorManager_h

#include "WString.h"

//base class for all sensor, neccessary to interface with the FRLogger
class SensorManager {
public:
  virtual String HeaderString() = 0;
  virtual String SensorString() = 0;
  virtual ~SensorManager() = default;
};

#endif