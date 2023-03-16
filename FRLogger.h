#ifndef FRLogger_h
#define FRLogger_h

#include <SD.h>  // include the library for the SD card
#include <FS.h>  // include the library for writing files
#include <FRSensor.h> //has access to the virtual functions of the sensor class
#include <vector>


// typedef enum {
//   MPU6050,
//   TINYGPS,
//   MS4525DO
// } logger_sensortype;

class Logger{
  public:
  Logger();
  bool CheckSD();

  bool IsLogging();
  bool StartLogger();
  bool StopLogger();
  String GetLoggerFileName();
  void Update();
  void AddSensor(SensorManager* Sensor);
  void AddFloatMonitorToLog(float* value);
  // void AddFloatToLogLine(float value, String format);
  // void AddStringToLogLine(float value, String format);


  private:
  String FindNewFileName();
  std::vector<SensorManager*> sensors;  // vector of Sensor objects
  bool _isLogging;
  String _fileName;
  File _file;
  
};


#endif