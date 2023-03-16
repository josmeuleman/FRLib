#include "Arduino.h"
#include "FRLogger.h"

const int I2C_SDA = 33; // The data pin for I2C communication
const int I2C_SCL = 32; // The clock pin for I2C communcation


Logger::Logger() {
  _isLogging = false;
  _fileName = "";
}

bool Logger::CheckSD() {
  if (!SD.begin()) {
    return false;
  } else {
    return true;
  }
}

bool Logger::IsLogging() {
  return _isLogging;
}

bool Logger::StartLogger() {
  if (_isLogging) {  // Already logging
    return false;
  }

  _fileName = FindNewFileName();
  if (_fileName.length() == 0) {  // No proper filename found
    return false;
  }

  _file = SD.open(_fileName, FILE_WRITE);
  if (!_file) {  //Failed to open the file
    return false;
  }

  _isLogging = true;
  return true;
}


bool Logger::StopLogger() {
  if (!_isLogging) { // Logger not running
    return false;
  }

  if (!_file) { // File not open
    return false;
  }

  _file.close();
  _isLogging = false;
  return true;
}




String Logger::GetLoggerFileName() {
  return _fileName;
}

void Logger::Update(){
  for (int i = 0; i < sensors.size(); i++) {
    Serial.print(sensors[i]->SensorString());
  }
  Serial.println();
}

void Logger::AddSensor(SensorManager *Sensor){
  sensors.push_back(Sensor);
  Serial.println("Added a sensor");
}

String Logger::FindNewFileName() {
  int fileNumber = 1;
  while (fileNumber <= 99999) {
    _fileName = "/LOG";
    String fileNumberString = String(fileNumber);
    for (int i = 0; i < 5 - fileNumberString.length(); i++) {
      _fileName.concat("0");
    }
    _fileName.concat(fileNumberString);
    _fileName.concat(".CSV");

    if (!SD.exists(_fileName)) {
      return _fileName;
    }

    fileNumber++;
  }
  return "";
}
