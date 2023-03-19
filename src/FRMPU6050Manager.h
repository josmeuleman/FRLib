#ifndef FRMPU6050Manager_h
#define FRMPU6050Manager_h

#include <FRSensor.h>
#include <Adafruit_MPU6050.h>  // include the library for the MPU6050 sensor
#include <Wire.h>

//creates class which inherents Sensor
class MPU6050Manager : public SensorManager {
  public : 
  Adafruit_MPU6050* _myMPU; // Pointer to the sensor object
  const int MPU6050_ADDRESS = 0x68; // The I2C address of the MPU6050 sensor
  
  MPU6050Manager();
  ~MPU6050Manager(); // Add a destructor
  bool InitI2C(TwoWire &myWire);
  String HeaderString() override;
  String SensorString() override;

};

#endif