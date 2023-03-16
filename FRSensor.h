#ifndef Sensor_h
#define Sensor_h

#include "WString.h"

//base class for all sensor, neccessary to interface with the FRLogger
class SensorManager {
public:
  virtual String HeaderString() = 0;
  virtual String SensorString() = 0;
  virtual ~SensorManager() = default;
};


#endif