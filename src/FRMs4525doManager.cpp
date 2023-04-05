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
  tempString.concat("pressure [Pa]; ");
  tempString.concat("tempPitot [degC]; ");
  return tempString;
}

String Ms4525doManager::SensorString(){
  String tempString;
  
  tempString.concat(createFloatString(_myPitot->pres_pa();, 3));
  tempString.concat(createFloatString(_myPitot->temp(), 1));
  
  return tempString;
}