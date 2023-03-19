// Generic functions for FRLib
// 
// 2023-03-19, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#ifndef FRGeneric_h
#define FRGeneric_h
#include <cstdio>

String createTimeString(int hour, int minute, int second) {
  char buffer[11];
  sprintf(buffer, "%02d:%02d:%02d; ", hour, minute, second);
  return  buffer;
}

String createDateString(int year, int month, int day){
  char buffer[13];
  sprintf(buffer, "%04d-%02d-%02d; ", year, month, day);
  return  buffer;
}

String createFloatString(float value, unsigned int accuracy){
  String myString = String(value, accuracy);
  myString.concat("; ");
  return myString;
}

String createIntString(int value) {
  String myString = String(value);
  myString.concat("; ");
  return myString;  
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


#endif