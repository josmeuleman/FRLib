// Testscript for testing the button and the LED on the ESP PCB
//
// 2023-02-20, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include "FRButton.h"
#include "FRServo.h"

const int PINSWITCH = 22;
const int PINSERVO = 25;

Button myButton(PINSWITCH, true); // Create a button object with the given pin. True for an inverted button, false for a normal button
Servo myServo(PINSERVO);
//---------------------------------------------------------------------------------------------------------
// SETUP
// This block of code is only run once at the beginning
//---------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  myServo.SetMaxSpeed(1);
  myServo.SetTargetPos(127);
}

//---------------------------------------------------------------------------------------------------------
// LOOP
// This block of code is looped infinitely
//---------------------------------------------------------------------------------------------------------
void loop() {
  // Checks if the button has changed from not pushed to pushed
  myButton.Update();
  if (myButton.HasChangedUp()){
    myServo.SetTargetPos(255);
  }
  if (myButton.HasChangedDown()){
    myServo.SetTargetPos(0);
  }
  myServo.Update();
  Serial.println();
  delay(10);
}
