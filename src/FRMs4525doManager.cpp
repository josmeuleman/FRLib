// Manager for a MPU6050 sensor. It uses the SensorManager class, such that the Logger class can log the sensor.
// 
// 2023-04-05, Jos Meuleman & Tim van Cuylenborg, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "FRMs4525doManager.h"
#include "FRGeneric.h"

//Ms4525doManager::Ms4525doManager() : _myPitot(){
//}

Ms4525doManager::Ms4525doManager() {
  _myPitot = new bfs::Ms4525do(); // Allocate memory for the object
}

Ms4525doManager::~Ms4525doManager() {
  //_myPitot.~Ms4525do(); // Call the destructor of the object
  delete _myPitot;
}

bool Ms4525doManager::Init(TwoWire &myWire){
  _myPitot->Config(&Wire, PITOT_I2C_ADDRESS, 1.0f, -1.0f);
  // Start communication with the Pitot Sensor. If this fails, the program will stop here
  if (!_myPitot->Begin()) {
    //Serial.println("Error communicating with ms4525do");
    return false;
  }
  else {
    //Serial.println("ms4525do found!");
	return true;
  }
}

String Ms4525doManager::HeaderString(){
  String tempString;
  tempString.concat("pressure [Pa]; ");
  tempString.concat("tempPitot [degC]; ");
  return tempString;
}

String Ms4525doManager::SensorString(){
  _myPitot->Read();
  String tempString;
  
  tempString.concat(createFloatString(_myPitot->pres_pa(), 3));
  tempString.concat(createFloatString(_myPitot->die_temp_c(), 1));
  
  return tempString;
}