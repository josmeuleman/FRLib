// Manager for a MPU6050 sensor. It uses the SensorManager class, such that the Logger class can log the sensor.
// 
// 2023-04-05, Jos Meuleman & Tim van Cuylenborg, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "FRMs4525doManager.h"
#include "FRGeneric.h"

Ms4525doManager::Ms4525doManager(){
  _myPitot = new bfs::Ms4525do(); // Allocate memory for the object
}


Ms4525doManager::~Ms4525doManager(){
  delete _myPitot; // Free the memory for the object
}

bool Ms4525doManager::Init(TwoWire &myWire){

  if (!_myPitot->begin(PITOT_I2C_ADDRESS, &myWire)) {
    //Serial.println("Error communicating with ms4525do");
    return false;
  }
  else {
    //Serial.println("ms4525do found!");
	_myPitot->Config(&Wire, PITOT_I2C_ADDRESS, 1.0f, -1.0f);
	return true;
  }
}

String Ms4525doManager::HeaderString(){
  String tempString;
  tempString.concat("accX [m/s2]; ");
  tempString.concat("accY [m/s2]; ");
  tempString.concat("accZ [m/s2]; ");
  tempString.concat("rotX [deg/s]; ");
  tempString.concat("rotY [deg/s]; ");
  tempString.concat("rotZ [deg/s]; ");
  tempString.concat("tempMPU [degC]; ");
  return tempString;
}

String Ms4525doManager::SensorString(){
  sensors_event_t a, g, temp;
  _myPitot->getEvent(&a, &g, &temp);
  String tempString;
  
  tempString.concat(createFloatString(a.acceleration.x, 3));
  tempString.concat(createFloatString(a.acceleration.y, 3));
  tempString.concat(createFloatString(a.acceleration.z, 3));
  tempString.concat(createFloatString(g.gyro.x, 3));
  tempString.concat(createFloatString(g.gyro.y, 3));
  tempString.concat(createFloatString(g.gyro.z, 3));
  tempString.concat(createFloatString(temp.temperature,1));
 
  return tempString;
}