// Manager for a MPU6050 sensor. It uses the SensorManager class, such that the Logger class can log the sensor.
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "FRTinyGPSManager.h"
#include "FRGeneric.h"

TinyGPSManager::TinyGPSManager(){
  _myGPS = new TinyGPSPlus();
}

TinyGPSManager::~TinyGPSManager(){
  delete _myGPS; 
}

bool TinyGPSManager::Init(){
  Serial2.begin(_BAUDGPS);
  return true;
}

String TinyGPSManager::HeaderString(){
  String tempString;
  tempString.concat("Satellites []; ");
  tempString.concat("Date [yyyy-mm-dd]; ");
  tempString.concat("Time [hh:mm:ss]; ");
  tempString.concat("Latitude [deg]; ");
  tempString.concat("Longitude [deg]; ");
  tempString.concat("Altitude [m]; ");
  return tempString;
}

String TinyGPSManager::SensorString(){
  long tStart = millis();
  while ((Serial2.available() > 0) & (millis()-tStart < _TIMEOUTMS)){
    _myGPS->encode(Serial2.read());
  }	

  String tempString;
  tempString.concat(createIntString(_myGPS->satellites.value()));
  if (_myGPS->date.isValid()) {
	tempString.concat(createDateString(_myGPS->date.year(), _myGPS->date.month(), _myGPS->date.day()));
  }
  else {
    tempString.concat(createDateString(9999, 99, 99));
  }
  
  if (_myGPS->time.isValid()) {
	tempString.concat(createTimeString(_myGPS->time.hour(), _myGPS->time.minute(), _myGPS->time.second()));
  }
  else {
    tempString.concat(createTimeString(99, 99, 99));
  }
  
  if (_myGPS->location.isValid()) {
	tempString.concat(createFloatString(_myGPS->location.lat(), 6));
	tempString.concat(createFloatString(_myGPS->location.lng(), 6));
  }
  else {
    tempString.concat(createFloatString(0, 6));
	tempString.concat(createFloatString(0, 6));  
  }	  
  if (_myGPS->altitude.isValid()) {
	tempString.concat(createFloatString(_myGPS->altitude.meters(), 1));
  }
  else {
 	tempString.concat(createFloatString(0, 1));
  }
  return tempString;
}