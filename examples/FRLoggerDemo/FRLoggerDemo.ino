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
#include <FRLogger.h>
#include <FRLED.h>
#include <FRButton.h>
#include <FRMPU6050Manager.h> //Use a custom library, that internally initializes and logs the MPU6050
//#include <Adafruit_MPU6050.h>  


const int I2C_SDA = 33;                 // The data pin for I2C communication
const int I2C_SCL = 32;                 // The clock pin for I2C communcation
const int PINSWITCH = 22;               // The pin number for he button to start and stop logging
const int PINLED = 21;                  // The pin number for the LED
const int PINAD = 34;                   // Analog input pin number
const int LOOPTIMEMS = 100;             // Loop time for reading the AD channel in milliseconds

// Create all objects
Timer myTimer(LOOPTIMEMS);              // Timer object for the clock
Logger myLogger;                        // Logger object for logging sensors to the SD
Button myButton(PINSWITCH, true);       // Create a button object with the given pin. True for an inverted button, false for a normal button
LED myLed(PINLED);                      // Create a led object with the given pin.
MPU6050Manager myMPU;                   // Make an object for the sensor manager for the MPU6050 (accelerometer and gyro)
int analogValue; 

//---------------------------------------------------------------------------------------------------------
// SETUP
// This block of code is only run once at the beginning
//---------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);     // Start the serial communciation
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);
  myMPU.InitI2C(Wire);
  pinMode(PINAD, INPUT);  // Assign the pin for input
  if (myLogger.CheckSD()) {
    Serial.println("SD card found.");
  } else {
    Serial.println("No SD card found.");
  }
  myLogger.AddSensor(&myMPU);

  myTimer.Start();
  
}

//---------------------------------------------------------------------------------------------------------
// LOOP
// This block of code is looped infinitely
//---------------------------------------------------------------------------------------------------------
void loop() {
  // Loop through the two pins
  analogValue = analogRead(PINAD);  // Read the analog input

  myButton.Update();              // Read the state of the button

  if (myButton.HasChangedUp()) {  //Check if the state has changed from low to high
    myLed.Toggle();  // Change the state of the led
    if (!myLogger.IsLogging()) { // Start logging
      Serial.println("Start logging");
      if (!myLogger.StartLogger()) {
        Serial.println("Something went wrong with the start of the log");
      }
    } else {// Stop logging
      Serial.println("Stop logging");
      if (!myLogger.StopLogger()) {
        Serial.println("Something went wrong with the end of the log");
      }
    }
  }

  // All sensors that are connected to the logger in the setup, will be read and written to the logfile
  myLogger.Update();



  if (myTimer.WaitUntilEnd()) {
    Serial.println("Overrun!");
  }
}