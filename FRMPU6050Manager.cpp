#include "FRMPU6050Manager.h"

MPU6050Manager::MPU6050Manager(){
  _myMPU = new Adafruit_MPU6050(); // Allocate memory for the object
}


MPU6050Manager::~MPU6050Manager(){
  delete _myMPU; // Free the memory for the object
}

bool MPU6050Manager::InitI2C(TwoWire &myWire){

  if (!_myMPU->begin(MPU6050_ADDRESS, &myWire)) {
    Serial.println("Error communicating with MPU6050");
    return false;
  }
  else {
    Serial.println("MPU6050 found!");
	return true;
  }
}

String MPU6050Manager::HeaderString(){
  return "Acceleration.x(m/s^2),Acceleration.y(m/s^2),Acceleration.z(m/s^2),Rotation.x(rad/s),Rotation.y(rad/s),Rotation.z(rad/s),Temperature(degC)";
}

String MPU6050Manager::SensorString(){
  sensors_event_t a, g, temp;
  _myMPU->getEvent(&a, &g, &temp);


  String Data = String(a.acceleration.x) + "," + String(a.acceleration.y) + "," + String(a.acceleration.z);

  //adding rotation data
  Data = Data + "," + String(g.gyro.x) + "," + String(g.gyro.y) + "," + String(g.gyro.z);
  //adding temperature
  Data = Data + "," + String(temp.temperature);
  return Data;
}