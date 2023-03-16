// Testscript OverSampling & Timers on the Flight Recorder PCB
// Required hardware:
// - 1x potmeter
// - 6x breadboard cables female-male
// Connections:
// - Potmeter1, GND - Analog Input J6, GND
// - Potmeter1, Wiper - Analog Input J6, D35
// - Potmeter1, VCC - Analog Input J6, 3.3V
// Required libraries:
// - FRLib (download from https://github.com/josmeuleman/FRLib, unzipped in ../Documents/Arduino/libraries/ )
//
// 2023-03-14, Jos Meuleman, Inholland Aeronautical & Precision Engineering, The Netherlands

#include <FRTimer.h>
#include "FRLogger.h"
#include "FRLED.h"
#include "FRButton.h"

const int PINSWITCH = 22;
const int PINLED = 21;
const int PINAD = 34;              // Analog input pin number
const int LOOPTIMEREADMS = 100;    // Loop time for reading the AD channel in milliseconds
const int LOOPTIMEPRINTMS = 1000;  // Loop time for printing average values to the Serial monitor

Timer myFastTimer(LOOPTIMEREADMS);
Timer mySlowTimer(LOOPTIMEPRINTMS);
Logger myLogger;

Button myButton(PINSWITCH, true);  // Create a button object with the given pin. True for an inverted button, false for a normal button
LED myLed(PINLED);                 // Create a led object with the given pin.

int analogValue;
long sumAnalogValues = 0;
int counter = 0;
float averageValue = 0.0;

//---------------------------------------------------------------------------------------------------------
// SETUP
// This block of code is only run once at the beginning
//---------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);     // Start the serial communciation
  pinMode(PINAD, INPUT);  // Assign the pin for input
  if (myLogger.CheckSD()) {
    Serial.println("SD card found.");
  } else {
    Serial.println("No SD card found.");
  }
  myFastTimer.Start();
  mySlowTimer.Start();
}

//---------------------------------------------------------------------------------------------------------
// LOOP
// This block of code is looped infinitely
//---------------------------------------------------------------------------------------------------------
void loop() {
  // Loop through the two pins
  analogValue = analogRead(PINAD);  // Read the analog input
  sumAnalogValues += analogValue;   //add the new value to the total sum
  counter++;                        // increase the counter

  myButton.Update();              // Read the state of the button
  if (myButton.HasChangedUp()) {  //Check if the state has changed from low to high
    Serial.println("toggle");
    myLed.Toggle();  // Change the state of the led
    if (!myLogger.IsLogging()) {
      if (myLogger.StartLogger()) {
        Serial.println("Log started successfully");
      } else {
        Serial.println("Something went wrong with the start of the log");
      }

    } else {
      if (myLogger.StopLogger()) {
        Serial.println("Log stopped successfully");
      } else {
        Serial.println("Something went wrong with the end of the log");
      }
    }
  }


  if (mySlowTimer.LoopTimePassed()) {
    averageValue = float(sumAnalogValues) / float(counter);
    counter = 0;          //Reset the counter
    sumAnalogValues = 0;  //Reset the sum value
  }
  // Serial.print("CurrentValue:");
  // Serial.print(analogValue);  // Print the current value
  // Serial.print("; AverageValue:");
  // Serial.println(averageValue); // Print the last average value
  if (myFastTimer.WaitUntilEnd()) {
    Serial.println("Overrun!");
  }
}